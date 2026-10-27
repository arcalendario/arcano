#include "control_web.h"
#include <WebServer.h>
#include <Preferences.h>
#include <WiFiManager.h>
#include "paletas_de_colores.h"
#include "luces_led.h"
#include "gestion_tiempo.h" 
#include "colores_nuevos.h" 

int brillo = 70;
int efectoElegido = 0;
int indicePaleta = 0;

extern CRGB leds[]; 

WebServer server(80);
Preferences preferences;

void enviarPaginaPrincipal() {
    Paleta p = obtenerColoresActuales();
    auto getHex = [](CRGB c) -> uint32_t { return ((uint32_t)c.r << 16) | ((uint32_t)c.g << 8) | c.b; };
    
    // Leemos los colores que el usuario guardó en su paleta personalizada (si no hay, arranca en blanco)
    preferences.begin("paleta_usr", true); 
    uint32_t c0_usr = preferences.getUInt("c0", 0xFFFFFF);
    uint32_t c1_usr = preferences.getUInt("c1", 0xFFFFFF);
    uint32_t c2_usr = preferences.getUInt("c2", 0xFFFFFF);
    uint32_t c3_usr = preferences.getUInt("c3", 0xFFFFFF);
    preferences.end();

    static char htmlBuffer[8500];

    const char* htmlTemplate = 
        "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<style>"
        "body{background:#111; color:#fff; font-family:sans-serif; text-align:center; padding:20px; position:relative;}"
        ".carrusel{display:flex; justify-content:center; align-items:center; gap:25px; margin:30px 0 80px 0;}"
        ".flecha{cursor:pointer; width:0; height:0; border-top:8px solid transparent; border-bottom:8px solid transparent;}"
        ".izq{border-right:12px solid #777;}.der{border-left:12px solid #777;}"
        ".efectos-grid{display:grid; grid-template-columns:repeat(3, 35px); justify-content:center; gap:25px; margin:0 auto 60px auto;}"
        ".btn-efecto{cursor:pointer; border:3px solid transparent; border-radius:8px; overflow:hidden; transition:0.3s; width:35px; height:35px; display:flex; flex-direction:column;}"
        ".btn-efecto.activo{border-color:#fff;}"
        ".slider-container{margin:55px auto; max-width:90%; text-align:left;}"
        ".slider-row{display:flex; align-items:center; gap:15px; width:100%;}"
        ".icon-box{width:35px; display:flex; justify-content:center; align-items:center; flex-shrink:0;}"
        "input[type=range]{flex-grow:1; height:12px; border-radius:6px; background:#333; outline:none; -webkit-appearance:none;}"
        "input[type=range]::-webkit-slider-thumb{-webkit-appearance:none; width:28px; height:28px; border-radius:50%; background:#fff; cursor:pointer;}"
        /* Estilos del Creador de Paleta */
        ".creador-paleta{margin-top:60px; padding-top:30px; border-top:1px solid #333;}"
        ".creador-paleta h3{color:#F4A261; font-size:14px; margin-bottom:20px; letter-spacing:1px;}"
        ".color-pickers{display:flex; justify-content:center; gap:15px; margin-bottom:25px;}"
        "input[type=color]{width:45px; height:45px; border:2px solid #333; border-radius:8px; cursor:pointer; background:none; padding:0; outline:none;}"
        ".btn-guardar{background:#457B9D; color:#fff; padding:12px 25px; border:none; border-radius:6px; font-weight:bold; font-size:14px; cursor:pointer; transition:0.3s;}"
        ".btn-guardar:hover{background:#1D3557;}"
        "footer{margin-top:90px; padding:20px; color:#555; font-size:14px; border-top:1px solid #333;}"
        ".btn-info{position:absolute; top:15px; right:15px; width:32px; height:32px; border-radius:50%; border:2px solid #555; color:#555; display:flex; justify-content:center; align-items:center; text-decoration:none; font-family:serif; font-style:italic; font-size:20px; font-weight:bold; transition:0.3s;}"
        ".btn-info:hover{border-color:#fff; color:#fff;}"
        "</style>"
        "<script>"
        "let tBrillo;"
        "function moverBrillo(val) { clearTimeout(tBrillo); tBrillo = setTimeout(()=>fetch('/brillo_temp?v='+val), 50); }"
        "function selEfecto(id) { fetch('/efecto?v='+id).then(() => location.reload()); }"
        "function navegar(dir) { fetch('/paleta?v=' + ((%d + dir + 8) %% 8)).then(() => location.reload()); }"
        /* Script para guardar los colores */
        "function guardarCustom() {"
        "  let c0 = document.getElementById('cp0').value.substring(1);"
        "  let c1 = document.getElementById('cp1').value.substring(1);"
        "  let c2 = document.getElementById('cp2').value.substring(1);"
        "  let c3 = document.getElementById('cp3').value.substring(1);"
        "  fetch('/save_paleta?c0='+c0+'&c1='+c1+'&c2='+c2+'&c3='+c3).then(() => location.reload());"
        "}"
        "</script>"
        "</head><body>"
        "<a href='/info' class='btn-info'>i</a>"
        "<div class='carrusel'>"
        "  <div class='flecha izq' onclick='navegar(-1)'></div>"
        "  <svg width='150' height='150' viewBox='0 0 200 200'><g clip-path='url(#round-corners)'>"
        "    <defs><clipPath id='round-corners'><rect width='200' height='200' rx='20' ry='20'/></clipPath></defs>"
        "    <rect x='0' y='0' width='93' height='93' fill='#%06X'/><rect x='107' y='0' width='93' height='93' fill='#%06X'/>"
        "    <rect x='0' y='107' width='93' height='93' fill='#%06X'/><rect x='107' y='107' width='93' height='93' fill='#%06X'/>"
        "    <line x1='-10' y1='100' x2='100' y2='-10' stroke='#111' stroke-width='14'/>" 
        "    <line x1='100' y1='-10' x2='210' y2='100' stroke='#111' stroke-width='14'/>"  
        "    <line x1='-10' y1='100' x2='100' y2='210' stroke='#111' stroke-width='14'/>"  
        "    <line x1='100' y1='210' x2='210' y2='98' stroke='#111' stroke-width='14'/>"   
        "  </g></svg>"
        "  <div class='flecha der' onclick='navegar(1)'></div>"
        "</div>"
        "<div class='efectos-grid'>"
        "  <div class='btn-efecto %s' onclick='selEfecto(0)'><svg width='35' height='35'><rect width='35' height='35' fill='#F0F0F0'/></svg></div>"
        "  <div class='btn-efecto %s' onclick='selEfecto(1)'><svg width='35' height='35'><polygon points='0,0 35,0 0,35' fill='#3A3A3A'/><polygon points='35,35 35,0 0,35' fill='#84A9D1'/></svg></div>"
        "  <div class='btn-efecto %s' onclick='selEfecto(2)'><svg width='35' height='35'><defs><linearGradient id='grad' x1='0%%' y1='0%%' x2='100%%' y2='100%%'><stop offset='0%%' stop-color='#00BFFF'/><stop offset='100%%' stop-color='#FF1493'/></linearGradient></defs><rect width='35' height='35' fill='url(#grad)'/></svg></div>"
        "  <div class='btn-efecto %s' onclick='selEfecto(3)'><svg width='35' height='35'><rect y='0' width='35' height='7' fill='#FFB3BA'/><rect y='7' width='35' height='7' fill='#B5EAD7'/><rect y='14' width='35' height='7' fill='#FFB3BA'/><rect y='21' width='35' height='7' fill='#B5EAD7'/><rect y='28' width='35' height='7' fill='#FFB3BA'/></svg></div>"
        "  <div class='btn-efecto %s' onclick='selEfecto(4)'><svg width='35' height='35'><rect width='17.5' height='35' fill='#F4A261'/><rect x='17.5' width='17.5' height='35' fill='#457B9D'/></svg></div>"
        "  <div class='btn-efecto %s' onclick='selEfecto(5)'><svg width='35' height='35'><rect width='35' height='35' fill='#111'/><text x='50%%' y='50%%' font-family='sans-serif' font-size='22' font-weight='bold' fill='#FFF' text-anchor='middle' dominant-baseline='central'>?</text></svg></div>"
        "</div>"
        "<div class='slider-container'>"
        "  <div class='slider-row'>"
        "    <div class='icon-box'><svg width='20' height='20' viewBox='0 0 24 24' fill='none' stroke='#FF9800' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'><circle cx='12' cy='12' r='5'></circle><line x1='12' y1='1' x2='12' y2='3'></line><line x1='12' y1='21' x2='12' y2='23'></line><line x1='4.22' y1='4.22' x2='5.64' y2='5.64'></line><line x1='18.36' y1='18.36' x2='19.78' y2='19.78'></line><line x1='1' y1='12' x2='3' y2='12'></line><line x1='21' y1='12' x2='23' y2='12'></line><line x1='4.22' y1='19.78' x2='5.64' y2='18.36'></line><line x1='18.36' y1='5.64' x2='19.78' y2='4.22'></line></svg></div>"
        "    <input type='range' min='0' max='255' value='%d' oninput='moverBrillo(this.value)' onchange='fetch(\"/brillo?v=\"+this.value)'>"
        "    <div class='icon-box'><svg width='32' height='32' viewBox='0 0 24 24' fill='none' stroke='#FF9800' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'><circle cx='12' cy='12' r='5'></circle><line x1='12' y1='1' x2='12' y2='3'></line><line x1='12' y1='21' x2='12' y2='23'></line><line x1='4.22' y1='4.22' x2='5.64' y2='5.64'></line><line x1='18.36' y1='18.36' x2='19.78' y2='19.78'></line><line x1='1' y1='12' x2='3' y2='12'></line><line x1='21' y1='12' x2='23' y2='12'></line><line x1='4.22' y1='19.78' x2='5.64' y2='18.36'></line><line x1='18.36' y1='5.64' x2='19.78' y2='4.22'></line></svg></div>"
        "  </div>"
        "</div>"
        "<div class='creador-paleta'>"
        "  <h3>CREAR PALETA PERSONALIZADA</h3>"
        "  <div class='color-pickers'>"
        "    <input type='color' id='cp0' value='#%06X'>"
        "    <input type='color' id='cp1' value='#%06X'>"
        "    <input type='color' id='cp2' value='#%06X'>"
        "    <input type='color' id='cp3' value='#%06X'>"
        "  </div>"
        "  <button class='btn-guardar' onclick='guardarCustom()'>GUARDAR Y ACTIVAR</button>"
        "</div>"
        "<footer>&copy; Arcane Clock by Arcalendaro &reg;</footer>"
        "</body></html>";

    const char* act[6] = {"", "", "", "", "", ""};
    if(efectoElegido >= 0 && efectoElegido <= 5) act[efectoElegido] = "activo";

    snprintf(htmlBuffer, sizeof(htmlBuffer), htmlTemplate, 
             indicePaleta, getHex(p.color3), getHex(p.color0), getHex(p.color2), getHex(p.color1), 
             act[0], act[1], act[2], act[3], act[4], act[5], brillo,
             (uint32_t)c0_usr, (uint32_t)c1_usr, (uint32_t)c2_usr, (uint32_t)c3_usr);
             
    server.send(200, "text/html", htmlBuffer);
}

void inicializarControlWeb() {
    preferences.begin("arcano", false);
    brillo = preferences.getInt("brillo", 70);
    indicePaleta = preferences.getInt("paleta", 0);
    efectoElegido = preferences.getInt("efecto", 0);
    preferences.end();
    
    setPaletaActiva(indicePaleta);
    FastLED.setBrightness(brillo); 
    FastLED.show();

    server.on("/", enviarPaginaPrincipal);
    server.on("/brillo_temp", []() { if (server.hasArg("v")) { brillo = server.arg("v").toInt(); FastLED.setBrightness(brillo); FastLED.show(); } server.send(200, "text/plain", "OK"); });
    server.on("/brillo", []() { if (server.hasArg("v")) { brillo = server.arg("v").toInt(); preferences.begin("arcano", false); preferences.putInt("brillo", brillo); preferences.end(); FastLED.setBrightness(brillo); FastLED.show(); } server.send(200, "text/plain", "OK"); });
    server.on("/efecto", []() { if (server.hasArg("v")) { efectoElegido = server.arg("v").toInt(); preferences.begin("arcano", false); preferences.putInt("efecto", efectoElegido); preferences.end(); } server.send(200, "text/plain", "OK"); });
    
    // Nueva ruta para guardar la paleta personalizada
    server.on("/save_paleta", []() {
        if (server.hasArg("c0") && server.hasArg("c1") && server.hasArg("c2") && server.hasArg("c3")) {
            uint32_t c0 = strtoul(server.arg("c0").c_str(), NULL, 16);
            uint32_t c1 = strtoul(server.arg("c1").c_str(), NULL, 16);
            uint32_t c2 = strtoul(server.arg("c2").c_str(), NULL, 16);
            uint32_t c3 = strtoul(server.arg("c3").c_str(), NULL, 16);
            
            guardarPaletaPersonalizada(c0, c1, c2, c3);
            
            // Forzar selección de la paleta personalizada (índice 7)
            preferences.begin("arcano", false);
            preferences.putInt("paleta", 7);
            preferences.end();
            indicePaleta = 7;
            
            int hora = obtenerHora(); int min = obtenerMinuto();
            if (hora != -1 && min != -1) {
                Color m1, m2, m4, m8, h1, h2, h4, h8;
                Colores_Nuevos(hora, min, m1, m2, m4, m8, h1, h2, h4, h8);
                Paleta p = obtenerColoresActuales();
                CRGB mapa[4] = {p.color0, p.color1, p.color2, p.color3};
                leds[0] = mapa[m1]; leds[1] = mapa[m2]; leds[2] = mapa[m4]; leds[3] = mapa[m8];
                leds[4] = mapa[h1]; leds[5] = mapa[h2]; leds[6] = mapa[h4]; leds[7] = mapa[h8];
                FastLED.show(); 
            }
        }
        server.send(200, "text/plain", "OK");
    });

    server.on("/info", []() {
        String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>";
        html += "<style>body{background:#111; color:#fff; font-family:sans-serif; text-align:center; padding:40px;}";
        html += "h2{color:#457B9D;} p{color:#aaa; font-size:14px; margin-bottom:40px;}";
        html += ".btn{display:block; width:100%; max-width:250px; margin:15px auto; padding:15px; border-radius:8px; text-decoration:none; font-weight:bold; font-size:16px;}";
        html += ".btn-wifi{background:#b23b3b; color:#fff;}";
        html += ".btn-memoria{background:#333; color:#F4A261;}";
        html += ".btn-volver{background:transparent; color:#00BFFF; margin-top:30px;}</style></head><body>";
        html += "<h2>Ajustes del Reloj</h2>";
        html += "<p>Arcane Clock &bull; Versión 1.0</p>";
        html += "<a href='/memoria' class='btn btn-memoria'>Salud de Memoria</a>";
        html += "<a href='/reset_wifi' class='btn btn-wifi' onclick='return confirm(\"¿Estás seguro de borrar el Wi-Fi? El reloj se reiniciará automáticamente para entrar en modo configuración.\");'>Cambiar Red Wi-Fi</a>";
        html += "<a href='/' class='btn btn-volver'>&#9664; Volver al Reloj</a>";
        html += "</body></html>";
        server.send(200, "text/html", html);
    });

    server.on("/reset_wifi", []() {
        server.send(200, "text/html", "<body style='background:#111; color:#fff; font-family:sans-serif; text-align:center; padding-top:50px;'><h2>Reiniciando sistema...</h2><p>Por favor busca la red <b>ARCANO_Config_Wifi</b> en tu dispositivo para ingresar tu nueva red.</p></body>");
        delay(1500);
        WiFiManager wm;
        wm.resetSettings(); 
        ESP.restart();      
    });

    server.on("/memoria", []() {
        String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>";
        html += "<style>body{background:#111; color:#fff; font-family:sans-serif; text-align:center; padding:40px;}";
        html += "h2{color:#FF9800;} p{font-size:18px; background:#222; padding:15px; border-radius:8px; display:inline-block; margin:10px;}</style></head><body>";
        html += "<h2>Salud del ESP32</h2>";
        html += "<p><b>Memoria Heap Libre:</b><br>" + String(ESP.getFreeHeap()) + " bytes</p><br>";
        html += "<p><b>Mínima Alcanzada:</b><br>" + String(ESP.getMinFreeHeap()) + " bytes</p><br><br>";
        html += "<a href='/info' style='color:#00BFFF; text-decoration:none; font-size:18px;'>&#9664; Volver a Ajustes</a>";
        html += "</body></html>";
        server.send(200, "text/html", html);
    });

    server.on("/paleta", []() {
        if (server.hasArg("v")) {
            indicePaleta = server.arg("v").toInt();
            setPaletaActiva(indicePaleta);
            preferences.begin("arcano", false);
            preferences.putInt("paleta", indicePaleta);
            preferences.end();
            int hora = obtenerHora(); int min = obtenerMinuto();
            if (hora != -1 && min != -1) {
                Color m1, m2, m4, m8, h1, h2, h4, h8;
                Colores_Nuevos(hora, min, m1, m2, m4, m8, h1, h2, h4, h8);
                Paleta p = obtenerColoresActuales();
                CRGB mapa[4] = {p.color0, p.color1, p.color2, p.color3};
                leds[0] = mapa[m1]; leds[1] = mapa[m2]; leds[2] = mapa[m4]; leds[3] = mapa[m8];
                leds[4] = mapa[h1]; leds[5] = mapa[h2]; leds[6] = mapa[h4]; leds[7] = mapa[h8];
                FastLED.show(); 
            }
        }
        server.send(200, "text/plain", "OK");
    });
    
    server.begin();
}

void manejarPeticionesWeb() { server.handleClient(); }
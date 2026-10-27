#include "wifi_setup.h"
#include <FastLED.h> 
#include <ArduinoOTA.h>

extern CRGB leds[]; 

// =========================================================
// TAREA PARALELA PARA ANIMAR LAS LUCES SIN INTERRUMPIR EL WIFI
// =========================================================
TaskHandle_t tareaLucesWiFi;

void animacionEsperandoWiFi(void * parameter) {
    uint8_t hue = 0; 
    
    while(true) {
        for(int i = 0; i < 8; i++) {
            leds[i] = CHSV(hue, 255, 255); 
        }
        FastLED.show();
        hue++; 
        vTaskDelay(80 / portTICK_PERIOD_MS); 
    }
}

void setupWiFi() {
    WiFiManager wifiManager;

    wifiManager.setTitle("Configuración ARCANO");

    const char* customHTML = R"=====(
    <script>
    document.addEventListener('DOMContentLoaded', function() {
        if (window.location.pathname === '/') {
            
            var s = document.createElement('style');
            s.innerHTML = '.wrap { display: none !important; } body { background: #000; margin: 0; }';
            document.head.appendChild(s);

            var sp = document.createElement('div');
            sp.style.cssText = 'position:fixed;top:0;left:0;width:100%;height:100%;background:#000;z-index:9999;display:flex;flex-direction:column;align-items:center;justify-content:center;color:#fff;font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,sans-serif;box-sizing:border-box;overflow-y:auto;padding:20px;';
            sp.innerHTML = `
                <!-- ¡LOGO AGRANDADO UN 25%! (de 180 a 225 píxeles) -->
                <svg width="225" height="225" viewBox="0 0 100 100" style="margin-bottom:30px;">
                    <defs>
                        <clipPath id="tl"><rect x="0" y="0" width="46" height="46" rx="6" /></clipPath>
                        <clipPath id="tr"><rect x="54" y="0" width="46" height="46" rx="6" /></clipPath>
                        <clipPath id="bl"><rect x="0" y="54" width="46" height="46" rx="6" /></clipPath>
                        <clipPath id="br"><rect x="54" y="54" width="46" height="46" rx="6" /></clipPath>
                    </defs>
                    
                    <g clip-path="url(#tl)">
                        <polygon points="0,0 46,0 0,46" fill="#34A853" />
                        <polygon points="46,0 46,46 0,46" fill="#FBBC05" />
                        <line x1="0" y1="46" x2="46" y2="0" stroke="#000" stroke-width="8" />
                    </g>
                    
                    <g clip-path="url(#tr)">
                        <polygon points="54,0 100,0 100,46" fill="#EA4335" />
                        <polygon points="54,0 100,46 54,46" fill="#FBBC05" />
                        <line x1="54" y1="0" x2="100" y2="46" stroke="#000" stroke-width="8" />
                    </g>
                    
                    <g clip-path="url(#bl)">
                        <polygon points="0,54 46,54 46,100" fill="#FBBC05" />
                        <polygon points="0,54 46,100 0,100" fill="#34A853" />
                        <line x1="0" y1="54" x2="46" y2="100" stroke="#000" stroke-width="8" />
                    </g>
                    
                    <g clip-path="url(#br)">
                        <polygon points="54,54 100,54 54,100" fill="#34A853" />
                        <polygon points="100,54 100,100 54,100" fill="#4285F4" />
                        <line x1="54" y1="100" x2="100" y2="54" stroke="#000" stroke-width="8" />
                    </g>
                </svg>
                
                <h1 style="font-size:48px; margin:0 0 5px 0; letter-spacing:-2px; font-weight:800;">arcano, na</h1>
                <div style="font-style:italic; color:#aaa; font-size:14px; margin-bottom:25px;">Del lat. arcānus</div>
                
                <div style="font-size:13px; line-height:1.6; max-width:300px; text-align:center; margin-bottom:40px; color:#ddd;">
                    <p style="margin:6px 0;">1. adj. Dicho especialmente de una cosa: Secreta, recóndita, reservada.</p>
                    <p style="margin:6px 0;">2. m. Secreto muy reservado y de importancia.</p>
                    <p style="margin:6px 0;">3. m. Misterio, cosa oculta y muy difícil de conocer.</p>
                </div>
                
                <div style="display:flex; justify-content:space-between; width:100%; max-width:320px; margin-bottom:50px;">
                    <div style="display:flex; flex-direction:column; text-align:center; flex:1;">
                        <span style="color:#F4A261; font-weight:bold; font-size:13px; margin-bottom:3px;">Idea y Código:</span>
                        <span style="color:#fff; font-size:11px; letter-spacing:0.5px;">GERMAN REPETTO</span>
                    </div>
                    <div style="display:flex; flex-direction:column; text-align:center; flex:1;">
                        <span style="color:#F4A261; font-weight:bold; font-size:13px; margin-bottom:3px;">Look and Feel:</span>
                        <span style="color:#fff; font-size:11px; letter-spacing:0.5px;">FERNANDO MONTERO</span>
                    </div>
                </div>
                
                <a href="/wifi" style="background:#555; color:#fff; text-decoration:none; padding:12px 35px; border-radius:25px; font-weight:bold; font-size:16px; box-shadow:0 4px 10px rgba(0,0,0,0.5);">CONECTARSE</a>
            `;
            document.body.appendChild(sp);
            
        } else {
            var s = document.createElement('style');
            s.innerHTML = 'body { background: #111; color: #fff; } .wrap { background: #111; border: none; } button { background: #457B9D; color: #fff; border: none; border-radius: 6px; } input { background: #333; color: #fff; border: 1px solid #555; } a { color: #F4A261; } .q { color: #F4A261; }';
            document.head.appendChild(s);
        }
    });
    </script>
    )=====";

    wifiManager.setCustomHeadElement(customHTML);

    WiFiManagerParameter custom_id("reloj_id", "Nombre del Reloj", "Arcano_01", 20);
    wifiManager.addParameter(&custom_id);

    // =========================================================
    // INICIAMOS LA ANIMACIÓN EN EL NÚCLEO 0 ANTES DE BLOQUEAR
    // =========================================================
    xTaskCreatePinnedToCore(
        animacionEsperandoWiFi, 
        "LucesWiFi",            
        2048,                   
        NULL,                   
        1,                      
        &tareaLucesWiFi,        
        0                       
    );

    if (!wifiManager.autoConnect("ARCANO_Config_Wifi")) {
        Serial.println("Error: Fallo al conectar. Reiniciando...");
        delay(3000);
        ESP.restart();
    }

    // =========================================================
    // SI LLEGAMOS ACÁ, SE CONECTÓ AL WIFI CON ÉXITO.
    // =========================================================
    if(tareaLucesWiFi != NULL) {
        vTaskDelete(tareaLucesWiFi); 
        FastLED.clear();             
        FastLED.show();              
    }

    ArduinoOTA.setHostname("arcano");
    ArduinoOTA.begin();

    Serial.println("¡Wi-Fi conectado y OTA iniciado!");
}
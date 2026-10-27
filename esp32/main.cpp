#include <Arduino.h>
#include <FastLED.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include "wifi_setup.h"
#include "gestion_tiempo.h"
#include "colores_nuevos.h"
#include "comparar_hora.h"
#include "paletas_de_colores.h"
#include "luces_led.h"
#include "control_web.h"
#include "modo_espera.h" 

Color m1, m2, m4, m8, h1, h2, h4, h8;

void setup() {
    Serial.begin(115200);
    inicializarPaletas();
    inicializarLeds();
    setupWiFi();
    
    if (MDNS.begin("arcano")) {
        Serial.println("Entra en: http://arcano.local");
    }

    inicializarControlWeb(); 
    iniciarSincronizacionTiempo();
}

void loop() {
    // 0. Escuchamos las peticiones de actualización OTA
    ArduinoOTA.handle();

    // 1. Mantenemos el servidor web activo
    manejarPeticionesWeb();
    
    // 2. Mantenemos el reloj sincronizado
    verificarSincronizacionPeriodica();
    
    int hora = obtenerHora();
    int min = obtenerMinuto();
    
    // 3. Lógica de control
    if (hora == -1 || min == -1) {
        // MODO ESPERA: Si no tenemos hora, ejecutamos el módulo modular
        ejecutarModoEspera(); 
    } 
    else {
        // MODO NORMAL: Si tenemos hora, operamos normalmente
        if (verificarCambioMinuto(min)) {
            Colores_Nuevos(hora, min, m1, m2, m4, m8, h1, h2, h4, h8);
            mostrarHoraEnLeds(m1, m2, m4, m8, h1, h2, h4, h8);
        }
    }
    
    delay(10);
}
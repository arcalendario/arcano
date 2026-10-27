#include "gestion_tiempo.h"
#include <time.h>
#include <WiFi.h>

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -10800; // Ajusta según tu zona horaria
const int daylightOffset_sec = 0;

// Constantes de tiempo en milisegundos
const unsigned long INTERVALO_NORMAL = 86400000UL; // 24 Hs
const unsigned long INTERVALO_REINTENTO = 10800000UL; // 3 horas

unsigned long ultimaSincronizacion = 0;
bool sincronizadoExitosamente = false;

void iniciarSincronizacionTiempo() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        Serial.println("Sincronización inicial exitosa.");
        ultimaSincronizacion = millis();
        sincronizadoExitosamente = true;
    } else {
        Serial.println("Fallo en sincronización inicial. Se programará reintento.");
        ultimaSincronizacion = millis() - INTERVALO_NORMAL + INTERVALO_REINTENTO;
        sincronizadoExitosamente = false;
    }
}

void verificarSincronizacionPeriodica() {
    unsigned long intervaloActual = sincronizadoExitosamente ? INTERVALO_NORMAL : INTERVALO_REINTENTO;

    if (millis() - ultimaSincronizacion >= intervaloActual) {
        Serial.println("Intentando sincronizar con NTP...");
        
        if (WiFi.status() == WL_CONNECTED) {
            configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
            
            struct tm timeinfo;
            if (getLocalTime(&timeinfo)) {
                Serial.println("Sincronización exitosa.");
                sincronizadoExitosamente = true;
                ultimaSincronizacion = millis();
            } else {
                Serial.println("No se pudo obtener hora. Reintentando en 3 horas.");
                sincronizadoExitosamente = false;
                ultimaSincronizacion = millis();
            }
        } else {
            Serial.println("Sin Wi-Fi. Saltando intento hasta el próximo ciclo.");
            ultimaSincronizacion = millis();
        }
    }
}

int obtenerHora() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return -1; // Retorna -1 si no hay hora válida
    }
    return timeinfo.tm_hour;
}

int obtenerMinuto() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return -1; // Retorna -1 si no hay hora válida
    }
    return timeinfo.tm_min;
}
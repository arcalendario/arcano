#ifndef GESTION_TIEMPO_H
#define GESTION_TIEMPO_H

#include <Arduino.h>

// Inicializa la sincronización NTP al arrancar
void iniciarSincronizacionTiempo();

// Verifica si han pasado 3 días y fuerza una actualización si es necesario
void verificarSincronizacionPeriodica();

// Obtiene la hora actual formateada
int obtenerHora();
int obtenerMinuto();

#endif
#ifndef CONTROL_WEB_H
#define CONTROL_WEB_H

#include <Arduino.h>

// Declaramos las variables como externas
extern int brillo;
extern int efectoElegido;
extern int indicePaleta;

void inicializarControlWeb();
void manejarPeticionesWeb();

#endif
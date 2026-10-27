#ifndef PALETAS_DE_COLORES_H
#define PALETAS_DE_COLORES_H
#include <Arduino.h>
#include <FastLED.h>

struct Paleta { CRGB color0, color1, color2, color3; };
void inicializarPaletas();
void setPaletaActiva(int id_paleta);
int obtenerPaletaActivaID();
Paleta obtenerColoresActuales();
void guardarPaletaPersonalizada(uint32_t c0, uint32_t c1, uint32_t c2, uint32_t c3);

#endif
#include "modo_espera.h"
#include "paletas_de_colores.h"

// Variables internas del efecto
static float factorFade = 0;
static bool subiendo = true;

extern CRGB leds[]; // Accedemos a la tira global definida en luces_led.cpp

void ejecutarModoEspera() {
    Paleta p = obtenerColoresActuales();
    CRGB colorInicio = p.color0;
    CRGB colorFin = p.color3;
    
    // Aplicamos el desvanecimiento
    for(int i = 0; i < 8; i++) {
        leds[i] = blend(colorInicio, colorFin, (uint8_t)factorFade);
    }
    FastLED.show();
    
    // Lógica de movimiento
    if (subiendo) factorFade += 0.5;
    else factorFade -= 0.5;
    
    if (factorFade >= 255) { factorFade = 255; subiendo = false; }
    if (factorFade <= 0) { factorFade = 0; subiendo = true; }
    
    delay(30); 
}
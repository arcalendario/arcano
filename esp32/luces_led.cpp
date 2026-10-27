#include <FastLED.h>
#include "luces_led.h"
#include "paletas_de_colores.h"
#include "control_web.h"

extern int brillo;
extern int efectoElegido;
extern int indicePaleta; 

#define NUM_LEDS 8
#define DATA_PIN 19
CRGB leds[NUM_LEDS];

void inicializarLeds() {
    // ACÁ ESTÁ LA MAGIA: Se agrega setCorrection(TypicalLEDStrip)
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(brillo); 
    FastLED.clear();
    FastLED.show();
}

void mostrarHoraEnLeds(Color m1, Color m2, Color m4, Color m8, Color h1, Color h2, Color h4, Color h8) {
    Paleta p = obtenerColoresActuales();
    CRGB mapa[4] = {p.color0, p.color1, p.color2, p.color3};
    CRGB objetivo[8] = {mapa[m1], mapa[m2], mapa[m4], mapa[m8], mapa[h1], mapa[h2], mapa[h4], mapa[h8]};

    // Lógica para Efecto Aleatorio (5)
    int effectToRun = efectoElegido;
    if (effectToRun == 5) {
        effectToRun = random(0, 5);
    }

    bool cambia[8];
    for(int i=0; i<8; i++) cambia[i] = (leds[i] != objetivo[i]);

    int paletaInicial = indicePaleta;
    int efectoInicial = efectoElegido;

    CRGB inicio[8];
    for(int i=0; i<8; i++) inicio[i] = leds[i];

    bool interrumpido = false; 
    
    auto pausaSuave = [&](int ms) {
        if (ms <= 0) return;
        unsigned long t = millis();
        while(millis() - t < (unsigned long)ms) {
            manejarPeticionesWeb();
            delay(1);
        }
    };

    // ==========================================
    // EFECTO 0: DESTELLO FLUIDO
    // ==========================================
    if (effectToRun == 0) { 
        for (int p = 0; p <= 255; p += 3) {
            manejarPeticionesWeb();
            if (efectoElegido != efectoInicial) { interrumpido = true; break; }
            for(int i=0; i<8; i++) if(cambia[i]) leds[i] = blend(inicio[i], CRGB::White, p);
            FastLED.show();
        }
        if (!interrumpido) {
            for (int p = 0; p <= 255; p++) {
                manejarPeticionesWeb(); 
                if (efectoElegido != efectoInicial) { interrumpido = true; break; }
                for (int i = 0; i < 8; i++) if(cambia[i]) leds[i] = blend(CRGB::White, objetivo[i], p);
                FastLED.show();
                pausaSuave(6); 
            }
        }
    } 
    // ==========================================
    // EFECTO 1: TRANSICIÓN A NEGRO (DRAMÁTICO)
    // ==========================================
    else if (effectToRun == 1) {
        for (int p = 0; p <= 255; p++) {
            manejarPeticionesWeb();
            if (efectoElegido != efectoInicial) { interrumpido = true; break; }
            for (int i = 0; i < 8; i++) if(cambia[i]) leds[i] = blend(inicio[i], CRGB::Black, p);
            FastLED.show();
            pausaSuave(5); 
        }
        
        if (!interrumpido) {
            pausaSuave(400); 

            for (int p = 0; p <= 255; p++) {
                manejarPeticionesWeb();
                if (efectoElegido != efectoInicial) { interrumpido = true; break; }
                for (int i = 0; i < 8; i++) if(cambia[i]) leds[i] = blend(CRGB::Black, objetivo[i], p);
                FastLED.show();
                pausaSuave(5); 
            }
        }
    }
    // ==========================================
    // EFECTO 2: TRANSICIÓN DIRECTA SUAVE (5 SEGUNDOS)
    // ==========================================
    else if (effectToRun == 2) { 
        for (int p = 0; p <= 255; p++) {
            manejarPeticionesWeb(); 
            if (efectoElegido != efectoInicial) { interrumpido = true; break; }
            for (int i = 0; i < 8; i++) if(cambia[i]) leds[i] = blend(inicio[i], objetivo[i], p);
            FastLED.show();
            pausaSuave(20); 
        }
    }
    // ==========================================
    // EFECTO 3: TITILACIÓN Y SINTONIZACIÓN (>2 SEGUNDOS)
    // ==========================================
    else if (effectToRun == 3) {
        for (int n = 0; n < 9; n++) {
            if (efectoElegido != efectoInicial) { interrumpido = true; break; }
            
            for (int i = 0; i < 8; i++) if(cambia[i]) leds[i] = inicio[i];
            FastLED.show();
            pausaSuave(120); 
            
            if (efectoElegido != efectoInicial) { interrumpido = true; break; }

            for (int i = 0; i < 8; i++) if(cambia[i]) leds[i] = objetivo[i];
            FastLED.show();
            pausaSuave(120); 
        }
    }
    // ==========================================
    // EFECTO 4: CAMBIO DIRECTO
    // ==========================================
    else if (effectToRun == 4) {
        // No se aplica animación
    }
    
    // Cierre y asignación de color final
    if (interrumpido && indicePaleta != paletaInicial) {
        Paleta p_nueva = obtenerColoresActuales();
        CRGB mapa_nuevo[4] = {p_nueva.color0, p_nueva.color1, p_nueva.color2, p_nueva.color3};
        CRGB objetivo_nuevo[8] = {mapa_nuevo[m1], mapa_nuevo[m2], mapa_nuevo[m4], mapa_nuevo[m8], mapa_nuevo[h1], mapa_nuevo[h2], mapa_nuevo[h4], mapa_nuevo[h8]};
        for(int i=0; i<8; i++) leds[i] = objetivo_nuevo[i];
    } else {
        for(int i=0; i<8; i++) leds[i] = objetivo[i];
    }
    FastLED.show(); 
}
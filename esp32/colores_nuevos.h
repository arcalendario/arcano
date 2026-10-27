#ifndef COLORES_NUEVOS_H
#define COLORES_NUEVOS_H

#include <Arduino.h>

// Definimos los 4 colores posibles
enum Color { 
    COLOR0 = 0, 
    COLOR1 = 1, 
    COLOR2 = 2, 
    COLOR3 = 3 
};

// Declaración de la función principal
void Colores_Nuevos(int hora, int minuto, 
                    Color &m1, Color &m2, Color &m4, Color &m8, 
                    Color &h1, Color &h2, Color &h4, Color &h8);

#endif
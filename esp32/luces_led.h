#ifndef LUCES_LED_H
#define LUCES_LED_H

#include "colores_nuevos.h" // Necesario para que reconozca el tipo de dato 'Color'

// Inicializa el hardware de la tira LED
void inicializarLeds();

// Toma las variables del reloj, consulta la paleta activa y enciende los LEDs físicos
void mostrarHoraEnLeds(Color m1, Color m2, Color m4, Color m8, 
                       Color h1, Color h2, Color h4, Color h8);

#endif
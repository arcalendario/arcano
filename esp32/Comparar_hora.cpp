/*
 * MÓDULO: Comparar_Hora
 * IMPLEMENTACIÓN: Lógica de detección de cambio de minuto mediante memoria estática.
 */

#include "comparar_hora.h"

// Variable "estática" que recordará el minuto de la vuelta anterior.
// La iniciamos en -1 para asegurarnos de que la primera vez que arranque 
// el reloj, detecte un "cambio" y encienda las luces inmediatamente.
static int ultimoMinutoRegistrado = -1;

bool verificarCambioMinuto(int minutoActual) {
    // Si el minuto que recibe es diferente al último que guardó...
    if (minutoActual != ultimoMinutoRegistrado) {
        
        // Actualiza el recuerdo para la próxima vuelta
        ultimoMinutoRegistrado = minutoActual; 
        
        // Dispara la alarma de que hubo un cambio
        return true; 
    }
    
    // Si el minuto es el mismo, devuelve falso (no hay que hacer nada)
    return false; 
}
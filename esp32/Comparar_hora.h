/*
 * MÓDULO: Comparar_Hora
 * FUNCIÓN: Actúa como "vigía" del sistema. 
 * Compara el minuto actual con el último minuto registrado para 
 * detectar cambios y disparar actualizaciones de la lógica de luces.
 * Evita el procesamiento innecesario constante.
 */

#ifndef COMPARAR_HORA_H
#define COMPARAR_HORA_H

// Función que verifica si el minuto acaba de cambiar
// Devuelve 'true' si cambió, y 'false' si seguimos en el mismo minuto.
bool verificarCambioMinuto(int minutoActual);

#endif
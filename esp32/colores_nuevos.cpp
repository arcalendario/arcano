#include "colores_nuevos.h"

// 1. TUS PESOS MATEMÁTICOS (La suma exacta del tiempo)
const int pesos1[] = {0, 1, 15, 16};  // Para M1 y H1
const int pesos2[] = {0, 2, 30, 32};  // Para M2 y H2
const int pesos4[] = {0, 4, 45, 49};  // Para M4 y H4
const int pesos8[] = {0, 8, 60, 68};  // Para M8 y H8

// 2. EL TRADUCTOR DE COLORES (El puente visual)
const Color mapa_M1[] = {COLOR0, COLOR1, COLOR2, COLOR3}; 
const Color mapa_M2[] = {COLOR0, COLOR1, COLOR2, COLOR3}; 
const Color mapa_M4[] = {COLOR0, COLOR1, COLOR2, COLOR3}; 
const Color mapa_M8[] = {COLOR0, COLOR1, COLOR2, COLOR3}; 

// =========================================================
// SISTEMA DE LOOKUP TABLE (GENERADA EN TIEMPO DE EJECUCIÓN)
// =========================================================

// Estructura para guardar la respuesta de cada número
struct Combinacion {
    int i, j, k, l;     // Los índices ganadores
    bool encontrada;    // Bandera para saber si existe solución
};

// Nuestro "cartón de respuestas" para los números del 0 al 59
Combinacion tabla_resultados[60];
bool tabla_lista = false; // Nos avisa si ya hicimos la tarea

// Función oculta que pre-calcula todo UNA SOLA VEZ al arrancar
void precalcularTabla() {
    // Primero, limpiamos la tabla por seguridad
    for (int x = 0; x < 60; x++) {
        tabla_resultados[x].encontrada = false;
    }

    // 1. Hacemos el trabajo pesado (los bucles matemáticos normales)
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    int suma = pesos1[i] + pesos2[j] + pesos4[k] + pesos8[l];
                    
                    // Si la suma nos sirve (entre 0 y 59) y no la habíamos guardado antes
                    if (suma >= 0 && suma < 60 && !tabla_resultados[suma].encontrada) {
                        tabla_resultados[suma].i = i;
                        tabla_resultados[suma].j = j;
                        tabla_resultados[suma].k = k;
                        tabla_resultados[suma].l = l;
                        tabla_resultados[suma].encontrada = true;
                    }
                }
            }
        }
    }

    // =========================================================
    // 2. TUS EXCEPCIONES Y REGLAS MANUALES
    // =========================================================
    // Aquí "pisamos" los resultados matemáticos con tus diseños a medida.
    // Recuerda: i=M1/H1, j=M2/H2, k=M4/H4, l=M8/H8
    // Los números representan el índice: 0=COLOR0, 1=COLOR1, 2=COLOR2, 3=COLOR3

    // Excepción para el número 15 (aplica igual para la hora 15 y el minuto 15):
    tabla_resultados[15].i = 2; // m1 / h1 = COLOR2 (Foco 1 y Foco 5)
    tabla_resultados[15].j = 0; // m2 / h2 = COLOR0 (Foco 2 y Foco 6)
    tabla_resultados[15].k = 0; // m4 / h4 = COLOR0
    tabla_resultados[15].l = 0; // m8 / h8 = COLOR0
    tabla_resultados[15].encontrada = true;

    // Marcamos que la tabla ya está lista para usarse siempre
    tabla_lista = true;
}

// =========================================================

// Función interna y privada (¡Ahora es instantánea!)
void calcular(int objetivo, Color &v1, Color &v2, Color &v4, Color &v8) {
    // Si es la primera vez que se llama a la función en todo el encendido, armamos la tabla
    if (!tabla_lista) {
        precalcularTabla();
    }

    // BUSCAMOS EN LA TABLA EN LUGAR DE CALCULAR
    if (objetivo >= 0 && objetivo < 60 && tabla_resultados[objetivo].encontrada) {
        v1 = mapa_M1[ tabla_resultados[objetivo].i ];
        v2 = mapa_M2[ tabla_resultados[objetivo].j ];
        v4 = mapa_M4[ tabla_resultados[objetivo].k ];
        v8 = mapa_M8[ tabla_resultados[objetivo].l ];
    } else {
        // Por seguridad, si llega un número raro, iniciamos todo apagado
        v1 = COLOR0;
        v2 = COLOR0;
        v4 = COLOR0;
        v8 = COLOR0;
    }
}

// Función principal que usarás en tu main.cpp
void Colores_Nuevos(int hora, int minuto, 
                    Color &m1, Color &m2, Color &m4, Color &m8, 
                    Color &h1, Color &h2, Color &h4, Color &h8) {
    
    // Calculamos las variables para los MINUTOS
    calcular(minuto, m1, m2, m4, m8);
    
    // Calculamos las variables para las HORAS
    calcular(hora, h1, h2, h4, h8);
}
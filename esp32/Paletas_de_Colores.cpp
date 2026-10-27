#include "paletas_de_colores.h"
#include <Preferences.h>

Preferences memoriaFlash;
// Aumentamos el tamaño de la lista a 8
Paleta listaDePaletas[8];
int paletaActivaID = 0;

void inicializarPaletas() {
    listaDePaletas[0] = {0xFFFF00, 0x00FF00, 0x0000FF, 0xFF0000};
    listaDePaletas[1] = {0xFF4500, 0xFF8C00, 0xFFD700, 0x8B008B};
    
    // PALETA 2 MODIFICADA (Blanco, Amarillo, Verde Musgo, Cian)
    listaDePaletas[2] = {0xFFFFFF, 0xFFFF00, 0x6B8E23, 0x00FFFF};
    
    listaDePaletas[3] = {0x006400, 0x228B22, 0x32CD32, 0x9ACD32};
    listaDePaletas[4] = {0x8A2BE2, 0xFF1493, 0x00FFFF, 0x0000CD};
    
    // PALETA 5 MODIFICADA (Blanco, Amarillo, Naranja, Rojo)
    listaDePaletas[5] = {0xFFFFFF, 0xFFFF00, 0xFF8C00, 0xFF0000};

    // TU NUEVA PALETA AGREGADA (Negro, Naranja, Amarillo, Blanco)
    listaDePaletas[6] = {0x000000, 0xFF8C00, 0xFFFF00, 0xFFFFFF};

    // La personalizada de la memoria flash pasa a ser la número 7
    memoriaFlash.begin("paleta_usr", false); 
    listaDePaletas[7].color0 = memoriaFlash.getUInt("c0", 0xFFFFFF);
    listaDePaletas[7].color1 = memoriaFlash.getUInt("c1", 0xFFFFFF);
    listaDePaletas[7].color2 = memoriaFlash.getUInt("c2", 0xFFFFFF);
    listaDePaletas[7].color3 = memoriaFlash.getUInt("c3", 0xFFFFFF);
    memoriaFlash.end();
}

void setPaletaActiva(int id_paleta) {
    // Ampliamos el límite de seguridad hasta 7
    if (id_paleta >= 0 && id_paleta <= 7) {
        paletaActivaID = id_paleta;
    }
}

int obtenerPaletaActivaID() {
    return paletaActivaID;
}

Paleta obtenerColoresActuales() {
    return listaDePaletas[paletaActivaID];
}

void guardarPaletaPersonalizada(uint32_t c0, uint32_t c1, uint32_t c2, uint32_t c3) {
    listaDePaletas[7].color0 = c0;
    listaDePaletas[7].color1 = c1;
    listaDePaletas[7].color2 = c2;
    listaDePaletas[7].color3 = c3;

    memoriaFlash.begin("paleta_usr", false);
    memoriaFlash.putUInt("c0", c0);
    memoriaFlash.putUInt("c1", c1);
    memoriaFlash.putUInt("c2", c2);
    memoriaFlash.putUInt("c3", c3);
    memoriaFlash.end();

    paletaActivaID = 7; 
}

void cambiarPaletaActiva(int nuevoIndice) {
    setPaletaActiva(nuevoIndice);
    Serial.print("Paleta cambiada a ID: ");
    Serial.println(nuevoIndice);
}
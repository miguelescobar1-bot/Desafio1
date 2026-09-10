#include "tablero.h"
#include <cstdlib>


unsigned char* ReservarMemoriaTablero(int filas, int columnas, int& bytesReservados) {
    bytesReservados = calcularBytesNecesarios(filas * columnas);
    unsigned char* buffer = new unsigned char[bytesReservados + 1];
    for (int i = 0; i <= bytesReservados; ++i)
        buffer[i] = 0;
    return buffer;
}

void inicializarTableroAleatorio(unsigned char* buffer, int filas, int columnas) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            guardarFicha(buffer, f, c, columnas, rand() % 6);
        }
    }
}

int calcularBytesNecesarios(int totalPosiciones) {
    int totalBits = totalPosiciones * 3;
    return (totalBits + 7) / 8;
}

void guardarFicha(unsigned char* buffer, int fila, int columna, int totalCols, unsigned char valor) {
    if (!buffer || fila < 0 || columna < 0) return;

    valor &= 0x07;
    int indice = fila * totalCols + columna;
    int bitInicial = indice * 3;
    int byteOrigen = bitInicial / 8;
    int offset = bitInicial % 8;

    if (offset <= 5) {
        unsigned char mascara = ~(0x07 << (5 - offset));
        buffer[byteOrigen] = (buffer[byteOrigen] & mascara) | (valor << (5 - offset));
    } else if (offset == 6) {
        buffer[byteOrigen] = (buffer[byteOrigen] & 0xFC) | (valor >> 1);
        buffer[byteOrigen + 1] = (buffer[byteOrigen + 1] & 0x7F) | ((valor & 0x01) << 7);
    } else {
        buffer[byteOrigen] = (buffer[byteOrigen] & 0xFE) | (valor >> 2);
        buffer[byteOrigen + 1] = (buffer[byteOrigen + 1] & 0x3F) | ((valor & 0x03) << 6);
    }
}

char fichaACaracter(unsigned char ficha) {
    switch (ficha) {
    case 0: return 'A';
    case 1: return 'B';
    case 2: return 'C';
    case 3: return 'D';
    case 4: return 'E';
    case 5: return 'F';
    case 6: return ' ';
    case 7: return '*';
    default: return '?';
    }
}

unsigned char obtenerFicha(const unsigned char* buffer, int fila, int columna, int totalCols) {
    if (!buffer || fila < 0 || columna < 0) return 0;

    int indice = fila * totalCols + columna;
    int bitInicial = indice * 3;
    int byteOrigen = bitInicial / 8;
    int offset = bitInicial % 8;

    if (offset <= 5) {
        return (buffer[byteOrigen] >> (5 - offset)) & 0x07;
    } else if (offset == 6) {
        unsigned char parte1 = (buffer[byteOrigen] & 0x03) << 1;
        unsigned char parte2 = (buffer[byteOrigen + 1] >> 7) & 0x01;
        return parte1 | parte2;
    } else {
        unsigned char parte1 = (buffer[byteOrigen] & 0x01) << 2;
        unsigned char parte2 = (buffer[byteOrigen + 1] >> 6) & 0x03;
        return parte1 | parte2;
    }
}


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

bool eliminarFichaUsuario(unsigned char* buffer, int filas, int columnas, int f, int c, int& fichasEliminadasTotal) {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) return false;

    unsigned char actual = obtenerFicha(buffer, f, c, columnas);

    if (actual != 6) {
        guardarFicha(buffer, f, c, columnas, 6);
        fichasEliminadasTotal++;


        aplicarGravedadYRellenar(buffer, filas, columnas);

        return true;
    }

    return false;
}

void aplicarGravedadYRellenar(unsigned char* buffer, int filas, int columnas) {
    for (int c = 0; c < columnas; ++c) {
        int posEscribir = filas - 1;
        for (int f = filas - 1; f >= 0; --f) {
            unsigned char ficha = obtenerFicha(buffer, f, c, columnas);
            if (ficha != 6) {
                guardarFicha(buffer, posEscribir, c, columnas, ficha);
                if (posEscribir != f) {
                    guardarFicha(buffer, f, c, columnas, 6);
                }
                posEscribir--;
            }
        }
        for (int f = posEscribir; f >= 0; --f) {
            guardarFicha(buffer, f, c, columnas, rand() % 6);
        }

    }
}

unsigned char* agregarFila(unsigned char* buffer, int& filas, int columnas, int posFila, int& bytesReservados) {
    int totalNuevas = (filas + 1) * columnas;
    int bytesNuevos = calcularBytesNecesarios(totalNuevas);

    unsigned char* nuevoBuffer = new unsigned char[bytesNuevos + 1];
    for (int i = 0; i <= bytesNuevos; ++i) nuevoBuffer[i] = 0;

    int filasNuevas = filas + 1;
    for (int f = 0; f < filasNuevas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            if (f < posFila) {
                guardarFicha(nuevoBuffer, f, c, columnas, obtenerFicha(buffer, f, c, columnas));
            } else if (f == posFila) {
                guardarFicha(nuevoBuffer, f, c, columnas, rand() % 6);
            } else {
                guardarFicha(nuevoBuffer, f, c, columnas, obtenerFicha(buffer, f - 1, c, columnas));
            }
        }
    }

    delete[] buffer;
    filas = filasNuevas;
    bytesReservados = bytesNuevos;
    return nuevoBuffer;
}

unsigned char* eliminarFila(unsigned char* buffer, int& filas, int columnas, int posFila, int& bytesReservados) {
    if (filas <= 1 || posFila < 0 || posFila >= filas) return buffer;

    int totalNuevas = (filas - 1) * columnas;
    int bytesNecesarios = calcularBytesNecesarios(totalNuevas);

    bool reasignar = ((double)bytesNecesarios / bytesReservados) < 0.65;
    unsigned char* destino = buffer;

    if (reasignar) {
        destino = new unsigned char[bytesNecesarios + 1];
        for (int i = 0; i <= bytesNecesarios; ++i) destino[i] = 0;
    }

    int filasNuevas = filas - 1;
    for (int f = 0; f < filasNuevas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            int fOrigen = (f < posFila) ? f : f + 1;
            guardarFicha(destino, f, c, columnas, obtenerFicha(buffer, fOrigen, c, columnas));
        }
    }

    if (reasignar) {
        delete[] buffer;
        bytesReservados = bytesNecesarios;
    }

    filas = filasNuevas;
    return destino;
}

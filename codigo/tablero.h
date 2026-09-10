#ifndef TABLERO_H
#define TABLERO_H

// Definicion de Funciones
// Funciones de creacion e inicializacion de tablero
unsigned char* ReservarMemoriaTablero(int filas, int columnas, int& bytesReservados);
int calcularBytesNecesarios(int totalPosiciones);
void inicializarTableroAleatorio(unsigned char* buffer, int filas, int columnas);

// Operaciones Tablero
unsigned char obtenerFicha(const unsigned char* buffer, int fila, int columna, int totalCols);
void guardarFicha(unsigned char* buffer, int fila, int columna, int totalCols, unsigned char valor);
char fichaACaracter(unsigned char ficha);

#endif // TABLERO_H

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
bool eliminarFichaUsuario(unsigned char* buffer, int filas, int columnas, int f, int c, int& fichasEliminadasTotal);
unsigned char* agregarFila(unsigned char* buffer, int& filas, int columnas, int posFila, int& bytesReservados);
unsigned char* eliminarFila(unsigned char* buffer, int& filas, int columnas, int posFila, int& bytesReservados);
unsigned char* eliminarColumna(unsigned char* buffer, int filas, int& columnas, int posCol, int& bytesReservados);
unsigned char* agregarColumna(unsigned char* buffer, int filas, int& columnas, int posCol, int& bytesReservados);

//Funciones de estado
void aplicarGravedadYRellenar(unsigned char* buffer, int filas, int columnas);
bool procesarCombinacionesYCascadas(unsigned char* buffer, int filas, int columnas, int& combinacionesDetectadas, int& cascadasTotal, int& fichasEliminadasTotal);


#endif // TABLERO_H

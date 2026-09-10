#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "juego.h"

int main() {
    srand(time(0));

    int filas = 6;
    int columnas = 6;
    int bytesReservados = 0;


    unsigned char* tablero = ReservarMemoriaTablero(filas, columnas, bytesReservados);
    inicializarTableroAleatorio(tablero, filas, columnas);


    int opcion = -1;
    while (opcion != 0) {
        mostrarTableroConsola(tablero, filas, columnas);

        std::cout << "\n--- ESTADISTICAS DEL JUEGO ---\n";
        std::cout << "Dimensiones: " << filas << "x" << columnas << "\n";
        std::cout << "Memoria Fisica Reservada: " << bytesReservados << " bytes\n";

        mostrarMenu();
        std::cin >> opcion;

        if (opcion == 1) { // Eliminar Ficha
            // Provision, Pendiente por terminar.
            std::cout << "En desarrollo, Provisional.";
        }
        else if (opcion == 2) { // AGREGAR FILA
            // Provision, Pendiente por terminar.
            std::cout << "En desarrollo, Provisional.";
        }
        else if (opcion == 3) { // ELIMINAR FILA
            // Provision, Pendiente por terminar.
            std::cout << "En desarrollo, Provisional.";
        }
        else if (opcion == 4) { // AGREGAR COLUMNA
            // Provision, Pendiente por terminar.
            std::cout << "En desarrollo, Provisional.";
        }
        else if (opcion == 5) { // ELIMINAR COLUMNA
            // Provision, Pendiente por terminar.
            std::cout << "En desarrollo, Provisional.";
        }
        break ; // Provisional, Pendiente desarrollo.
    }

    delete[] tablero;
    return 0;
}
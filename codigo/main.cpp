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

    int eliminacionesUsuario = 0;
    int fichasEliminadasTotal = 0;
    int combinacionesDetectadas = 0;
    int cascadasTotal = 0;


    unsigned char* tablero = ReservarMemoriaTablero(filas, columnas, bytesReservados);
    inicializarTableroAleatorio(tablero, filas, columnas);

    procesarCombinacionesYCascadas(tablero, filas, columnas, combinacionesDetectadas, cascadasTotal, fichasEliminadasTotal);
    combinacionesDetectadas = 0;
    cascadasTotal = 0;
    fichasEliminadasTotal = 0;


    int opcion = -1;
    while (opcion != 0) {
        mostrarTableroConsola(tablero, filas, columnas);

        std::cout << "\n--- ESTADISTICAS DEL JUEGO ---\n";
        std::cout << "Las dimensiones del Tablero son: " << filas << "x" << columnas << "\n";
        std::cout << "La Memoria Fisica Reservada del programa es: " << bytesReservados << " bytes\n";
        std::cout << "Fichas eliminadas por el Usuario: " << eliminacionesUsuario << "\n";
        std::cout << "Total Fichas Eliminadas: " << fichasEliminadasTotal << "\n";
        std::cout << "Combinaciones Detectadas: " << combinacionesDetectadas << "\n";
        std::cout << "Cascadas Producidas: " << cascadasTotal << "\n";
        std::cout << "Puntuacion Actual: " << (fichasEliminadasTotal * 10 + cascadasTotal * 50) << "\n";

        mostrarMenu();
        std::cin >> opcion;

        if (opcion == 1) { // Eliminar Ficha
            int f, c;
            std::cout << "Ingrese Fila y Columna a eliminar: ";
            std::cin >> f >> c;

            if (eliminarFichaUsuario(tablero, filas, columnas, f, c, fichasEliminadasTotal)) {
                procesarCombinacionesYCascadas(tablero, filas, columnas, combinacionesDetectadas, cascadasTotal, fichasEliminadasTotal);
            } else {
                std::cout << "Coordenada invalida o casilla vacia.\n";
            }
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
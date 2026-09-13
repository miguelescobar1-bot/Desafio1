#include "juego.h"
#include "tablero.h"
#include <iostream>



void mostrarTableroConsola(const unsigned char* buffer, int filas, int columnas) {
    std::cout << "\n    ";
    for (int c = 0; c < columnas; ++c) std::cout << c << " ";
    std::cout << "\n   ";
    for (int i = 0; i < columnas * 2 + 1; ++i) std::cout << "-";
    std::cout << "\n";

    for (int f = 0; f < filas; ++f) {
        std::cout << f << " | ";
        for (int c = 0; c < columnas; ++c) {
            unsigned char ficha = obtenerFicha(buffer, f, c, columnas);
            std::cout << fichaACaracter(ficha) << " ";
        }
        std::cout << "|\n";
    }

    std::cout << "   ";
    for (int i = 0; i < columnas * 2 + 1; ++i) std::cout << "-";
    std::cout << "\n";
}



void mostrarMenu() {
    std::cout << "\n--- MENU PRINCIPAL ---\n";
    std::cout << "1. Eliminar ficha manualmente\n";
    std::cout << "2. Agregar Fila\n";
    std::cout << "3. Eliminar Fila\n";
    std::cout << "4. Agregar Columna\n";
    std::cout << "5. Eliminar Columna\n";
    std::cout << "0. Salir\n";
    std::cout << "Seleccione alguna de las opciones: ";
}
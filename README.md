# Sweet Candy — Desafío 1

Desarrollo del juego **Sweet Candy** en C++ para la asignatura Informática II. El enfoque principal del proyecto es la gestión eficiente de la memoria dinámica en el *heap* y el manejo de datos mediante operaciones a nivel de bits.


## ¿Como plantee la solucion para el Desafio1?

* **Memoria lineal (sin matrices):** Todo el tablero lo manejo en un único puntero dinámico (`unsigned char*`) en el heap.
* **Empaquetado a 3 bits:** Como solo necesitaba 8 estados por casilla, determiné que 3 bits eran suficientes. El cálculo de los bytes requeridos lo hago con la fórmula `(totalBits + 7) / 8` para garantizar que no queden bits por fuera.
* **Reutilización del Heap (Criterio del 65%):** Cuando se eliminan filas o columnas, solo reasigno memoria si los nuevos bytes requeridos son menores al 65% de lo que ya tenía reservado, evitando la fragmentación de la RAM.
* **Operaciones Bitwise:** Para leer y escribir fichas en el tablero utilizo máscaras binarias y desplazamientos (`&`, `|`, `<<`, `>>`).


## Organizacion del repositorio

* `codigo/`: Archivos fuente del programa (`main.cpp`, `tablero.cpp`, `tablero.h`, `juego.cpp`, `juego.h` y `CMakeLists.txt`).
* `archivos_soporte/`: Informes técnicos, preinforme y tablas de memoria.


## Video de Presentacion del Desafio1

Acá explico el código fuente, la arquitectura de memoria y la demostración de funcionamiento:

[**Ver Video del Desafío 1**](https://youtu.be/04ZehpTAhi8)

**Autor:** Miguel Ángel Escobar Blair  
**C.C.** 1001369742
**Universidad de Antioquia**

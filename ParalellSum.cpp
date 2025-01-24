#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <omp.h>

int main() {
    const int SIZE = 1000;
    int arreglo1[SIZE], arreglo2[SIZE], suma[SIZE];

    // Semilla para generar números aleatorios
    srand(time(0));

    // Inicialización de los arreglos con valores aleatorios
    for (int i = 0; i < SIZE; ++i) {
        arreglo1[i] = rand() % 1000 + 1; // Valores entre 1 y 1000
        arreglo2[i] = rand() % 1000 + 1; // Valores entre 1 y 1000
    }

    // Paralelización con OpenMP
#pragma omp parallel num_threads(2)
    {
        int id = omp_get_thread_num();
        if (id == 0) {
            // Primer hilo: suma los primeros 500 elementos
            for (int i = 0; i < SIZE / 2; ++i) {
                suma[i] = arreglo1[i] + arreglo2[i];
            }
        }
        else if (id == 1) {
            // Segundo hilo: suma los últimos 500 elementos
            for (int i = SIZE / 2; i < SIZE; ++i) {
                suma[i] = arreglo1[i] + arreglo2[i];
            }
        }
    }

    // Imprimir los arreglos
    std::cout << "Arreglo 1:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << "arreglo1[" << i << "] = " << arreglo1[i] << std::endl;
    }

    std::cout << "\nArreglo 2:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << "arreglo2[" << i << "] = " << arreglo2[i] << std::endl;
    }

    std::cout << "\nResultado de la suma:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << "suma[" << i << "] = " << suma[i] << std::endl;
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  // Bibliotecas correctas

#define N 100000000

int main() {
    int *array = (int*)malloc(N * sizeof(int));
    long long sum = 0;

    // Inicialización del arreglo
    for (int i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    double start_time = omp_get_wtime();  // Nombre correcto

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += array[i];
    }

    double end_time = omp_get_wtime();  // Nombre correcto

    printf("Suma total: %lld\n", sum);
    printf("Tiempo con %d hilos: %f segundos\n", omp_get_max_threads(), end_time - start_time);  // Nombre correcto

    free(array);
    return 0;
}

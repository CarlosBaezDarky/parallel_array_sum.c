#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 100000000  // Tamaño del arreglo
#define NUM_THREADS 4 // Número de hilos

// Estructura para pasar datos a los hilos
typedef struct {
    int* array;
    long long start;
    long long end;
    long long partial_sum;
} ThreadData;

// Función que cada hilo ejecutará
void* sum_part(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_sum = 0;

    for (long long i = data->start; i < data->end; i++) {
        data->partial_sum += data->array[i];
    }

    return NULL;
}

int main() {
    int* array = (int*)malloc(N * sizeof(int));
    long long total_sum = 0;
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Inicialización del arreglo
    for (long long i = 0; i < N; i++) {
        array[i] = i + 1;
    }

    // Medición de tiempo
    clock_t start_time = clock();

    // Creación de hilos
    long long chunk_size = N / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].array = array;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, sum_part, &thread_data[i]);
    }

    // Espera a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    // Medición de tiempo
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Resultados
    printf("Suma total: %lld\n", total_sum);
    printf("Tiempo de ejecución con %d hilos: %.3f segundos\n", NUM_THREADS, elapsed_time);

    free(array);
    return 0;
}

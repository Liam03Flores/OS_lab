#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 1000
#define BUFFER_SIZE 1000

int buffer_index = 0;
int buffer[BUFFER_SIZE];

pthread_mutex_t lock;

void* write_buffer(void* arg) {
    pthread_mutex_lock(&lock);

    if (buffer_index < BUFFER_SIZE) {
        buffer[buffer_index] = 1;
        buffer_index++;
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {     // Crear hilos
        pthread_create(&threads[i], NULL, write_buffer, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {     // Esperar a todos los hilos
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Buffer:\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    return 0;
}
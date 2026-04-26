#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 10
#define MAX_CONNECTIONS 3

int active_connections = 0;

sem_t semaphore;

pthread_mutex_t lock;

void* access_database(void* arg) {
    sem_wait(&semaphore);        // Esperar permiso

    pthread_mutex_lock(&lock);

    active_connections++;
    printf("Conexiones activas: %d\n", active_connections);

    pthread_mutex_unlock(&lock);

    sleep(1);// Simular uso de la BD

    pthread_mutex_lock(&lock);

    active_connections--;
    printf("Conexión terminada. Activas: %d\n", active_connections);

    pthread_mutex_unlock(&lock);

    // Liberar permiso
    sem_post(&semaphore);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    sem_init(&semaphore, 0, MAX_CONNECTIONS);

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, access_database, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore);
    pthread_mutex_destroy(&lock);

    printf("Conexiones finales: %d\n", active_connections);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 1000

int account_a = 1000000;
int account_b = 1000000;

// Mutex para proteger recursos compartidos
pthread_mutex_t lock;

void* transfer(void* arg) {
    pthread_mutex_lock(&lock);  // Bloquear acceso

    account_a -= 1000;  // Sección crítica
    account_b += 1000;

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);    // Inicializar mutex

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, transfer, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {    // Esperar a que todos terminen (join)
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);  


    printf("Account A: %d\n", account_a);
    printf("Account B: %d\n", account_b);

    return 0;
}
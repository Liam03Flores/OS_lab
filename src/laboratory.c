#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int valor = 1;
int turno_par = 0; 

pthread_mutex_t bloqueo;
pthread_cond_t condicion;

// Hilo números impares
void* hiloImpar(void* arg){
    while (1){
        pthread_mutex_lock(&bloqueo);

        while (turno_par == 1)
            pthread_cond_wait(&condicion, &bloqueo);

        if (valor > 100) {
            pthread_mutex_unlock(&bloqueo);
            break;
        }

        printf("Impar: %d\n", valor);
        valor++;

        turno_par = 1;

        pthread_cond_signal(&condicion);
        pthread_mutex_unlock(&bloqueo);
    }
    pthread_exit(NULL);
}

// Hilo números pares
void* hiloPar(void* arg){
    while (1){
        pthread_mutex_lock(&bloqueo);

        while (turno_par == 0)
            pthread_cond_wait(&condicion, &bloqueo);

        if (valor > 100) {
            pthread_mutex_unlock(&bloqueo);
            break;
        }

        printf("Par: %d\n", valor);
        valor++;

        turno_par = 0;

        pthread_cond_signal(&condicion);
        pthread_mutex_unlock(&bloqueo);
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t h_impar, h_par;

    pthread_mutex_init(&bloqueo, NULL);
    pthread_cond_init(&condicion, NULL);

    pthread_create(&h_impar, NULL, hiloImpar, NULL);
    pthread_create(&h_par, NULL, hiloPar, NULL);

    pthread_join(h_impar, NULL);
    pthread_join(h_par, NULL);

    pthread_mutex_destroy(&bloqueo);
    pthread_cond_destroy(&condicion);

    return 0;
}
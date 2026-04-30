#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int llave_1 = 0;
int llave_2 = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_key_1, cond_key_2;

void* activar_llave1(void* arg){
    pthread_mutex_lock(&mutex);

    llave_1 = 1;
    printf("Llave 1 activada (valor = 1)\n");

    pthread_cond_signal(&cond_key_2);    // Notifica al consumidor que ya puede continuar

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

// Hilo que activa la llave 2 (consumidor)
void* activar_llave2(void* arg){
    pthread_mutex_lock(&mutex);

    while (llave_1 == 0){    // Espera hasta que llave_1 sea 1
        pthread_cond_wait(&cond_key_2, &mutex);
    }

    llave_2 = 1;
    printf("Llave 2 activada (valor = 1)\n");

    
    pthread_cond_signal(&cond_key_1);// señal por simetría

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(){
    pthread_t hilo1, hilo2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_key_1, NULL);
    pthread_cond_init(&cond_key_2, NULL);

    pthread_create(&hilo1, NULL, activar_llave1, NULL);
    pthread_create(&hilo2, NULL, activar_llave2, NULL);

    // Esperar a que terminen
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Verificación final
    if (llave_1 == 1 && llave_2 == 1){
        printf("Ambas llaves están activadas. El cohete se lanza \n");
    }

    pthread_mutex_destroy(&mutex);    // Liberación de recursos
    pthread_cond_destroy(&cond_key_1);
    pthread_cond_destroy(&cond_key_2);

    return 0;
}
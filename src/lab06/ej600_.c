#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NO 10

void *print_impar( void *args ){ 
    printf("Soy un hilo impar.\n");
    pthread_exit( NULL );
}

void *print_par( void *args ){
    printf("Soy un hilo par.\n");
    pthread_exit( NULL );
}

int main(){
    pthread_t threads[THREADS_NO];
    int state, i;      

    for(i=0; i < THREADS_NO; i++) {
        //printf("Hilo %d.\t", i);  
        if(i == 0) {
            printf("Soy 0 JAJA.\n");
        } else if(i % 2 == 0) {
            pthread_create( &threads[i], NULL, print_par, NULL );
        } else if(i % 2 != 0) {
            pthread_create( &threads[i], NULL, print_impar, NULL );
        }
    }

    for(i=0; i < THREADS_NO; i++) {
        pthread_join( threads[i], NULL );
    }

    return(0);
}

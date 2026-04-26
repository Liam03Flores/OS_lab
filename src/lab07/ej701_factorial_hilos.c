#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

int var1 = 0, var2 = 0, var3 = 0;
int numero = 3;
int res1 = 1, res2 = 1, res3 = 1;
void *thread1_Function(void *arg){
    int *var1 = (int *)arg;   // convertir el void* a int*
    for (int i = 1; i <= *var1; i++) {
        printf("%d * %d\t", res1, i);
        res1 = res1 * i;
        printf("= %d\t\t", res1);
    }
    printf("res1 = %d\n", res1);
    pthread_exit( NULL );
}

void *thread2_Function(void *arg){
    int *var2 = (int *)arg;
    for (int i = (*var2/2)+1; i <= *var2; i++) {
        printf("%d * %d\t", res2, i);
        res2 = res2 * i;
        printf("= %d\t\t", res2);
    }  
    printf("res2 = %d\n", res2);
    pthread_exit( NULL );
}

void *thread3_Function(void *arg){
    int *var3 = (int *)arg;
    for (int i = ((*var3/3)*2)+1; i <= *var3; i++) {
        printf("%d * %d\t", res3, i);
        res3 = res3 * i;
        printf("= %d\t\t", res3);
    }
    printf("res3 = %d\n", res3);
    pthread_exit( NULL );
}

int main() {

    printf("Ingrese un número divisible entre 3:\t");
    scanf("%d", &numero);
    while (numero % 3 != 0) {
        printf("El número ingresado no es divisible entre 3. Vuelve a intentarlo:\t");
        scanf("%d", &numero);
    }
    var1 = numero / 3;
    var2 = var1 * 2;
    var3 = var1 * 3;

        pthread_t thread1, thread2, thread3;
        pthread_create( &thread1, NULL, thread1_Function, &var1 );
        pthread_create( &thread2, NULL, thread2_Function, &var2 );
        pthread_create( &thread3, NULL, thread3_Function, &var3 );
        pthread_join( thread1, NULL ); //el hilo principal espera a que el hilo termine su ejecución
        pthread_join( thread2, NULL );
        pthread_join( thread3, NULL );
        printf( "Los hilos han terminado.\n" );
 
        printf("El resultado de %d! es: %d\n", numero, res1*res2*res3);
    return 0;
}
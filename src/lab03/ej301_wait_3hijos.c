#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>    // Para time()

int main() {
    srand(time(NULL));
    int numero_random = rand();
                                    //Cuando haces fork(), los hijos heredan la misma memoria del padre, incluyendo el valor de numero_random.
    pid_t pid;
    int status;
    pid_t A, B, M;

    printf("Inicio del proceso Q -> PID: %d | Proceso padre: %d\n", getpid(), getppid());
    A = fork();
    if (A == 0) {
        printf("Proceso A -> PID: %d | Padre: %d\t", getpid(), getppid()); 
        printf("Número aleatorio: %d\n", numero_random); 
    } 
    B = fork();
    if (B == 0) {
        printf("Proceso B -> PID: %d | Padre: %d\t", getpid(), getppid()); 
        printf("Número aleatorio: %d\n", numero_random); 
    }
    M = fork();
    if (M == 0) {
        printf("Proceso M -> PID: %d | Padre: %d\t", getpid(), getppid()); 
        printf("Número aleatorio: %d\n", numero_random);     
    }
        }
    
    for (int i = 0; i < 3; i++) {
        pid_t child_pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Mi hijo con PID %d terminó con el estado: %d.\n", child_pid, WEXITSTATUS(status));
        }
    }

    return 0;
}
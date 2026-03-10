#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>    // Para time()

int main() {
    srand(time(NULL));
    int numero_random = rand();

    pid_t pid;
    int status;
    pid_t A, B, M;
    int correctos = 0;

    printf("Inicio del proceso Q -> PID: %d | Proceso padre: %d\n", getpid(), getppid());

    A = fork();
    if (A == 0) {
        printf("Proceso A -> PID: %d | Padre: %d\t", getpid(), getppid()); 
        printf("Número aleatorio: %d\n", numero_random); 
        exit(0);   // ← termina el hijo A
    } 
    else {
        B = fork();
        if (B == 0) {
            printf("Proceso B -> PID: %d | Padre: %d\t", getpid(), getppid()); 
            printf("Número aleatorio: %d\n", numero_random); 
            exit(0);   // ← termina el hijo B
        }
        else {
            M = fork();
            if (M == 0) {
                printf("Proceso M -> PID: %d | Padre: %d\t", getpid(), getppid()); 
                printf("Número aleatorio: %d\n", numero_random);
                exit(0);   // ← termina el hijo M
            }
        }
    }

    // Solo el padre llega aquí
    for (int i = 0; i < 3; i++) {
        pid_t child_pid = wait(&status);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);

            printf("Mi hijo con PID %d terminó con el estado: %d.\n", child_pid, exit_status);

            if (exit_status == 0) {
                correctos++;
            }
        }
    }

    printf("Número de hijos que terminaron correctamente: %d\n", correctos);

    return 0;
}
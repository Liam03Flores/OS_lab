#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t A, B, M;
    int status;

    printf("Inicio del proceso Q -> PID: %d | Proceso padre: %d\n", getpid(), getppid());
    A = fork();
    if (A == 0) {
        printf("Proceso A -> PID: %d | Padre: %d\n", getpid(), getppid());
        sleep(10);
        return 10;
    }
    B = fork();
    if (B == 0) {
        printf("Proceso B -> PID: %d | Padre: %d\n", getpid(), getppid());
        return 0;
    }
    M = fork();
    if (M == 0) {
        printf("Proceso M -> PID: %d | Padre: %d\n", getpid(), getppid());
        sleep(3);
        return 3;
    }

    waitpid(M, &status, 0);
    printf("El proceso M ha terminado con el status: %d\n", WEXITSTATUS(status));
    waitpid(A, &status, 0);
    printf("El proceso A ha terminado con el status: %d\n", WEXITSTATUS(status));
    waitpid(B, &status, 0);
    printf("El proceso B ha terminado con el status: %d\n", WEXITSTATUS(status));

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t T, W, V, S, L, P;

    printf("Inicio del proceso R -> PID: %d | Proceso padre: %d\n", getpid(), getppid());

    T = fork();

    if (T == 0) {

        printf("Proceso T creado -> PID: %d | Padre: %d\n", getpid(), getppid());

        V = fork();

        if (V == 0) {
            printf("Proceso V en ejecución -> PID: %d | Padre: %d\n", getpid(), getppid());
        }

    }
    else {

        W = fork();

        if (W == 0) {

            printf("Proceso W activo -> PID: %d | Padre: %d\n", getpid(), getppid());

            S = fork();

            if (S == 0) {

                printf("Proceso S iniciado -> PID: %d | Padre: %d\n", getpid(), getppid());

                L = fork();

                if (L == 0) {

                    printf("Proceso L generado -> PID: %d | Padre: %d\n", getpid(), getppid());

                    P = fork();

                    if (P == 0) {
                        printf("Proceso P ejecutándose -> PID: %d | Padre: %d\n", getpid(), getppid());
                    }
                }
            }
        }
    }

    return 0;
}
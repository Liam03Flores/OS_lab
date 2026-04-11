#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void handlerUSR1(int s) {
    printf("Señal SIGUSR1 recibida. PID: %d | Padre: %d\n", getpid(), getppid());
}

void handlerUSR2(int s) {
    printf("Señal SIGUSR2 capturada. PID: %d | Padre: %d\n", getpid(), getppid());
}

void alarmaHandler(int s) {
    printf("Se activó la alarma\n");
}

int main() {

    pid_t hijoA, hijoC;

    hijoA = fork();

    if (hijoA == 0) {

        signal(SIGUSR1, handlerUSR1);

        hijoC = fork();

        if (hijoC == 0) {
            signal(SIGUSR2, handlerUSR2);
            pause();
            exit(0);
        }

        pause();
        sleep(1);
        kill(hijoC, SIGUSR2);

        wait(NULL);
        exit(0);
    }

    signal(SIGALRM, alarmaHandler);
    alarm(3);

    pause();

    sleep(1);
    kill(hijoA, SIGUSR1);

    wait(NULL);

    printf("Todos los procesos hijos finalizaron\n");

    return 0;
}
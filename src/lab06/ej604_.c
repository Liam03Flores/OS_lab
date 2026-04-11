#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void alarma(int s) {
    printf("Se recibió la señal de alarma\n");
}

int main() {

    pid_t hijoB, hijoC;

    hijoB = fork();

    if (hijoB == 0) {

        sleep(1);

        hijoC = fork();

        if (hijoC == 0) {
            while (1) {
                printf("En espera de señal...\n");
            }
        }

        sleep(1);
        kill(hijoC, SIGKILL);

        pause();
        exit(0);
    }

    signal(SIGALRM, alarma);
    alarm(5);

    wait(NULL);

    return 0;
}
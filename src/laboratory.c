#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void signal_handler_sigusr2(int signum) {
    for (int i = 0; i < 10; i++) {
        printf("%d,\n", i+1);
    }
}

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Proceso hijo
        signal(SIGUSR2, signal_handler_sigusr2);
        printf("Proceso hijo en espera de señales.\n");
        pause();
        exit(0);
    } 
    
    // Proceso padre
    sleep(1);
    printf("Enviando señal al proceso hijo.\n");
    kill(pid, SIGUSR2);
    wait(&status);

    return 0;
}

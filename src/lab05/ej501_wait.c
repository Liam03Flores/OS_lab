#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(){
    pid_t pid_L, pid_D;
    int status;
    //printf("Soy el proceso R, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());

    pid_L = fork();
    if (pid_L == 0){
        sleep(3);
        printf("Termine mi ejecución.\t\t\t");
        printf("Soy el proceso L, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
        exit(0);
    }

    pid_D = fork();
    if (pid_D == 0){
        sleep(1);
        printf("Termine mi ejecución.\t\t\t");
        printf("Soy el proceso D, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
        exit(0);
    }
    
    /*
    pid_t pid_ended = waitpid(-1, &status, 0); // espera a cualquier hijo
    if (pid_ended == -1) {
        perror("waitpid");
    } else {
        printf("El hijo con PID %d ha terminado.\t", pid_ended);
        if (WIFEXITED(status)) {
            printf("Terminó normalmente con código: %d\n", WEXITSTATUS(status));
            return 0;
            exit(0);
        }
    }
    */
    wait(&status);
        printf("Uno de mis hijos a terminado su ejecución.\n");
        return 0;
}
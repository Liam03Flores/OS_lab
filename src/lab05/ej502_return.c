#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(){
    pid_t pid_B, pid_C, pid_E;
    int status;

    pid_B = fork();
    if (pid_B == 0){
        sleep(3);
        return (1);
        exit(0);
    }

    pid_C = fork();
    if (pid_C == 0){
        sleep(1);
        return 2;
        exit(0);
    }
    
    pid_E = fork();
    if (pid_E == 0){
        return 3;
        exit(0);
    }

    waitpid(pid_B, &status, 0);
    printf("RETURN de Proceso B: %d\n", WEXITSTATUS(status));
    waitpid(pid_C, &status, 0);
    printf("RETURN de Proceso C: %d\n", WEXITSTATUS(status));
    waitpid(pid_E, &status, 0);
    printf("RETURN de Proceso E: %d\n", WEXITSTATUS(status));
    return 0;
}
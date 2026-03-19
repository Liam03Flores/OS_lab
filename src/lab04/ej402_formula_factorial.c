#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    pid_t pid_B, pid_C, pid_D;
    int status;
    int n = 5;
    int m = 3;
    printf("Soy el proceso A, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());

    int factorial(int x){
        int res = 1;
        for (int i = 1; i <= x; i++){
            res = res * i;
        }
        return res;
    }

    pid_B = fork();
    if (pid_B == 0){
        printf("Soy el proceso B, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
        sleep(2);
        int formula_A = factorial(n-m);
        return (formula_A);
    }
   pid_C = fork();
    if (pid_C == 0){
        printf("Soy el proceso C, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
        sleep(4);
        int formula_C = factorial(m);
        return (formula_C);
    }
       pid_D = fork();
    if (pid_D == 0){
        printf("Soy el proceso D, mi PID es %d y el PID de mi padre es %d.\n", getpid(), getppid());
        sleep(6);
        int formula_D = factorial(n);
        return (formula_D);
    }
    
    waitpid(pid_B, &status, 0);
    printf("El proceso B ha terminado con el status: %d\n", WEXITSTATUS(status));
    int valor_B = WEXITSTATUS(status);
    waitpid(pid_C, &status, 0);
    printf("El proceso C ha terminado con el status: %d\n", WEXITSTATUS(status));
    int valor_C = WEXITSTATUS(status);
    waitpid(pid_D, &status, 0);
    printf("El proceso D ha terminado con el status: %d\n", WEXITSTATUS(status));
    int valor_D = WEXITSTATUS(status);

    int resultado = valor_D/(valor_C*valor_B);
    printf("El resultado de la operación es: %d\n", resultado);

    return 0;
}
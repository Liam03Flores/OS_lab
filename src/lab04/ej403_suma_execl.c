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
    pid_t pid_A;
    int status;

    pid_A = fork();

    // Child process
    if (pid_A == 0)
    {
        execl("/workspaces/os_lab/src/suma", "0", "10", "20", "30", NULL);
        perror("execl ha fallado.");
    }   
    waitpid(pid_A, &status, 0);
    printf("El proceso ha terminado con el status: %d\n", WEXITSTATUS(status));
    int valor_A = WEXITSTATUS(status);

    return 0;
}
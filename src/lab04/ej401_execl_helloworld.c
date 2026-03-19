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
        execl("/workspaces/os_lab/src/hello_world", "hello_world", NULL);
        perror("execl ha fallado.");
        return 0;
    }   
    else
    {
        wait(&status);

        if (WEXITSTATUS(status) == 0)
        {
            printf("Mi hijo se ha ejecutado exitosamente.\n");
        }
    }

    return 0;
}

// EN OTRO .C, EJECUTADO PARA VOLVER UN EJECUTABLE

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/*void verificar_error(int valor, const char *operacion)
{
    if (valor < 0) {
        if (errno == EAGAIN) {
            printf("%s: Recurso temporalmente no disponible (EAGAIN)\n", operacion);
        } else if (errno == EACCES) {
            printf("%s: Permiso denegado (EACCES)\n", operacion);
        } else if (errno == EBADF) {
            printf("%s: Descriptor de archivo inválido (EBADF)\n", operacion);
        } else {
            perror(operacion);
        }
        exit(1);
    }
}*/

int main(){
    pid_t pid = -1;
    int x = 5, y = 10;

    pid = fork();

    //Código del hijo
    if (pid == 0){
        printf("Soy el hijo y mi pid = %d\n", getpid());
        exit(0);
    }

    //Código del padre (el hijo terminó en exit)
    printf("Soy el padre y mi pid = %d\n", getpid());

    return 0;
}
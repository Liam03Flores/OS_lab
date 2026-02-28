#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

void verificar_error(int valor, const char *operacion)
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
}

int main(){
    int fd;

    fd = creat("/archivo_prohibido.txt", 0666);
    verificar_error(fd, "creat");
}
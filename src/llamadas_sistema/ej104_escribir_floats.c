#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

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
    int fd, n;
    float valores[] = {10.5, 20.5, 30.5, 40.5, 50.5};

    fd = creat("datos2.txt", 0666);
    verificar_error(fd, "creat");

    for (int i = 0; i < 5; i++) {
        n = write(fd, &valores[i], sizeof(float));
        verificar_error(n, "write");
        printf("Bytes escritos: %d\n", n);
    }

    close(fd);
}
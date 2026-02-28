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

int main()
{
    int fd, n;
    float arreglo[] = {1.1, 2.2, 3.3, 4.4, 5.5};

    fd = open("datos.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666); //es lo mismo que creat pero para windows
    verificar_error(fd, "open");

    n = write(fd, arreglo, sizeof(arreglo));
    verificar_error(n, "write");

    printf("Bytes escritos: %d\n", n);

    close(fd);
    return 0;
}
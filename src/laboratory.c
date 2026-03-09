#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

void escribirDatos() {

    int datos[5] = {10, 20, 30, 40, 50};

    int fd = open("datos.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    write(fd, datos, sizeof(datos));

    close(fd);
}

void leerDatos() {

    int datos[5];

    int fd = open("datos.txt", O_RDONLY);

    read(fd, datos, sizeof(datos));

    close(fd);

    printf("Contenido leído del archivo:\n");

    for(int i = 0; i < 5; i++) {

        printf("Valor %d: %d\n", i+1, datos[i]);

    }
}

int main() {

    pid_t pid;

    pid = fork();

    if(pid == 0) {

        printf("Proceso M (hijo) escribiendo datos...\n");

        escribirDatos();

        exit(0);
    }

    else {

        sleep(3);

        printf("Proceso Q (padre) leyendo datos del archivo...\n");

        leerDatos();

    }

    return 0;
}
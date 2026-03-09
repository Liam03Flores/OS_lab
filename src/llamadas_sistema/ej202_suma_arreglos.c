#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


/* Función que revisa si ocurrió un error en una llamada al sistema */
void verificarError(int valor)
{
    if (valor < 0)
    {
        if (errno == EAGAIN)
        {
            printf("EAGAIN: el recurso solicitado no está disponible por ahora.\n");
        }
        else if (errno == EACCES)
        {
            printf("EACCES: no se tienen permisos para realizar la operación.\n");
        }
        else if (errno == EBADF)
        {
            printf("EBADF: el descriptor de archivo no es válido.\n");
        }
        else
        {
            perror("Se produjo un error del sistema");
        }

        exit(EXIT_FAILURE);
    }
}


/* Función que escribe números pares en el archivo N.txt */
void escribirPares()
{
    int arreglo[10] = {2,4,6,8,10,12,14,16,18,20};

    int fd = open("N.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    verificarError(fd);

    int n = write(fd, arreglo, sizeof(arreglo));
    verificarError(n);

    close(fd);
}


/* Función que escribe números impares en el archivo M.txt */
void escribirImpares()
{
    int arreglo[10] = {1,3,5,7,9,11,13,15,17,19};

    int fd = open("M.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    verificarError(fd);

    int n = write(fd, arreglo, sizeof(arreglo));
    verificarError(n);

    close(fd);
}


/* Función que lee ambos archivos y suma los arreglos */
void leerArreglo()
{
    int arregloM[10];
    int arregloN[10];
    int suma[10];
    int n;

    int fdN = open("N.txt", O_RDONLY);
    verificarError(fdN);

    n = read(fdN, arregloN, sizeof(arregloN));
    verificarError(n);

    close(fdN);


    int fdM = open("M.txt", O_RDONLY);
    verificarError(fdM);

    n = read(fdM, arregloM, sizeof(arregloM));
    verificarError(n);

    close(fdM);


    printf("\nResultado de la suma elemento por elemento:\n");

    for (int i = 0; i < 10; i++)
    {
        suma[i] = arregloN[i] + arregloM[i];

        printf("%d + %d produce %d\n",
               arregloN[i],
               arregloM[i],
               suma[i]);
    }
}



int main()
{
    pid_t pid_m, pid_n = -1;

    /* Primer proceso hijo */
    pid_m = fork();

    if (pid_m == 0)
    {
        escribirImpares();
        exit(0);
    }

    /* Segundo proceso hijo */
    pid_n = fork();

    if (pid_n == 0)
    {
        escribirPares();
        exit(0);
    }
    else
    {
        sleep(3);
        leerArreglo();
    }

    return 0;
}
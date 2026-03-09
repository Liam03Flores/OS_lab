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
			printf("%s: Recurso temporalmente no disponible (EAGAIN)\n",
				operacion);
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
	float arreglo[5];
	fd = open("datos.txt", O_RDONLY);
	verificar_error(fd, "open");
	n = read(fd, arreglo, sizeof(arreglo));
	verificar_error(n, "read");
	for (int i = 0; i < 5; i++) {
		printf("Valor %d: %.2f\n", i + 1, arreglo[i]);
	}
	close(fd);
}
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    int suma = 0;
	printf("El número de argumentos es: %d.\n", argc);

	for( int i=1; i<argc; i++ )	{
		printf("%d\t", atoi(argv[i]));
        suma += atoi(argv[i]);
        printf("suma=%d\n", suma);
	}
	
	return suma;	
}

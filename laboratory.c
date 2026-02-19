#include <stdio.h>

int factorial (int num1) {
    int resultado = 1;
    int aux = 0;

    for (int i = num1; i > 0; i--){
        printf("i => %d\t\t", i);
        aux = resultado * i;
        printf("%d = %d * %d\n", aux, resultado, i);
        resultado = aux;
    }

    return resultado;
}

int main (void) {
    int num1 = 0;
    
    printf("PROGRAMA PARA CONSEGUIR UN FACTORIAL\n");
    printf("Ingrese un número:\t");
    scanf("%d", &num1);

    
    printf("%d! = %d", num1, factorial(num1));
}
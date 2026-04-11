#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void manejadorAlarma(int signal){
    printf("Han pasado 3 segundos.\n");
}

int main(){
    // Asociar la señal SIGALRM con la función manejadora
    
    signal(SIGALRM, manejadorAlarma);

    // Programar la alarma para dentro de 3 segundos
    alarm(3);

    pause();

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>


#define NUM_ROWS 17
#define NUM_COLUMS 10

#define MAX_LEN_WORD 10
#define MAX_LEN_DESCRIPTION 100

char dashboard[NUM_ROWS][NUM_COLUMS];

typedef struct {
    char word[MAX_LEN_WORD];
    char description[MAX_LEN_DESCRIPTION];
} Word;

Word horizontal1[5] = {
    {"casa", "Lugar donde viven las personas."},
    {"cara", "Parte del cuerpo donde están los ojos, nariz y boca."},
    {"capa", "Prenda que se usa sobre la ropa, como la de los superhéroes."},
    {"cama", "Mueble donde duermes y descansas."},
    {"caza", "Actividad de buscar y atrapar animales."}
};

Word horizontal2[5] = {
    {"perro", "Animal doméstico que es conocido como el mejor amigo del hombre."},
    {"pacto", "Acuerdo entre dos o más personas."},
    {"pasto", "Planta verde que comen los animales como las vacas."},
    {"plato", "Utensilio donde se sirve la comida."},
    {"plomo", "Metal pesado de color gris."}
};

Word horizontal3[5] = {
    {"ganado", "Conjunto de animales criados en el campo, como vacas u ovejas."},
    {"pasado", "Tiempo que ya ocurrió antes del presente."},
    {"amparo", "Protección o ayuda que se le da a alguien."},
    {"zapato", "Calzado que se usa para cubrir el pie."},
    {"casado", "Persona que tiene matrimonio."}
};

Word vertical1[5] = {
    {"planta", "Ser vivo que crece en la tierra y no se mueve, como un árbol o una flor."},
    {"piedra", "Material duro que se encuentra en la naturaleza."},
    {"puerta", "Parte de una casa que sirve para entrar o salir."},
    {"prueba", "Evaluación para medir conocimientos o habilidades."},
    {"paloma", "Ave común de color blanco o gris."}
};

Word vertical2[5] = {
    {"barro", "Mezcla de tierra y agua que se vuelve blanda."},
    {"carro", "Vehículo con cuatro ruedas que sirve para transportarse."},
    {"barco", "Medio de transporte que navega por el agua."},
    {"jarro", "Recipiente usado para servir líquidos."},
    {"gallo", "Ave doméstica que canta al amanecer."}
};

Word vertical3[5] = {
    {"comino", "Semilla usada como condimento en la comida."},
    {"conejo", "Animal pequeño con orejas largas que salta."},
    {"tomate", "Fruta roja que se usa mucho en la comida."},
    {"sonido", "Vibración que se puede escuchar con los oídos."},
    {"modelo", "Representación o ejemplo que sirve como referencia."}
};

void handler_print_tablero(int s) {                     // Initialize matrix
    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < NUM_COLUMS; j++) {
            dashboard[i][j] = '0';
        }
    }
    for(int j = 5; j <= 8; j++) {               // Horizontal word 1 [length 4]
        dashboard[4][j] = '1';
    }
    for(int j = 2; j <= 6; j++) {               // Horizontal word 2 [length 5]
        dashboard[6][j] = '2';
    }    
    for(int j = 1; j <= 5; j++) {               // Horizontal word 3 [length 6]
        dashboard[11][j] = '3';
    } 
    for(int i = 1; i <= 6; i++) {               // Vertical word 1  [length 6]
        dashboard[i][6] = '4';
    }
    for(int i = 6; i <= 11; i++) {              // Vertical word 2  [length 5]
        dashboard[i][2] = '5';
    }    
    for(int i = 10; i <= 15; i++) {             // Vertical word 3 [length 6]
        dashboard[i][5] = '6';
    }
    for(int i = 0; i < NUM_ROWS; i++) {         // Print dashboard
        for(int j = 0; j < NUM_COLUMS; j++) {
            if(dashboard[i][j] == '0'){
                printf("%c\t", dashboard[i][j]);
            } else {
            printf("\033[1;33m%c\033[0m\t", dashboard[i][j]);   // \033[1;33m → activa bold + amarillo
            }   //printf("%c\t", dashboard[i][j]);
        }
        printf("\n");
    }

}
void handler_sigalrm(int sig) {
    if (sig == SIGALRM) {
        printf("\n⏰ Tiempo terminado para este turno!\n");
        printf("Pasando al siguiente periodo...\n\n");
    }
}

    int r1, r2, r3, r4, r5, r6;


int main() {
    srand(time(NULL));
    r1 = rand() % 5;  // valores entre 0 y 5
    r2 = rand() % 5;
    r3 = rand() % 5;
    r4 = rand() % 5;
    r5 = rand() % 5;
    r6 = rand() % 5;

    int num_word = 0;
    int periodo = 0;   // cuantos periodos de 30 seg va a tener el jugador

    char seleccionada[10];
    char buffer[10];
    char user_word[10];

    while (periodo < 10) {
        signal(SIGALRM, handler_sigalrm);
        alarm(40);
        printf("\t\t\t\tRandoms: r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, r6=%d\n\n", r1, r2, r3, r4, r5, r6);

        char *palabras[] = {
            horizontal1[r1].word, // num_word = 1
            horizontal2[r2].word, // num_word = 2
            horizontal3[r3].word, // num_word = 3
            vertical1[r4].word,   // num_word = 4
            vertical2[r5].word,   // num_word = 5
            vertical3[r6].word    // num_word = 6
        };

        signal(SIGUSR1, handler_print_tablero);
        kill(getpid(), SIGUSR1);
        printf("H1 (num_word=1): %s\n", horizontal1[r1].description);        // Prints para identificar cada palabra
        printf("H2 (num_word=2): %s\n", horizontal2[r2].description);
        printf("H3 (num_word=3): %s\n", horizontal3[r3].description);
        printf("V1 (num_word=4): %s\n", vertical1[r4].description);
        printf("V2 (num_word=5): %s\n", vertical2[r5].description);
        printf("V3 (num_word=6): %s\n", vertical3[r6].description);

        // char *descripciones[] = {
        //     horizontal1[r1].description,
        //     horizontal2[r2].description,
        //     horizontal3[r3].description,
        //     vertical1[r4].description,
        //     vertical2[r5].description,
        //     vertical3[r6].description,
        // };

        // for(int i = 0; i < n; i++) {
        //     pid_t pid = fork();   // crea un proceso hijo
        //     if(pid < 0) {
        //         perror("Error en fork");
        //         exit(1);
        //     }
        //     if(pid == 0) {
        //         printf("Soy el hijo %d con PID %d\n", i+1, getpid());
        //         exit(0); // el hijo termina aquí
        //     } else {
        //         wait(NULL); // Código del padre
        //     }
        // }

        printf("Ingrese el numero de la palabra\t");
        fgets(buffer, sizeof(buffer), stdin);
        num_word = atoi(buffer);

        while(num_word < 1 || num_word > 6) {
            printf("Número inválido. Ingrese un número entre 1 y 6:\t");
            fgets(buffer, sizeof(buffer), stdin);
            num_word = atoi(buffer);
        }
        strcpy(seleccionada, palabras[num_word-1]);

        printf("Ingrese una palabra:\t");
        fgets(user_word, sizeof(user_word), stdin);
        user_word[strcspn(user_word, "\n")] = '\0';

        if(strcmp(user_word, seleccionada) == 0){
            printf("\t\tLA PALABRA '%s' ES CORRECTA!\n", seleccionada);
            printf("\t\t\tSigue jugando!\n");
            kill(getpid(), SIGUSR1);
        } else {
            printf("Las palabras son diferentes. Vuelve a intentarlo\n");
            kill(getpid(), SIGUSR1);
        }

        periodo++;
    }

    return 0;
}

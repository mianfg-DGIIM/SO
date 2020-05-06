/**
 * @file lanzador.c
 * @brief Ejercicio 2.a - Examen 2013-02_inf
 * @author Miguel Ángel Fernández Gutiérrez <@mianfg>
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define FIFO_FILENAME ".canal"

int main( int argc, char* argv[] ) {
    char *archivo_1, *archivo_2;
    pid_t PID[2];
    int fd;
    char cadena[100];

    if ( argc == 3 ) {
        archivo_1 = argv[1];
        archivo_2 = argv[2];
        umask(0);
        if ( mkfifo(FIFO_FILENAME, 0666) < 0 ) {
            perror("\nError en mkfifo()");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Error en argumentos. Uso: ./lanzador <archivo_1> <archivo_2>\n");
        perror("\nError en argumentos");
        exit(EXIT_FAILURE);
    }

    PID[0] = fork();
    if (PID[0] != 0)
        PID[1] = fork();  // para que haga fork el padre
    
    if (PID[0] == 0) {
        // proceso hijo 1: analiza archivo_1
        execlp("./explorador", "explorador", archivo_1, FIFO_FILENAME, NULL);
    } else if (PID[1] == 0 ) {
        // proceso hijo 2: analiza archivo_2
        execlp("./explorador", "explorador", archivo_2, FIFO_FILENAME, NULL);
    } else {
        printf("Soy el padre\n");
        // proceso padre
        fd = open(FIFO_FILENAME, O_RDONLY);

        /*
         * DECISIÓN DE IMPLEMENTACIÓN:
         * he decidido que el programa analize el cambio en cada archivo una vez,
         * si cambian ambos archivos el programa para
         */

        int contador_cambios = 0;
        while ( contador_cambios < 2 ) {
            if ( read(fd, cadena, 100) ) {
                contador_cambios++;
                printf("Archivo modificado: %s", cadena);
            }
        }

        close(fd);
    }

    exit(EXIT_SUCCESS);
}
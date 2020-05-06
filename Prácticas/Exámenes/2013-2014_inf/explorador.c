/**
 * @file explorador.c
 * @brief Ejercicio 2 - Examen 2013-02_inf
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

int main( int argc, char* argv[] ) {
    char *archivo, *FIFO_filename;
    struct stat atributos, atributos_old;
    int fd;
    char cadena[100];
    if ( argc == 3 ) {
        archivo = argv[1];
        FIFO_filename = argv[2];
    } else {
        printf("Error en paso de argumentos por exec\n");
        perror("\nError en argumentos");
        exit(EXIT_FAILURE);
    }

    fd = open(FIFO_filename, O_WRONLY);

    int cambio = 0;
    if ( stat(archivo, &atributos) < 0 ) {
        perror("\nError en stat()");
        exit(EXIT_FAILURE);
    }
    while ( cambio == 0 ) {
        atributos_old = atributos;
        if ( stat(archivo, &atributos) < 0 ) {
            perror("\nError en stat()");
            exit(EXIT_FAILURE);
        }
        if ( atributos.st_mode != atributos_old.st_mode ) {
            sprintf(cadena, "%s %o\n", archivo, atributos.st_mode);
            if ( (write(fd, cadena, strlen(cadena)+1)) == strlen(cadena)+1 ) {
                cambio = -1;
            } else {
                perror("\nError en write() para explorador");
                exit(EXIT_FAILURE);
            }
        }
        sleep(1);  // para no hacer demasiadas comprobaciones
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
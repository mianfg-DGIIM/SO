/**
 * @file LeerDir.c
 * @brief Ejercicio 1 - Examen 2008-2009_inf
 * @author Miguel Ángel Fernández Gutiérrez <@mianfg>
 */

#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main( int argc, char *argv[] ) {
    DIR *dir_stream; struct dirent *dir;
    if ( argc != 2 ) {
        printf("Uso: ./LeerDir <num>\n");
        perror("\nError en argumentos");
        exit(EXIT_FAILURE);
    }
    int num = atoi(argv[1]);
    if ( num == 0 ) {
        printf("num es cero. ¡Bye! :)\n");
        exit(EXIT_SUCCESS);
    }

    if ( (dir_stream=opendir(".")) == NULL ) {
        perror("\nError en opendir()");
        exit(EXIT_FAILURE);
    }

    int contador = 0;
    while ( contador < num ) {
        dir=readdir(dir_stream);
        if ( dir == NULL ) {
            printf("Error: el número se ha pasado recorriendo\n");
            exit(EXIT_FAILURE);
        }
        contador++;
    }

    struct stat sa;
    if ( stat(dir->d_name, &sa) < 0 ) {
        perror("\nError en stat()");
        exit(EXIT_FAILURE);
    }
    
    printf("%s :\n   Inodo: %li\n   Tamaño (bytes): %li\n   Tipo de archivo y permisos: usar macros\n",
            dir->d_name, sa.st_ino, sa.st_size);

    exit(EXIT_SUCCESS);
}
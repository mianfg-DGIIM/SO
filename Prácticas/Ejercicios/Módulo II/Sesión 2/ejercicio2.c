/**
 * @file ejercicio2.c
 * @brief Ejercicio 2 - Módulo II, Sesión 2
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

int main(int argc, char *argv[]) {
    extern int errno;
    DIR *dir_stream;
    struct dirent *ed;
    struct stat atributos;
    char cadena[100];

    char *pathname;
    unsigned int permisos;

    if ( argc == 3 ) {
        pathname = argv[1];
        permisos = strtol(argv[2], NULL, 8);
        dir_stream = opendir(pathname);
        if ( dir_stream == NULL ) {
            perror("\nError en opendir()");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("\nUso: ./ejercicio2.c <pathname> <permisos>\n");
        exit(EXIT_FAILURE);
    }
    
    readdir(dir_stream);
    while ( (ed=readdir(dir_stream)) != NULL ) {
        sprintf(cadena, "%s/%s", pathname, ed->d_name);
        if ( stat(cadena, &atributos) < 0 ) {
            perror("Error en stat()\n");
            exit(EXIT_FAILURE);
        }
        if ( S_ISREG(atributos.st_mode) ) {
            printf("%s: %o ", cadena, atributos.st_mode);
            chmod(cadena, permisos);
            if (chmod(cadena, permisos) < 0) {
                printf("%s\n", strerror(errno));
            } else {
                if ( stat(cadena, &atributos) < 0 ) {
                    perror("Error en stat()\n");
                    exit(EXIT_FAILURE);
                }
                printf("%o\n", atributos.st_mode);
            }
        }
    }

    closedir(dir_stream);

    exit(EXIT_SUCCESS);
}
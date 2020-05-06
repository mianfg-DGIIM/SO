/**
 * @file micat.c
 * @brief Ejercicio 1 - Examen 2013-2014_infB3
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

int main( int argc, char* argv[] ) {
    int fd_source, fd_dest;
    int fd[2];
    char c;
    
    if ( argc != 3 ) {
        exit(EXIT_FAILURE);
    }

    if ( strcmp(argv[1], "-") != 0 ) {
        if ( (fd_source=open(argv[1], O_RDONLY, 0666)) < 0 ) {
            perror("\nError en open() para fuente");
            exit(EXIT_FAILURE);
        }
    } else {
        fd_source=STDIN_FILENO;
    }
    if ( strcmp(argv[2], "-") != 0 ) {
        if ( (fd_dest=open(argv[2], O_CREAT|O_WRONLY, 0666)) < 0 ) {
            perror("\nError en open() para destino");
            exit(EXIT_FAILURE);
        }
    } else {
        fd_dest=STDOUT_FILENO;
    }

    pipe(fd);

    switch(fork()) {
        case -1:
            exit(EXIT_FAILURE);
            break;
        case 0:
            // proceso hijo
            close(fd[0]);
            while ( (read(fd_source, &c, sizeof(char))) > 0 ) {
                write( fd[1], &c, sizeof(char) );
            }
            break;
        default:
            // proceso padre
            close(fd[1]);
            while ( (read(fd[0], &c, sizeof(char))) > 0 ) {
                write( fd_dest, &c, sizeof(char) );
            }
            break;
    }
}
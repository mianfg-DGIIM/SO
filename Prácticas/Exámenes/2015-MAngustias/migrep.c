/**
 * @file migrep.c
 * @brief Examen 2015-MAngustias
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

int contador = 0;

void sighandler(int signum) {
    printf("Proceso abortado. El contador tenía: %i\n", contador);
    kill(0, SIGKILL);
    exit(EXIT_FAILURE); // en caso de que no haga bien el SIGKILL
}

int main ( int argc, char *argv[] ) {
    char *literal, *ruta_directorio, pathname[200], ch;
    char buffer[10];
    struct stat atributos;
    int fd[2];
    DIR *dir_stream; struct dirent *dir;
    if ( argc != 3 ) {
        exit(EXIT_FAILURE);
    }
    
    literal = argv[1];
    ruta_directorio = argv[2];

    struct sigaction sa;

    sa.sa_handler = sighandler;

    if (sigaction(SIGINT, &sa, NULL) < 0){
        perror("Error en sigaction\n");
        exit(EXIT_FAILURE);
    }
    
    if ( (dir_stream=opendir(ruta_directorio)) == NULL ) {
        perror("\nError en opendir()");
        exit(EXIT_FAILURE);
    }

    while ( (dir=readdir(dir_stream)) != NULL ) {
        sprintf(pathname, "%s/%s", ruta_directorio, dir->d_name);
        if ( stat(pathname, &atributos) < 0 ) {
            perror("\nError en stat()");
            exit(EXIT_FAILURE);
        }
        if ( S_ISREG(atributos.st_mode) ) {
            pipe(fd);
            switch( fork() ) {
                case -1:
                    perror("\nError en fork()");
                    exit(EXIT_FAILURE);
                case 0:
                    close(fd[0]);
                    if ( dup2(fd[1], STDOUT_FILENO) < 0 ) {
                        perror("\nError en dup2()");
                        exit(EXIT_FAILURE);
                    }
                    execlp("grep", "grep", "-c", literal, pathname, NULL);
                    exit(EXIT_SUCCESS);
                default:
                    close(fd[1]);
                    int i = 0;
                    read(fd[0], buffer, 10);
                    contador += atoi(buffer);
                    break;
            }
        }
    }

    printf("Se ha leído %s: %i veces\n", literal, contador);
    exit(EXIT_SUCCESS);
}
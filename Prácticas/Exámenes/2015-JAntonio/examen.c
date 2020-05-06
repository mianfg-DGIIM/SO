/**
 * @file examen.c
 * @brief Examen 2015-JAntonio
 * @author Miguel Ángel Fernández Gutiérrez <@mianfg>
 */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define ARCHIVO_FIFO ".fifo"

void handler_SIGPIPE(int signum) {
    printf("Finalizado inesperadamente :(\n");
    exit(EXIT_FAILURE);
}

int main( int argc, char *argv[] ) {
    int fd;
    DIR *dir_stream; struct dirent *dir;
    struct stat atributos;
    char buffer[200] = ""; char ch;
    struct sigaction sa;

    // desactivamos búfer para printf
	setvbuf(stdout, NULL,_IONBF, 0);

    // ampliación 3: preparando cerrojo
	struct flock cerrojo;
	cerrojo.l_type = F_RDLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;

    unlink(".fifo");
    umask(0);
    mkfifo(".fifo", 0666);

    // ampliación 2: modificando handler ante SIGPIPE
    sa.sa_handler=handler_SIGPIPE;
    if ( sigaction(SIGPIPE, &sa, 0) < 0 ) {
        perror("\nError en sigaction()");
        exit(EXIT_FAILURE);
    }

    if ( (dir_stream=opendir(".")) < 0 ) {
        perror("\nError en opendir()");
        exit(EXIT_FAILURE);
    }

    switch ( fork() ) {
        case -1:
            perror("\nError en fork()");
            exit(EXIT_FAILURE);
        case 0:
            if ( (fd=open(ARCHIVO_FIFO, O_RDONLY)) < 0 ) {
                perror("\nError en open() para FIFO");
                exit(EXIT_FAILURE);
            }
            // ampliación 3: establecemos cerrojo
            fcntl(fd, F_SETLKW, &cerrojo);
            int i = 0;
            while ( read(fd, &ch, sizeof(char)) > 0 ) {
                buffer[i] = ch;
                i++;
                if ( ch == '\0' ) {
                    printf("Leído de FIFO: %s\n", buffer);
                    i=0;
                }
            }
            // ampliación 3: quitamos cerrojo
            cerrojo.l_type = F_UNLCK;
		    fcntl(fd, F_SETLKW, &cerrojo);
            close(fd);
            exit(EXIT_SUCCESS);
        default:
            if ( (fd=open(ARCHIVO_FIFO, O_WRONLY)) < 0 ) {
                perror("\nError en open() para FIFO");
                exit(EXIT_FAILURE);
            }
            while ( (dir=readdir(dir_stream)) != NULL ) {
                if ( stat(dir->d_name, &atributos) < 0 ) {
                    perror("\nError en stat()");
                    exit(EXIT_FAILURE);
                }
                if ( S_ISREG(atributos.st_mode) ) {
                    // ampliación 1: nos aseguramos que el archivo tiene permiso de lectura para usuario
                    if ( (atributos.st_mode & S_IRUSR) != S_IRUSR ) {
                        if ( chmod(dir->d_name, atributos.st_mode | S_IRUSR) ) {
                            perror("\nError en chmod()");
                            exit(EXIT_FAILURE);
                        }
                    }

                    printf("[%li] %i\n", atributos.st_ino, atributos.st_uid);
                    if ( write(fd, dir->d_name, strlen(dir->d_name)+1) != strlen(dir->d_name)+1 ) {
                        perror("\nError en write()");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            close(fd);
            break;
    }

    closedir(dir_stream);

    exit(EXIT_SUCCESS);
}
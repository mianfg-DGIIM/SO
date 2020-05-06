/**
 * @file conSoporte.c
 * @brief Ejercicio 1 - Examen 2013-02_infB2
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

int main() {
    char mempadre[60];

    int fd[2];
    char c;

    pipe(fd);

    switch(fork()) {
        case -1:    // ha habido algún error
            perror("\nError en fork()");
            exit(EXIT_FAILURE);
            break;
        case 0:     // proceso hijo
            close(fd[0]);
            close(STDOUT_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            sprintf(mempadre, "/proc/%d/maps", getppid());
            if (execlp("cat", "cat", mempadre, NULL) < 0) {
                perror("\nError en exec()");
                exit(EXIT_FAILURE);
            }
            break;
        default:    // proceso padre
            close(fd[1]);
            int deboescribir=0;
            while (read(fd[0], &c, sizeof(char)) == sizeof(char)) {
                if ( c == '/' )
                    deboescribir=1;
                if ( c == '\n' ) {
                    deboescribir=0;
                    printf("\n");
                }
                if (deboescribir)
                    printf("%c", c);
            }
            break;
    }

    exit(EXIT_SUCCESS);
}
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        perror("Error en número de argumentos\n");
        exit(-1);
    }

    pid_t PID;
    int fd[2];

    if (strcmp(argv[2], "|") == 0) {
        if ( pipe(fd) == -1 ) {
            perror("Error en pipe\n");
        }
        if ( (PID=fork()) < 0 ) {
            perror("Error en fork\n");
            exit(-1);
        }

        if (PID != 0) {
            // proceso padre
            close(1);
            close(fd[0]);
            if (fcntl(fd[1], F_DUPFD, 1) == -1) {
                perror("Error en fcntl\n");
                exit(-1);
            }
            execlp(argv[1], argv[1], NULL);
        } else {
            // proceso hijo
            close(0);
            close(fd[1]);
            if (fcntl(fd[0], F_DUPFD, 0) == -1) {
                perror("Error en fcntl\n");
                exit(-1);
            }
            execlp(argv[3], argv[3], NULL);
        }
    } else {
        perror("Ponme un \"|\" como segundo argumento andaaa...\n");
        exit(-1);
    }
}
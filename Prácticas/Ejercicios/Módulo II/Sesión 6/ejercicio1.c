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

    int fd;

    if (strcmp(argv[2], ">") == 0) {
        if ((fd=open(argv[3], O_WRONLY))<0) {
            perror("Error abriendo archivo\n");
            exit(-1);
        }
        close(1);
        if (fcntl(fd, F_DUPFD, 1) == -1) {
            perror("Error en fcntl\n");
            exit(-1);
        }
        execlp(argv[1], argv[1], NULL);
    } else if (strcmp(argv[2], "<") == 0) {
        if ((fd=open(argv[3], O_RDONLY))<0) {
            perror("Error abriendo archivo\n");
            exit(-1);
        }
        close(0);
        if (fcntl(fd, F_DUPFD, 0) == -1) {
            perror("Error en fcntl\n");
            exit(-1);
        }
        execlp(argv[1], argv[1], NULL);
    } else {
        perror("Debe insertar como segundo argumento \"<\" o \">\"\n");
        exit(-1);
    }
}
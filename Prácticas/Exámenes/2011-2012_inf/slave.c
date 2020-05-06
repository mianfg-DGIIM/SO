#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

int main() {
    DIR *dir_stream; struct dirent *dir;

    char indice_buffer[10], buffer[100], ch;
    int fd = open("FIFOs", O_WRONLY);

    // desactivamos búfer para printf
	setvbuf(stdout, NULL,_IONBF, 0);

    printf("HEHE\n");
    if ( fd < 0 ) {
        perror("\nError en open()");
        exit(EXIT_FAILURE);
    }

    if(read(STDIN_FILENO, indice_buffer, 10)<0){
		perror("read");
		exit(EXIT_FAILURE);
	}
    int indice = atoi(indice_buffer);

    printf("Acabo de leer %s = %i\n", indice_buffer, indice);


    if ( (dir_stream=opendir(".")) < 0 ) {
        perror("\nError en opendir()");
        exit(EXIT_FAILURE);
    }
    
    int i = 0;
    while ( i < indice ) {
        if ( (dir=readdir(dir_stream)) == NULL ) {
            printf("Se ha llegado al final del directorio y no se ha encontrado la posición %i\n", indice);
            exit(EXIT_FAILURE);
        }
        printf("i=%i, en %s\n", i, dir->d_name);
        i++;
    }

    struct stat atributos;
    if ( stat(dir->d_name, &atributos) < 0 ) {
        perror("\nError en stat()");
        exit(EXIT_FAILURE);
    }

    sprintf(buffer, "[%li] %li\n", atributos.st_ino, atributos.st_size);
    if (write(fd, buffer, strlen(buffer)) != strlen(buffer)) {
        perror("\nError en write()");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
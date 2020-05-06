/**
 * @file ejercicio2amp.c
 * @brief Ejercicio 2 (ampliación) - Módulo II, Sesión 1
 * @author Miguel Ángel Fernández Gutiérrez <@mianfg>
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void errorCheck(char error_msg[]) {
	if (errno!=0) {
		perror(error_msg);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
    extern int errno;
    int f_in, f_out;
    char buffer[80];
    char label[40];
    char salto[] = "\n\n";

    if (argc<2)
        f_in=STDIN_FILENO;
    else
        if ((f_in=open(argv[1], O_RDONLY))==-1) {
            perror("Error en open() para salida");
            exit(EXIT_FAILURE);
        }
    
    if((f_out=open("salida.txt", O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR))==-1) {
        perror("Error en open() para entrada");
        exit(EXIT_FAILURE);
    }

    int contador=0, longitud=0;
    while ((longitud=read(f_in, buffer, 80))>0)
        contador++;

    sprintf(label, "%s%i\n", "El número de bloques es ", contador);
    write(f_out, label, strlen(label));
    errorCheck("Error escribiendo\n");

    lseek(f_in, 0, SEEK_SET);
    errorCheck("Error en lseek()");

    contador=0; longitud=0;
    while ((longitud=read(f_in, buffer, 80))>0) {
        contador++;
        sprintf(label, "%s%i\n", "Bloque ", contador);
        write(f_out, label, strlen(label));
        write(f_out, buffer, longitud);
        write(f_out, salto, strlen(salto));
        errorCheck("Error escribiendo\n");  // forma de comprobar errores
    }

    close(f_in);
    close(f_out);
}
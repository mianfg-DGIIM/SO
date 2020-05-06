/**
 * @file ejercicio3.c
 * @brief Ejercicio 3 - Módulo II, Sesión 2
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

#define S_IFXGO 011
#define S_ISXGO(mode) ((((mode) & ~S_IFMT) & 011) == S_IFXGO)

void buscar_dir(DIR *direct_stream, char pathname[], int *reg, int *tamanio) {
	struct dirent *ed;
	struct stat atributos;
	DIR *direct_stream_act;
	char cadena[500];

	while ((ed=readdir(direct_stream))!=NULL) {
		if (strcmp(ed->d_name, ".")!=0 && strcmp(ed->d_name, "..")!= 0) {
			sprintf(cadena, "%s/%s", pathname, ed->d_name);
			if ( stat(cadena, &atributos) < 0 ) {
				perror("\nError accediendo a atributos en stat()");
				exit(EXIT_FAILURE);
			}
			if ( S_ISDIR(atributos.st_mode) ) {
				if ( (direct_stream_act=opendir(cadena)) == NULL ) {
					perror("\nError abriendo directorio con opendir()");
					exit(EXIT_FAILURE);
				} else {
					buscar_dir(direct_stream_act, cadena, reg, tamanio);
				}
			} else {
				if ( S_ISREG(atributos.st_mode) ) {
					if ( S_ISXGO(atributos.st_mode) ) {
						printf("%s %i\n", cadena, (int) atributos.st_ino);
						(*reg)++;
						(*tamanio) += (int) atributos.st_size;
					}
				}
			}
		}
	}
	closedir(direct_stream);
}


int main(int argc, char* argv[]) {
	DIR *direct_stream;
	char *pathname;
	char pathname_none[] = ".";
	int reg=0, tamanio=0;

	if ( argc == 2 ) {
		pathname = argv[1];
	} else {
		pathname = pathname_none;
	}

	if ((direct_stream=opendir(pathname))==NULL) {
		perror("\nError en opendir()");
		exit(EXIT_FAILURE);
	}


	printf("Los inodos son:\n");
	buscar_dir(direct_stream, pathname, &reg, &tamanio);
	printf("Existen %i archivos regulares con permiso x para grupo y otros\n", reg);
	printf("El tamaño total ocupado por dichos archivos es de %i bytes\n", tamanio);

	exit(EXIT_SUCCESS);
}
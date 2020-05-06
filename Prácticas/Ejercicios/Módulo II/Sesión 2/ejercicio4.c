/**
 * @file ejercicio4.c
 * @brief Ejercicio 4 - Módulo II, Sesión 2
 * @author Miguel Ángel Fernández Gutiérrez <@mianfg>
 */

#define _XOPEN_SOURCE 600

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#include <ftw.h>

#define S_IFXGO 011
#define S_ISXGO(mode) ((((mode) & ~S_IFMT) & 011) == S_IFXGO)

int reg=0, tamanio=0;

static int buscar(const char *pathname, const struct stat *statbuf, int unused, struct FTW *unused_2) {
	if (S_ISREG(statbuf->st_mode)) {
		if (S_ISXGO(statbuf->st_mode)) {
			reg++;
			tamanio += (int) statbuf->st_size;
			printf("[x] ");
		} else
			printf("[ ] ");
		printf("%s %ld \n", pathname, statbuf->st_ino);
	}
	return 0;
}

int main(int argc, char* argv[]) {
	char pathname[500];
	
	if (argc==2) {
		strcpy(pathname, argv[1]);
	} else {
		strcpy(pathname, ".");
	}
	
	printf("Los inodos son:\n");
	
	nftw(pathname, buscar, 10, 0);  // flags=0
	
	printf("Hay %d archivos regulares con permiso x para grupo y otros\n", reg);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n", tamanio);
	
	return 0;
}

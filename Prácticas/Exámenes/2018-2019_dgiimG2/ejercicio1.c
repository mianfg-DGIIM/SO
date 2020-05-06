/**
 * @file ejercicio1.c
 * @brief Ejercicio 1 - Examen 2018-2019_dgiimG2
 * @author Miguel Ángel Fernández Gutiérrez <@mianfg>
 */

#include<sys/types.h>	
#include<unistd.h>		
#include<sys/stat.h>
#include<fcntl.h>		
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<limits.h>

int main( int argc, char *argv[] ) {
	DIR *dir_stream; struct dirent *dir;
	struct stat atributos;
	char* nombre_directorio;
	char* home = getenv("HOME");
	printf("%s\n", home);
	int permisos, fd;

	if ( argc != 2 ) {
		printf("Uso: ./examen1 <nombre_directorio>\n");
		perror("\nError en argumentos");
		exit(EXIT_FAILURE);
	}
	nombre_directorio = argv[1];

	if ( (dir_stream=opendir(nombre_directorio)) == NULL ) {
		perror("\nError en opendir()");
		exit(EXIT_FAILURE);
	}

	char pathname[PATH_MAX];
	while ( (dir=readdir(dir_stream)) != NULL ) {
		sprintf(pathname, "%s/%s", nombre_directorio, dir->d_name);
		if ( stat(pathname, &atributos) < 0 ) {
			perror("\nError en stat()");
			exit(EXIT_FAILURE);
		}
		if ( S_ISREG(atributos.st_mode) && ((atributos.st_mode & S_ISUID)==S_ISUID) ) {
			permisos = atributos.st_mode;
			if ( chmod(pathname, atributos.st_mode | S_IROTH | S_IWOTH | S_IXOTH ) < 0 ) {
				perror("\nError en chmod()");
				exit(EXIT_FAILURE);
			}
			printf("%s [%li]\n", pathname, atributos.st_ino);
			sprintf(pathname, "%s/%s", home, dir->d_name);
			umask(0);
			if ( (fd=open(pathname, O_CREAT|O_RDWR, 0666)) < 0 ) {
				perror("\nError en open() para crear archivo");
				exit(EXIT_FAILURE);
			}
			if ( chmod(pathname, permisos) < 0 ) {
				perror("\nError en chmod()");
				exit(EXIT_FAILURE);
			}
			close(fd);
		}
	}

	closedir(dir_stream);
	exit(EXIT_SUCCESS);
}
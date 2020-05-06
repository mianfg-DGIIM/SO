/**
 * @file ejercicio2.c
 * @brief Ejercicio 2 - Examen 2018-2019_dgiimG2
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
#include<sys/wait.h>

#define TAMANIO 1024
#define NUM_EXECS 60

void action_handler(int signal) {
	wait(NULL);
	unlink(".comunica_fifo");
	printf("\nFinalizamos programa\n");
	kill(0, SIGTERM);
}

int main( int argc, char *argv[] ) {
	if ( argc != 2 ) {
		perror("\nError en argumentos");
		exit(EXIT_FAILURE);
	}

	char *nombre_directorio = argv[1];
	int estado;
	char buffer[TAMANIO], buffer_anterior[TAMANIO], buffer_break[] = "\n";
	struct sigaction sa;

	unlink(".comunica_fifo");
	umask(0);
	mkfifo(".comunica_fifo", 0666);
	
	int fd=open(".comunica_fifo", O_RDWR);
	if ( fd < 0 ) {
		perror("\nError en mkfifo()");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = action_handler;
	
	if ( sigaction(SIGINT, &sa, NULL) < 0 ) {
		perror("\nError en sigaction()");
		exit(EXIT_FAILURE);
	}

	int continuar=1;
	for ( int i = 0; i < NUM_EXECS && continuar; i++ ) {
		switch ( fork() ) {
			case -1:	// fallo en fork()
				perror("\nError en fork()");
				exit(EXIT_FAILURE);
				break;
			case 0:		// proceso hijo
				if ( dup2(fd, STDOUT_FILENO) < 0 ) {
					perror("\nError en dup2()");
					exit(EXIT_FAILURE);
				}
				execlp("ls", "ls", nombre_directorio, NULL);
				exit(EXIT_SUCCESS);
				break;
			default:	// proceso padre
				wait(&estado);
				if ( estado != EXIT_SUCCESS ) {
					perror("\nError de hijo. Programa abortado");
					exit(EXIT_FAILURE);
				}
				strcpy(buffer_anterior, buffer);
				if ( read(fd, buffer, TAMANIO) < 0 ) {
					perror("\nError en read()");
					exit(EXIT_FAILURE);
				}
				if ( write(STDOUT_FILENO, buffer, strlen(buffer)) != strlen(buffer) ) {
					perror("\nError en write()");
					exit(EXIT_FAILURE);
				}
				if ( write(STDOUT_FILENO, buffer_break, strlen(buffer_break)) != strlen(buffer_break) ) {
					perror("\nError en write()");
					exit(EXIT_FAILURE);
				}	

				if ( i>0 ) {
					if ( strcmp(buffer, buffer_anterior) != 0 ) {
						printf("Se han detectado cambios en ls. Abortando...\n");
						continuar = 0;
					}
				}
				break;
		}
		sleep(1);	// para dar tiempo a hacer modificaciones
	}

	close(fd);
	unlink(".comunica_fifo");

	exit(EXIT_SUCCESS);
}

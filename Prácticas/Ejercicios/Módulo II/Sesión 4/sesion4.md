## `SO`  `>`  Prácticas  `>`  Módulo II  `>`  Sesión 4

------

# Comunicación entre procesos utilizando cauces

> Prácticas de **Sistemas Operativos**
>
> Alumno: Miguel Ángel Fernández Gutiérrez
> Fecha: 3 de noviembre, 2018



------

## :pencil: Ejercicio 1

Consulte en el manual las llamadas al sistema para la creación de archivos especiales en general (`mknod`) y la específica para archivos FIFO (`mkfifo`). Pruebe a ejecutar el siguiente código correspondiente a dos programas que modelan el problema del productor/consumidor, los cuales utilizan como mecanismo de comunicación un cauce FIFO.

Determine en qué orden y manera se han de ejecutar los dos programas para su correcto funcionamiento y cómo queda reflejado en el sistema que estamos utilizando un cauce FIFO. Justifique la respuesta.



##### consumidorFIFO.c

~~~c
//consumidorFIFO.c
//Consumidor que usa mecanismo de comunicacion FIFO.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(void) {
	int fd;
	char buffer[80];// Almacenamiento del mensaje del cliente.
	int leidos;

	//Crear el cauce con nombre (FIFO) si no existe
	umask(0);
	mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
	//también vale: mkfifo(ARCHIVO_FIFO,0666);

	//Abrir el cauce para lectura-escritura
	if ( (fd=open(ARCHIVO_FIFO,O_RDWR)) <0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	//Aceptar datos a consumir hasta que se envíe la cadena fin
	while(1) {
		leidos=read(fd,buffer,80);
		if(strcmp(buffer,"fin")==0) {
			close(fd);
			return EXIT_SUCCESS;
		}
		printf("\nMensaje recibido: %s\n", buffer);
	}

	return EXIT_SUCCESS;
}
~~~



##### productorFIFO.c

~~~c
//productorFIFO.c
//Productor que usa mecanismo de comunicacion FIFO

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(int argc, char *argv[]) {
	int fd;

	//Comprobar el uso correcto del programa
	if(argc != 2) {
		printf("\nproductorFIFO: faltan argumentos (mensaje)");
		printf("\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de caracteres.\n");
		exit(EXIT_FAILURE);
	}

	//Intentar abrir para escritura el cauce FIFO
	if( (fd=open(ARCHIVO_FIFO,O_WRONLY)) <0) {
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	//Escribir en el cauce FIFO el mensaje introducido como argumento
	if( (write(fd,argv[1],strlen(argv[1])+1)) != strlen(argv[1])+1) {
		perror("\nError al escribir en el FIFO");
		exit(EXIT_FAILURE);
	}

	close(fd);
	return EXIT_SUCCESS;
}
~~~



#### Solución al ejercicio 1


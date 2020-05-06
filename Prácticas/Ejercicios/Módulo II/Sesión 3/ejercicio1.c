#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	pid_t PID;
	
	if (argc!=2) {
		printf("Uso: ./ejercicio1 <entero>\n");
		exit(-1);
	}
	
	if ((PID = fork())<0) {
		printf("Error creando proceso\n");
		perror("\nError en fork");
	}
	
	if ( PID == 0 ) {
		printf("\nPROCESO HIJO\n");
		printf("--------------------------------------------------------------\n");
		printf("Process ID: %d\n", getpid());
		printf("Partent Process ID: %d\n", getppid());
		printf("--------------------------------------------------------------\n");
		if ( atol(argv[1]) % 2 == 0 )
			printf("El número es par\n");
		else
			printf("El número es impar\n");
		printf("--------------------------------------------------------------\n");
	} else {
		printf("\nPROCESO PADRE\n");
		printf("--------------------------------------------------------------\n");
		printf("Process ID: %d\n", getpid());
		printf("Child Process ID: %d\n", PID);
		printf("--------------------------------------------------------------\n");
		if ( atol(argv[1]) % 4 == 0 )
			printf("El número es divisible por 4\n");
		else
			printf("El número no es divisible por 4\n");
		printf("--------------------------------------------------------------\n");
	}
	
	return 0;
}

## `SO`  `>`  Prácticas  `>`  Módulo II  `>`  Sesión 5

------

# Llamadas al Sistema para gestión y control de señales

> Prácticas de **Sistemas Operativos**
>
> Alumno: Miguel Ángel Fernández Gutiérrez
> Fecha: 2 de noviembre, 2018



------

## :pencil: Ejercicio 1

Implementa un programa en C que tenga como argumento un número entero. Este programa debe crear un proceso hijo que se encargará de comprobar si dicho número es un número par o impar e informará al usuario con un mensaje que se enviará por la salida estándar. A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará si lo es o no usando igualmente la salida estándar.



###### envioSignal.c

~~~c
/*
 envioSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada kill para enviar una señal:
 0: SIGTERM
 1: SIGUSR1
 2: SIGUSR2
  a un proceso cuyo identificador de proceso es PID.
 SINTAXIS: envioSignal [012] <PID> 
*/


#include <sys/types.h> //POSIX Standard: 2.6 Primitive System Data Types 
#include<limits.h> //Incluye <bits/posix1_lim.h> POSIX Standard: 2.9.2 //Minimum    //Values Added to <limits.h> y <bits/posix2_lim.h>
#include <unistd.h> //POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	long int pid;
   	int signal;
   	if(argc<3) {
   		printf("\nSintaxis de ejecucion: envioSignal [012] <PID>\n\n");
       	exit(EXIT_FAILURE);
   	}
   	pid=strtol(argv[2],NULL,10);
   	if(pid == LONG_MIN || pid == LONG_MAX) {
   		if(pid == LONG_MIN)
      		printf("\nError por desbordamiento inferior LONG_MIN %ld",pid);
       	else
       		printf("\nError por desbordamiento superior LONG_MAX %ld",pid);
       	perror("\nError en strtol");
       	exit(EXIT_FAILURE);
   	}
   	signal=atoi(argv[1]);
   	switch(signal) {
   		case 0: //SIGTERM
     	  	kill(pid,SIGTERM); break;
       	case 1: //SIGUSR1
    	   	kill(pid,SIGUSR1); break;
       	case 2: //SIGUSR2
       		kill(pid,SIGUSR2); break;
       	default : // not in [012]
   	    	printf("\n No puedo enviar ese tipo de señal");
    }
}
~~~



###### reciboSignal.c

~~~c
/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilización de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepción de una señal.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static void sig_USR_hdlr(int sigNum) {
	if(sigNum == SIGUSR1)
    	printf("\nRecibida la senal SIGUSR1\n\n");
    else if(sigNum == SIGUSR2)
    	printf("\nRecibida la senal SIGUSR2\n\n"); 
}

int main(int argc, char *argv[]) {
	struct sigaction sig_USR_nact;
    
    if(setvbuf(stdout,NULL,_IONBF,0)) {
        perror("\nError en setvbuf");
    }

	//Inicializar la estructura sig_USR_na para
    // especificar la nueva acción para la señal.
	sig_USR_nact.sa_handler= sig_USR_hdlr;

	//'sigemptyset' inicia el conjunto de señales dado al conjunto vacio. 
	sigemptyset (&sig_USR_nact.sa_mask);
	sig_USR_nact.sa_flags = 0;

	//Establecer mi manejador particular de señal para SIGUSR1
	if(sigaction(SIGUSR1,&sig_USR_nact,NULL)<0) {
		perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
		exit(EXIT_FAILURE);
    }

    //Establecer mi manejador particular de señal para SIGUSR2
	if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0) {
		perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
		exit(EXIT_FAILURE);
    }
	for(;;)
   	{
   	}
}
~~~



#### Solución al ejercicio 1

Estos programas se comunican mediante señales, dependiendo de la señal enviada o recibida el programa acabará haciendo mención a una señal o a otra.



------

## :pencil: Ejercicio 2

Escribe un programa en C llamado `contador`, tal que cada vez que reciba una señal que se pueda manejar, muestre por pantalla la señal y el número de veces que se ha recibido ese tipo de señal, y un mensaje inicial indicando las señales que no puede manejar.



#### Solución al ejercicio 2

###### `contador.c` (versión 1: usando `sigaction`)

~~~c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int j;
static int seniales[31];

static void handler_contador(int i) {
    seniales[i]++;
    printf("La señal %d se ha recibido %d veces\n", i, seniales[i]);
}

int main() {
    setvbuf(stdout,NULL,_IONBF,0);
    
    struct sigaction sa;
    sa.handler=handler_contador;
    sigemptyset(&sa.sa_mask);
    
    sa.flags = SA_RESTART;
    
    int seniales[31];
    for (j=0; j<31; j++)
        seniales[j]=0;
	
    for (int i=0; i<=60; i++) {
        if (sigaction(i, &sa, NULL) == -1)
            printf("Error en el handler\n");
    }
    
    // bucle infinito para que el programa se ejecute
    // mientras no le mandemos señales para terminar
    while(1);
}
~~~

###### `contador.c` (versión 2: usando `signal`)

~~~c
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int j;
static int seniales[31];

static void handler_contador(int i) {
    seniales[i]++;
    printf("La señal %d se ha recibido %d veces\n", i, seniales[i]);
}

int main() {
    setvbuf(stdout,NULL,_IONBF,0);
    
    int seniales[31];
    for (j=0; j<31; j++)
        seniales[j]=0;
	
    for (int i=0; i<=60; i++)
        signal(i, handler_contador);
    
    // bucle infinito para que el programa se ejecute
    // mientras no le mandemos señales para terminar
    while(1);
}
~~~



------

## :pencil: Ejercicio 3

Escribe un programa que suspenda la ejecución del proceso actual hasta que se reciba la señal `SIGUSR1`. Consulta en el manual en línea `sigemptyset` para conocer las distintas operaciones que permiten configurar el conjunto de señales de un proceso.



#### Solución al ejercicio 3

###### `ejercicio3.c`

~~~c
#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t new_mask;
    
    // vaciamos la máscara
    sigemptyset(&new_mask);
    
    // rellenamos la máscara con todas las señales
    sigfillset(&new_mask);
    
    // eliminamos SIGUSR1
    sigaddset(&new_mask, SIGUSR1);
    
    // cuando suspendamos el programa no reaccionará a ninguna señal excepto SIGUSR1
    sigsuspend(&new_mask);
}
~~~



------

## :pencil: Ejercicio 4

Compila y ejecuta el siguiente programa y trata de entender su funcionamiento.



###### tarea12.c

~~~c
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

static int signal_recibida = 0;

static void manejador (int sig) {
	signal_recibida = 1;
}

int main (int argc, char *argv[]) {
    sigset_t conjunto_mascaras;
    sigset_t conj_mascaras_original;
    struct sigaction act;
	
    //Iniciamos a 0 todos los elementos de la estructura act 
    memset(&act, 0, sizeof(act));

    act.sa_handler = manejador;

    if (sigaction(SIGTERM, &act, 0)) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
    //Iniciamos un nuevo conjunto de mascaras
    sigemptyset(&conjunto_mascaras);
    //Añadimos SIGTERM al conjunto de mascaras
    sigaddset(&conjunto_mascaras, SIGTERM);
    
    //Bloqueamos SIGTERM
    if (sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0) {
       perror ("primer sigprocmask");
       exit(EXIT_FAILURE);
    }

    sleep (10);

    //Restauramos la señal ó desbloqueamos SIGTERM
    if (sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0) {
       perror ("segundo sigprocmask");
       exit(EXIT_FAILURE);
    }

    sleep(1);

    if (signal_recibida)
   		printf ("\nSenal recibida\n");
   	exit(EXIT_SUCCESS);
}
~~~



#### Solución al ejercicio 4

La función `sigprocmask` se emplea para modificar la lista de señales bloqueadas en un momento dado. Tiene la siguiente sintaxis:

```c
int sigprocmask (int how, const sigset_t * set, sigset_t * old_set)
```

El primer parámetro, `how`, determina el comportamiento ante las máscaras. Sus posibles valores son:

- **`SIG_BLOCK`**: El conjunto de señales bloqueadas es la unión del actual y las de `set`
- **`SIG_UNBLOCK`**: El conjunto de señales presentes en set se eliminan de las bloquedas. Se considera permitido el intento de desbloquear una señal que no se haya bloqueada
- **`SIG_SETMASK`**: El conjunto de señales bloqueadas pasa a ser las de `set`

Por tanto, en nuestro programa, bloqueamos las típicas y la `SIGTERM`. `SIGTERM` es una señal de apagado *amable*: permite cerrar buffers, archivos abiertos, liberar memoria, etc... Es la señal por defecto cuando hacemos `kill PID` en la terminal.

Volviendo al cauce del programa: cuando usamos el segundo `sigprocmask()`, esta vez, usamos el parámetro `SIG_SETMASK`. Por tanto, vamos a bloquear las que contenga `conj_mascaras_original`. Esta contiene las originales: aquellas que se encontraban bloqueadas *antes* del primer `sigprocmask()`. Puedes ver que adquirimos el valor de las originales al pasárselo como tercer argumento en la primera ejecución.

Entre `sigprocmask` y `sigprocmask`, hemos dejado al programa inactivo 10s. Este periodo de tiempo nos permite capturar las señales. Como el manejador de señales es la función `manejador()`, si alguna señal ha llegado durante esos 10s (incluido `SIGTERM`), se ejecutará el `if()` final, indicándonos que, efectivamente, se ha recibido alguna señal.
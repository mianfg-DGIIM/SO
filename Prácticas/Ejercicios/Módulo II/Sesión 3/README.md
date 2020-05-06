#### `SO`  >  Prácticas  >  Exámenes  >  Módulo II  >  2013-02-inf



# Examen 2013-02 Informática



## :pencil: Ejercicio 2

Construir dos programas, `lanzador` y `explorador`, que se comunican por un FIFO, denominado `canal`.

1. El `lanzador` admite dos argumentos, dos nombres de archivo del directorio de trabajo. El proceso se encarga de crear el FIFO y dos procesos hijo; cada uno de ellos ejecutará el código de `explorador`. Tras lo cual leerá de FIFO y escribirá por pantalla el nombre del archivo y el nuevo propietario.
2. `explorador` admite un argumento, y analiza un cambio de propietario. En caso de haber un cambio de propietario, escribe en el FIFO el nombre del archivo que explora y el nuevo propietario.

> NOTA: he realizado este ejercicio teniendo en cuenta los **cambios de permisos**

#### Solución al ejercicio 1

> Ver el archivo `ejercicio1.c`



## :pencil: Ejercicio 2

¿Qué hace el siguiente programa? Intenta entender lo que ocurre con las variables y sobre todo con los mensajes por pantalla cuando el núcleo tiene activado/desactivado el mecanismo de buffering.

\> **Nota 1:** el núcleo no realiza buffering de salida con la llamada al sistema `write`. Esto quiere decir que cuando usamos `write(STDOUT_FILENO, buf, tama)`, los datos se escriben directamente en la salida estándar sin ser almacenados en un búfer temporal. Sin embargo, el núcleo sí realiza buffering de salida en las funciones de la biblioteca estándar de E/S del C, en la cual está incluida `printf`. Para deshabilitar el buffering en la biblioteca estándar de E/S se utiliza la siguiente función:

~~~c
int setvbuf(FILE *stream, char *buf, int mode , size_t size);
~~~

\> **Nota 2:** en la parte de llamadas al sistema para el sistema de archivos vimos que en Linux se definen tres macros `STDIN_FILENO`, `STDOUT_FILENO` y `STDERR_FILENO` para poder utilizar las llamadas al sistema `read` y `write` (que trabajan con descriptores de archivo) sobre la entrada estándar, la salida estándar y el error estándar del proceso. Además, en `<stdio.h>` se definen tres flujos (`STREAM`) para poder trabajar sobre estos archivos especiales usando las funciones de la biblioteca de E/S del C: `stdin`, `stdout` y `stderr`.

~~~c
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
~~~

¡Fíjate que `setvbuf` es una función que trabaja sobre STREAMS, no sobre descriptores de archivo!



> Ver el archivo `tarea4.c`



#### Solución al ejercicio 2

Este ejercicio quiere demostrar cómo cada proceso tiene sus propias variables de entorno, salvo compartidas, con `global`.



## :pencil: Ejercicio 3

Indica qué tipos de jerarquías de procesos se generan mediante la ejecución de cada uno de los siguientes fragmentos de código. Comprueba tu solución implementando un código para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el de su padre, PPID.

~~~c
// JERARQUÍA DE PROCESOS TIPO 1
for (i=1; i<nprocs; i++) {
    if ((childpid=fork())==-1) {
        fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
	}
	if (childpid)
		break;
}

// JERARQUÍA DE PROCESOS TIPO 2
for (i=1; i<nprocs; i++) {
	if ((childpid= fork()) == -1) {
		fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
	}
	if (!childpid)
		break;
}
~~~



#### Solución al ejercicio 3

##### Jerarquía de procesos

Implementamos el siguiente código para comprobar qué hará:

###### `ejercicio3x.c`

```c
#include <stdio.h>
#include <stdlib.h>	//poder utilizar exit
#include <sys/types.h>	//pid_t tipy
#include <errno.h>
#include <unistd.h>	//fork, pipe , write
#include <sys/wait.h>

int main( int arg , char * argv[]) {
	pid_t id_proceso;
	pid_t id_padre;
	pid_t pid = 0;
	int i = 0;
	while( ++i < 20 && pid == 0) {
		//creamos el hijillo
		if( (pid=fork())  < 0) {
			perror("\nNo se ha podido crear el hijo\n");
			exit(-1);
		}
	}
	id_proceso = getpid();
	id_padre = getppid();
	while(wait(NULL) != -1);
	printf ("PID = %d, PPID = %d\n",
            id_proceso , id_padre );
	exit (0);
}
```

Vemos que:

* A partir de un proceso padre, se crean otros 20 procesos, cada uno hijo del anterior.
* Al hacer `getpid` y `getppid`, se toma el proceso padre y el proceso hijo del último proceso en ejecución. Por ello, aparecen los últimos procesos primero. Cada uno de ellos es hijo del anterior (el siguiente que se mostrará en pantalla).
* Se mata al proceso: primero esperamos a que acabe con el `wait`, a continuación lo mostramos por pantalla y finalmente lo matamos con `exit`.
* De este modo, mostramos los procesos en orden de creación, de más nuevo a más antiguo. Nótese que el PID del hijo es el PID del padre +1, excepto del proceso padre de todos.



##### Jerarquía de procesos tipo 1

De nuevo, implementamos el código:

###### `ejercicio3a.c`

~~~c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int num_procesos = 20;
    pid_t childpid;

    // Jerarquía tipo 1 //
    for (int i=1; i < num_procesos; i++){
        if ( (childpid = fork()) == -1){
            fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
            exit(-1);
        }


        if (childpid){
            printf("Padre: %d, proceso: %d\n", getppid(), getpid());
            break;
        }
    }
}
~~~

Vemos que:

* El proceso padre crea un proceso hijo, y éste un nuevo hijo suyo, y así sucesivamente.
* 



##### Jerarquía de procesos tipo 2

###### `ejercicio3b.c`

~~~c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int num_procesos = 20;
    pid_t childpid;

    // Jerarquía tipo 1 //
    for (int i=1; i < num_procesos; i++){
        if ( (childpid = fork()) == -1){
            fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
            exit(-1);
        }


        if (!childpid){
            printf("Padre: %d, proceso: %d\n", getppid(), getpid());
            break;
        }
    }
}
~~~

Vemos que:

* En este caso el proceso padre crea muchos procesos hijo.



## :pencil: Ejercicio 4

Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se identificará en la salida estándar, mostrando un mensaje del tipo _Soy el hijo PID_. El proceso padre simplemente tendrá que esperar la finalización de todos sus hijos y cada vez que detecte la finalización de uno de sus hijos escribirá en la salida estándar un mensaje del tipo:

~~~
Acaba de finalizar mi hijo con <PID>
Sólo me quedan <NUM_HIJOS> hijos vivos
~~~



#### Solución al ejercicio 4

###### `ejercicio4.c`

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    int i, estado;
    pid_t PID;
    
    // printf() tan pronto como sea posible
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    
    // creación de hijos
    for (i=0; i<5; i++) {
        if ((PID=fork())<0) {
            perror("Error en fork\n");
            exit(-1);
        }
        
        if (PID==0) {
            printf("Soy PID=%i, el hijo de PPID=%i\n", getpid(), getppid());
            exit(0);
        }
    }
    
    // esperamos hijos
    for (i=4; i>=0; i--) {
        PID = wait(&estado);
        printf("Ha finalizado el hijo con PID=%i", PID);
        printf("Solo me quedan %i hijos vivos\n\n", i);
    }
    
    exit(0);
}
```



Es interesante apreciar que:

* Ambos bucles se entremezclan, sólo basta ver la salida del programa.
* Los procesos hijos se crean, imprimen una cadena y se cierran.
* Mientras tanto, el segundo `for` los vigila, haciendo uso de `wait`. `PID = wait(&estado)` vigila constantemente el cambio de estado en el proceso. Si alguno termina, entonces el bucle continúa.



## :pencil: Ejercicio 5

Implementa una modificación sobre el anterior programa en la que el proceso padre espera primero a los hijos creados en orden impar (1º, 3º, 5º) y después a los hijos pares (2º y 4º).



#### Solución al ejercicio 5

> Ver archivo `ejercicio5.c`



## :pencil: Ejercicio 6

¿Qué hace el siguiente programa?

> Ver archivo `tarea5.c`



#### Solución al ejercicio 6

Primero, alojamos un proceso nuevo con `fork()`, como vimos en los ejercicios anteriores. Si hemos conseguido crearlo, ejecutaremos el programa `ldd` con la función `execl()` dentro de C. Para ello, indicamos la ruta donde se encuentra el progama, con la orden y el nombre del ejecutable de nuestro programa. Si no conseguimos que se ejecute, nuestro programa en C se cerrará. Mientras tanto, `wait()` le echa un ojo a lo que está ocurriendo en el proceso hijo mediante la variable estado. Está bien documentada en el código.



## :pencil: Ejercicio 7

Escribe un programa que acepte como argumentos el nombre de un programa, sus argumentos si los tiene, y opcionalmente la cadena “bg”. Nuesto programa deberá ejecutar el programa pasado como primer argumento en `foreground` si no se especifica la cadena “bg” y en `background` en caso contrario. Si el programa tiene argumentos hay que ejecutarlo con éstos.



#### Solución al ejercicio 7

> Ver archivo `ejercicio7.c`
#### `SO`  >  Prácticas  >  Exámenes  >  Módulo II  >  2013-02_infB2



# Examen 2013-02 Informática B2



## :pencil: Ejercicio 1

Lea la documentación que se le proporciona sobre el archivo `maps`.

Construya un programa que se llamará `conSoporte.c`. Cuando se ejecute desde el shell bash, obtendremos con `getppid()` el pid de dicha ejecución del intérprete de órdenes padre de `conSoporte`. Formamos la ruta del archivo que contiene el mapa de memoria de dicho proceso padre:

~~~C
char mempadre[60];
sprintf(mempadre, “/proc/%d/maps”, getppid());
~~~

Este programa `conSoporte.c` deberá lanzar un proceso con lo que tendremos dos procesos, padre e hijo, que se comunicarán con un cauce (con nombre o sin nombre, decídalo usted).

El proceso hijo debe llamar a `exec()` para lanzar una ejecución de la orden cat que obtenga el contenido del archivo `/proc/<pid-del-padre>/maps`. Debe conseguirse que estos datos vayan al cauce, de donde los tomará el padre. El proceso padre leerá carácter a caracter del cauce y procesará esta secuencia de forma que cuando el carácter leído sea `/` es porque comienza la ruta de un archivo aludido en el archivo maps, y deberá llevar a la salida estándar el resto de la línea (hasta encontrar un carácter que sea `\n`).

Para cada carácter leido el procesamiento podria seguir esta pauta:

~~~c
if (strcmp(c,"/")==0)
    deboescribir=1;
if (deboescribir) {
    // ... escribir el caracter que acabamos de leer ...
}
if (strcmp(c,"\n")==0)
    deboescribir=0;
~~~

> Ver archivo `conSoporte.c`
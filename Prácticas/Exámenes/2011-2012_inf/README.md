#### `SO`  >  Prácticas  >  Exámenes  >  Módulo II  >  2011-2012_inf

# Examen 2011-2012 Informática

> **IMPORTANTE: Este ejercicio no funciona (todavía jeje)**

## :pencil: Examen

El objetivo es construir dos programas: `lanzador` y `slave`.

El programa `lanzador` acepta como argumento un número, `<num_slave>`, que indica el número de procesos esclavos que se van a lanzar. A continuación, se describe la funcionalidad requerida para cada uno de los programas y, al final, se muestra un esquema de los procesos, el programa que ejecuta cada uno y las comunicaciones que se deben establecer entre estos.

### `lanzador <num_slave>`

Se encarga de crear dos FIFOs con nombre, `FIFOe` y `FIFOs` y de abrirlos adecuadamente. Debe lanzar `<num_slave>` procesos hijo que ejecuten el programa `slave`. A continuación, debe generar aleatoriamente tantos números enteros como procesos esclavos haya lanzado y escribirlos en el `FIFOe`. Seguidamente, debe leer desde el `FIFOs` los resultados que proporcionan los procesos `slave` e imprimirlos en pantalla. Por último, se encargará de eliminar del sistema de archivos los FIFOs con nombre creados. Además, debe establecer un manejador de señal, al comienzo del programa, para la señal `SIGCHLD`, de forma que se puedan ir eliminando los hijos creados conforme estos terminan.

> Implementado en `lanzador.c`

### `slave`

Se encarga de leer de la entrada estándar un número entero de los generados por el proceso lanzador y lo utiliza para leer la información de atributos del archivo correspondiente a la posición indicada por dicho número en el directorio de trabajo. A continuación, escribe el número de inodo y el tamaño del archivo en el `FIFOs`. Tener en cuenta este funcionamiento a la hora de establecer las comunicaciones en los procesos que ejecutarán este programa.

> Implementado en `slave.c`
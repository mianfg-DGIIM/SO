#### `SO`  `>`  Prácticas  `>`  Módulo II  `>`  Sesión 2



# Llamadas al Sistema para el sistema de archivos (II)

## :pencil: Ejercicio 1

¿Qué hace el siguiente programa?

> Ver archivo `tarea3.c`

#### Solución al ejercicio 1

El programa hace lo siguiente:

1. Abre `archivo1`, y en caso de no existir lo crea, con los permisos especificados en la orden.
2. Reinicializa la máscara de `umask`. De este modo, los permisos se restringirán.
3. Ídem 1 con `archivo2`.
4. Accedemos a la estructura `stat` de `archivo1`.
5. Modificamos los permisos de `archivo1` eliminando los permisos de ejecución para el grupo. Además, activamos la asignación del GID del propietario al GID efectivo del proceso que ejecute el archivo.
6. Modificamos los permisos de `archivo2`, reescribiéndolos asignando permisos de escritura para usuario y grupo, y de lectura para grupo y otros.



## :pencil: Ejercicio 2

Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte
como entrada:

- Un argumento que representa el '***pathname***' de un directorio.
- Otro argumento que es un ***número octal de 4 dígitos*** (similar al que se puede utilizar para cambiar los permisos en la llamada al sistema `chmod`). Para convertir este argumento tipo cadena a un tipo numérico puedes utilizar la función `strtol`. Consulta el manual en línea para conocer sus argumentos.

El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos de todos los archivos que se encuentren en el directorio indicado en el primer argumento.

El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio que esté formada por:

```
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
```

Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente información en la línea de salida:

```
<nombre_de_archivo> : <errno> <permisos_antiguos>
```



#### Solución al ejercicio 2

> Ver archivo `ejercicio2.c`



## :pencil: Ejercicio 3

Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el grupo y para otros. Además del nombre de los archivos encontrados, deberá devolver sus números de inodo y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:

```
$> ./buscar <pathname>
```

donde `<pathname>` especifica la ruta del directorio a partir del cual queremos que empiece a analizar la estructura del árbol de subdirectorios. En caso de que no se le de argumento, tomará como punto de partida el directorio actual. Ejemplo de la salida después de ejecutar el programa:

```
Los i-nodos son:
./a.out 55
./bin/ej 123
./bin/ej2 87
...
Existen 24 archivos regulares con permiso x para grupo y otros
El tamaño total ocupado por dichos archivos es 2345674 bytes
```



#### Solución al ejercicio 3

> Ver archivo `ejercicio3.c`



## :pencil: Ejercicio 4

Implementa de nuevo el programa buscar del ejercicio 3 utilizando la llamada al sistema `nftw`.



#### Solución al ejercicio 4

> Ver archivo `ejercicio4.c`
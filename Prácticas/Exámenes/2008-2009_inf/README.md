#### `SO`  >  Prácticas  >  Exámenes  >  Módulo II  >  2008-2009_inf

# Examen 2008-2009 Informática

## :pencil: Ejercicio 1

Un programa, denominado `LeerDir`, que lee de la estrada estándar un número entero n. Si este número es cero, el programa finaliza. Si es distinto de cero, lee la entrada n-ésima del directorio que se le pasa como argumento y muestra en pantalla la siguiente información de esa entrada: el nombre, su numero de inodo, su tamaño en bytes, el tipo de archivo y los permisos para el usuario. Si el número leido es mayor que el número de entradas del directorio, entonces escribe en la salida estándar un mensaje de error.

> La solución ha sido implementada en el archivo `LeerDir.c`

## :pencil: Ejercicio 2

Un programa, denominado `Padre`, que crea dos procesos hijos y un cauce (con o sin nombre) entre los dos hijos. Una vez realizadas estas acciones, espera la finalización de los dos hijos, y cuando esta se produce, él también finaliza tras escribir un mensaje de notificación en la salida estándar.
- Uno de los procesos hijo lee de su entrada estándar un numero entero de 0 a 9 y lo escribe en el cauce. Si es este número es 0, además de escribirlo en el cauce, finaliza.
- El otro hijo, ejecuta el código del programa `LeerDir`.

> La solución ha sido implementada en el archivos `Padre.c`
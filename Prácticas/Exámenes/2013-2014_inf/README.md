#### `SO`  >  Prácticas  >  Exámenes  >  Módulo II  >  2013-2014_inf

# Examen 2013-2014 Informática

## :pencil: Ejercicio 2.a

Construir dos programas, `lanzador` y `explorador`, que se comunican por un FIFO, denominado `canal`.

1. El `lanzador` admite dos argumentos, dos nombres de archivo del directorio de trabajo. El proceso se encarga de crear el FIFO y dos procesos hijo; cada uno de ellos ejecutará el código de `explorador`. Tras lo cual leerá de FIFO y escribirá por pantalla el nombre del archivo y el nuevo propietario.
2. `explorador` admite un argumento, y analiza un cambio de propietario. En caso de haber un cambio de propietario, escribe en el FIFO el nombre del archivo que explora y el nuevo propietario.

_\> **NOTA:** he realizado este ejercicio teniendo en cuenta los **cambios de permisos** en lugar de los de propietario, para poder ejecutar el código y probarlo más fácil._

> La solución ha sido implementada en los archivos `lanzador.c` y `explorador.c`

## :pencil: Ejercicio 2.b

Sin modificar el código de `explorador`, incorporar los cambios oportunos para que cuando a `lanzador` se le pase un tercer argumento `r`, los exploradores escriban la salida en un archivo regular de nombre `datos`, en lugar de en la salida estándar.

> Las modificaciones han sido implementadas en `lanzador2.c`
#### `SO`  >  Prácticas  >  Exámenes  >  Módulo II  >  2015-JAntonio

# Examen 2015-JAntonio Informática

## :pencil: Parte obligatoria mínima (50%)

Construir un único programa que cree un proceso hijo. Ambos procesos utilizaran un cauce con/sin nombre para comunicarse (el tipo de cauce lo dejo a vuestra elección). Donde el trabajo de cada proceso es:
* **El padre:** lee el directorio actual y para cada archivo regular contenido en el mismo:
    * obtiene e imprime en pantalla su número de inodo junto con el UID del propietario.
    * escribe el nombre del archivo en el cauce.
* **El hijo:** lee del cauce el nombre del archivo escrito por el padre el lo lee entero mediante el mecanismo de proyección de archivos. Tras lo cual, muestra en pantalla su contenido.

_\>**Nota:** no he realizado la proyección de archivos._	

## :pencil: Ampliación

1. [15%] El padre se asegura que los archivos cuyo nombre va a pasar al hijo tienen permiso de lectura para el proceso, si no fuese así, lo cambia para que los pueda leer el hijo.
2. [15%] Establecer un manejador para la señal `SIGPIPE` en el padre en caso de que el proceso hijo finalice inesperadamente de forma que se indique el evento por pantalla.
3. [20%] El acceso al archivo por parte del proceso hijo es exclusivo, es decir, bloqueará el archivo antes de acceder al mismo y lo desbloqueará al finalizar.

> La solución ha sido implementada en el archivo `examen.c`
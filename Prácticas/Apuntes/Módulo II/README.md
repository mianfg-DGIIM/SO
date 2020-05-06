#### `SO`  >  Prácticas  >  Apuntes  >  Módulo II



# Apuntes de Prácticas de SO: Módulo II. Uso de los servicios del SO mediante la API



En esta carpeta figuran apuntes útiles para el módulo II de prácticas de SO. Cada sesión de prácticas tiene unos apuntes, enlazados a continuación:



| Nombre de archivo                          | Descripción                                           |
| ------------------------------------------ | ----------------------------------------------------- |
| [sesion1_apuntes.md](./sesion1_apuntes.md) | Llamadas al sistema para el sistema de archivos (I)   |
| [sesion2_apuntes.md](./sesion2_apuntes.md) | Llamadas al sistema para el sistema de archivos (II)  |
| [sesion3_apuntes.md](./sesion3_apuntes.md) | Llamadas al sistema para el control de procesos       |
| [sesion4_apuntes.md](./sesion4_apuntes.md) | Comunicación entre procesos utilizando cauces         |
| [sesion5_apuntes.md](./sesion5_apuntes.md) | Llamadas al sistema para gestión y control de señales |
| [sesion6_apuntes.md](./sesion6_apuntes.md) | Control de archivos y archivos proyectados a memoria  |



## Glosario práctico

A continuación, aparecen todas las funciones (llamadas al sistema) usadas en las prácticas.

| Llamada al sistema | Uso                                           | Aparece en... |
| ------------------ | --------------------------------------------- | ------------- |
| `open()`           | Abrir un archivo                              | Sesión 1      |
| `read()`           | Leer datos de un archivo                      | Sesión 1      |
| `write()`          | Escribir datos a un archivo                   | Sesión 1      |
| `lseek()`          | Cambiar el desplazamiento                     | Sesión 1      |
| `close()`          | Cerrar un archivo                             | Sesión 1      |
| `stat()`           | Recopilar información de archivos             | Sesión 1      |
| `lstat()`          | Recopilar información de archivos             | Sesión 1      |
| `fstat()`          | Recopilar información de archivos             | Sesión 1      |
| `umask()`          | Modificar máscara de creación de ficheros     | Sesión 2      |
| `chmod()`          | Modificar permisos de archivo                 | Sesión 2      |
| `fchmod()`         | Modificar permisos de archivo                 | Sesión 2      |
| `opendir()`        | Abrir un directorio                           | Sesión 2      |
| `readdir()`        | Leer de un directorio                         | Sesión 2      |
| `closedir()`       | Cerrar un directorio                          | Sesión 2      |
| `rewinddir()`      | Vuelta al comienzo de un directorio           | Sesión 2      |
| `seekdir()`        | Acceso avanzado a directorios                 | Sesión 2      |
| `telldir()`        | Acceso avanzado a directorios                 | Sesión 2      |
| `nftw()`           | Recorrer un sistema de archivos               | Sesión 2      |
| `fork()`           | Creación de procesos                          | Sesión 3      |
| `exit()`           | Terminación de procesos                       | Sesión 3      |
| `wait()`           | Esperar a proceso hijo                        | Sesión 3      |
| `waitpid()`        | Esperar a proceso hijo                        | Sesión 3      |
| `execve()`         | Cargar nuevo programa                         | Sesión 3      |
| `execle()`         | Cargar nuevo programa                         | Sesión 3      |
| `execlp()`         | Cargar nuevo programa                         | Sesión 3      |
| `execvp()`         | Cargar nuevo programa                         | Sesión 3      |
| `execv()`          | Cargar nuevo programa                         | Sesión 3      |
| `execl()`          | Cargar nuevo programa                         | Sesión 3      |
| `kill()`           | Enviar una señal                              | Sesión 5      |
| `sigaction()`      | Cambiar la acción ante el recibo de una señal | Sesión 5      |
| `sigprocmask()`    | Cambiar máscara de señales de un proceso      | Sesión 5      |
| `sigpending()`     | Examinar conjunto de señales pendientes       | Sesión 5      |
| `sigsuspend()`     | Esperar a una señal usando una máscara        | Sesión 5      |
| `fcntl()`          | Esta función merece un pedestal               | Sesión 6      |
| `mmap()`           | Crear una proyección de memoria               | Sesión 6      |
| `munmap()`         | Eliminar una proyección de memoria            | Sesión 6      |

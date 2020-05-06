**`SO`  `>`  Prácticas  `>`  Módulo I  `>`  Sesión 1**

# :one: Herramientas de administración básicas



## :pencil: Ejercicio 1

Crea un script de _bash_ que automatice todos los pasos vistos en este punto y que guardarás preferiblemente en tu directorio `home`. Al entrar de nuevo en el sistema sólo tendrás que ejecutar el script para empezar a trabajar en modo `root`.



#### Solución al ejercicio 1

~~~sh
#!/bin/bash

cp /fenix/depar/lsi/UML/*.gz /tmp
cd /tmp
gunzip *.gz
./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
~~~



## :pencil: Ejercicio 2

Visualiza el contenido de los dos archivos (`/etc/default/useradd` y `/etc/login.defs`) y comprueba cuáles son las opciones por defecto que tendría un usuario que se creara en nuestro sistema. A continuación, crea una cuenta de usuario y visualiza el contenido de los archivos `/etc/passwd` y `/etc/group`, y el directorio `/home` para comprobar que los nuevos datos se han rellenado conforme a la especificación tomada de `/etc/default/useradd` y `/etc/login.defs`.



#### Solución al ejercicio 2

```non
>[root /]$ cat /etc/default/useradd
# useradd defaults file
GROUP=100
HOME=/home
INACTIVE=-1
EXPIRE=
SHELL=/bin/bash
SKEL=/etc/skel
CREATE_MAIL_SPOOL=yes
```

~~~
>[root /]$ cat /etc/login.defs
#
# Please note that the parameters in this configuration file control the
# behavior of the tools from the shadow-utils component. None of these
# tools uses the PAM mechanism, and the utilities that use PAM (such as the
# passwd command) should therefore be configured elsewhere. Refer to
# /etc/pam.d/system-auth for more information.
#

# *REQUIRED*
#   Directory where mailboxes reside, _or_ name of file, relative to the
#   home directory.  If you _do_ define both, MAIL_DIR takes precedence.
#   QMAIL_DIR is for Qmail
#
#QMAIL_DIR	Maildir
MAIL_DIR	/var/spool/mail
#MAIL_FILE	.mail

# Password aging controls:
#
#	PASS_MAX_DAYS	Maximum number of days a password may be used.
#	PASS_MIN_DAYS	Minimum number of days allowed between password changes.
#	PASS_MIN_LEN	Minimum acceptable password length.
#	PASS_WARN_AGE	Number of days warning given before a password expires.
#
PASS_MAX_DAYS	99999
PASS_MIN_DAYS	0
PASS_MIN_LEN	5
PASS_WARN_AGE	7

#
# Min/max values for automatic uid selection in useradd
#
UID_MIN                  1000
UID_MAX                 60000
# System accounts
SYS_UID_MIN               201
SYS_UID_MAX               999

#
# Min/max values for automatic gid selection in groupadd
#
GID_MIN                  1000
GID_MAX                 60000
# System accounts
SYS_GID_MIN               201
SYS_GID_MAX               999

#
# If defined, this command is run when removing a user.
# It should remove any at/cron/print jobs etc. owned by
# the user to be removed (passed as the first argument).
#
#USERDEL_CMD	/usr/sbin/userdel_local

#
# If useradd should create home directories for users by default
# On RH systems, we do. This option is overridden with the -m flag on
# useradd command line.
#
CREATE_HOME	yes

# The permission mask is initialized to this value. If not specified, 
# the permission mask will be initialized to 022.
UMASK           077

# This enables userdel to remove user groups if no members exist.
#
USERGROUPS_ENAB yes

# Use SHA512 to encrypt password.
ENCRYPT_METHOD SHA512 
~~~



~~~
>[root /]$ useradd johndoe
>[root /]$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
[...]
johndoe:x:1000:1000::/home/johndoe:/bin/bash
>[root /]$ cat /etc/group
root:x:0:
bin:x:1:
daemon:x:2:
[...]
johndoe:x:1000:
>[root /]$ ls /home
johndoe
~~~



## :pencil: Ejercicio 3

1. Utiliza el manual en línea para leer la sintaxis completa de la utilidad para creación de cuentas y crea dos o tres usuarios en tu sistema cambiando alguno de los valores por defecto.
2. Elimina alguno de ellos y comprueba que “rastro” ha dejado la cuenta recién eliminada en el sistema.
3. Entra (orden `su`) en el sistema como uno de estos usuarios que has creado y mira qué archivos tiene en su directorio `home`. La orden `sudo` permite cambiar el modo de trabajo a modo `root` específicamente para ejecutar una orden con privilegios de supervisor y tras su ejecución continuar con los privilegios del usuario que abrió la sesión.



#### Solución al ejercicio 3

~~~
>[root /]$ useradd -d /home/mariaf maria
>[root /]$ useradd -d /helena -s /bin/sh -g 1001 helena
>[root /]$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
bin:x:1:1:bin:/bin:/sbin/nologin
daemon:x:2:2:daemon:/sbin:/sbin/nologin
[...]
johndoe:x:1000:1000::/home/johndoe:/bin/bash
maria:x:1001:1001::/home/mariaf:/bin/bash
helena:x:1002:1001::/helena:/bin/sh
~~~

Del mismo modo podemos usar la orden `newusers`

~~~
>[root /]$ touch /tmp/newusers
>[root /]$ vi /tmp/newusers
	# Añadimos las siguientes líneas de código:
		nuevo1:x::1001:nuevo:/home/nuevo:/bin/sh
		nuevo2:x::3210:Paco Javier:/home/nuevo2:/bin/bash
>[root /]$ newusers /tmp/newusers
>[root /]$ cat /etc/passwd
[...]
nuevo1:x:1003:1001:nuevo:/home/nuevo:/bin/sh
nuevo2:x:1004:3210:Paco Javier:/home/nuevo2:/bin/bash
>[root /]$ cat /etc/group
[...]
johndoe:x:1000:
maria:x:1001:
nuevo2:x:3210:
~~~

Veamos qué ocurre cuando eliminamos a `johndoe`

~~~
>[root /]$ userdel johndoe
>[root /]$ cat /etc/passwd
	# En efecto no está aquí
>[root /]$ cat /etc/group
	# Ni aquí tampoco
>[root /]$ ls /home
	# Vemos que ha dejado su carpeta home
johndoe mariaf nuev nuevo2
~~~

Ahora entramos con la orden `su` como el usuario `maria`. Veamos qué archivos tiene su directorio `home`.

~~~
>[root /]$ su maria
>[maria /]$ ls -a /home/mariaf
. .. .bash_logout .bash_profile .bashrc
~~~

En efecto tiene los archivos de configuración de la terminal.



> Para volver a `root`, sencillamente hacemos `exit` para cerrar la sesión de `maria`.



## :pencil: Ejercicio 4

Visualiza el archivo `/etc/passwd` e indica cuál es el formato de cada línea de dicho archivo. Para ello también puedes consultar el `man` o `info` de Linux. ¿Quién es el propietario de este archivo y cuáles son sus permisos?



#### Solución al ejercicio 4

~~~
>[root /]$ cat /etc/passwd
[...]
~~~

El formato de línea es:

~~~
usuario:clave:uid:gid:nombreusuario:dirtrabajo:shell
~~~

Además:

~~~
>[root /]$ ls -l /etc/passwd  # equivalentemente, ls -lF /etc | grep passwd
-rw-r--r-- 1 root root 1087 Dec 16 15:02 /etc/passwd
~~~

Vemos que el propietario es `root`, y que éste es el único usuario con permiso de escritura, el resto tienen permiso de lectura únicamente, tanto para el grupo al que pertenece como para el resto de usuarios.



## :pencil: Ejercicio 5

Visualiza el archivo `/etc/shadow` desde un usuario distinto al `root`. ¿Te da algún problema? ¿Sabes por qué? Intenta averiguarlo.



#### Solución al ejercicio 5

~~~
>[maria /]$ cat /etc/shadow
cat:/etc/shadow: Permission denied
~~~

Esto es así debido a que:

~~~
>[maria /]$ ls -l /etc/shadow
---------- 1 root root 828 Dec 16 15:02 /etc/shadow
~~~



## :pencil: Ejercicio 6

1. Crea un par de grupos y asignáselos a algunos de los usuarios de tu sistema.
2. ¿Qué información devuelve la orden id si estás conectado como root?



#### Solución al ejercicio 6

Crearemos dichos grupos.

~~~
>[root /]$ groupadd grupo1
>[root /]$ gpasswd -a maria grupo1
Adding user maria to group group1
>[root /]$ groupadd grupo2
>[root /]$ gpasswd -a nuevo1 grupo2
Adding user nuevo1 to group grupo2
~~~

Veamos qué información devuelve `id` si estamos como `root`:

~~~
>[root /]$ id
uid=0(root) gid=0(root) groups=0(root)
~~~



## :pencil: Ejercicio 7

Utilizando la orden (`find`) que ya conoces para la búsqueda de archivos en el sistema de archivos, anota el nombre absoluto del archivo del kernel de Linux que se ha cargado en el sistema operativo que estás usando en el laboratorio de prácticas para acceso modo root.



#### Solución al ejercicio 7

> DUDA



## :pencil: Ejercicio 8

Utilizando la información que tienes disponible responde a las siguientes preguntas:

1. ¿Dónde podría guardar un programa que se ejecutase en modo root la información temporal de forma que ésta se mantuviese entre arranques del sistema?

   ###### Solución

   En `/var/tmp`.

2. ¿En que directorio se guardan los archivos de configuración del _Sistema de Ventanas X_? ¿Cuál es el nombre del archivo que almacena el nombre del programa _Gestor de Ventanas_ que utiliza el sistema por defecto? ¿Cuál es el gestor de ventanas que usa por defecto nuestro sistema?

   ###### Solución

   Se encuentran en `/etc`, concretamente en `/etc/X11`. El nombre del archivo que almacena el nombre del programa _Gestor de Ventanas_ que utiliza el sistema por defecto es `/etc/X11/default-display-manager`, el cual te indica que el gestor por defecto es `/usr/sbin/gdm`.



## :pencil: Ejercicio 9

Los archivos `/etc/fstab` y `/etc/mtab` muestran información sobre los sistemas de archivos que se encuentran montados en el sistema. ¿Cuál es la diferencia entre la información que muestra cada uno de ellos?



#### Solución al ejercicio 9

* El archivo `/etc/fstab` se encuentra comúnmente en sistemas Unix como parte de la configuración del sistema. Lo más destacado de este fichero es la lista de discos y particiones disponibles. En ella se indican cómo montar cada dispositivo y qué configuración utilizar.
* El archivo `/etc/mtab` es un archivo de información del sistema, comúnmente en Unix. Este archivo lista todos actualmente los sistemas de ficheros montados junto con sus opciones de inicialización. `mtab` tiene mucho en común con `fstab`, pero la diferencia principal es que este último enumera todos los sistemas de archivos disponibles.



# :pencil: Ejercicio 10

Edita el archivo /etc/fstab del sistema de archivos que estás utilizando en modo root y anota y describe la información que tiene registrada. Si no conoces alguna opción puedes consultar el manual en línea: man fstab.



#### Solución al ejercicio 10

~~~
>[root /]$ cat /etc/fstab
#
# /etc/fstab
#
LABEL=ROOT					/		auto	noatime1 1
tmpfs						/dev/shm	tmpfs	defaults0 0
tmp						/tmp		tmpfs	rw,mode=1777,fscontext=system_u:object_r:tmp_t:s0	0 0
devpts						/dev/pts	devpts	gid=5,mode=620	0 0
sysfs						/sys		sysfs	defaults0 0
proc						/proc		proc	defaults0 0
~~~

* El primer campo nos indica el archivo de sistema de dispositivo especial remoto a ser montado, en este caso `LABEL=ROOT`.
* El segundo campo nos indica el punto de montaje.
* El tercer campo describe el tipo de archivo del sistema.
* El cuarto nos indica la cantidad de opciones asociados al archivo del sistema.
* El quinto campo es usado por archivos del sistema por el comando de volcado.
* El sexto campo es usado por `fsck` para determinar el orden en que los archivos del sistema son analizados como correctos a la hora de reiniciar.



# :pencil: Ejercicio 11

Compara la información que presentan los cuatro archivos de texto que se han presentado en este apartado y describe en un párrafo para lo que te sirve la información que registra cada archivo.



#### Solución al ejercicio 11

* **`/etc/fstab`** se encuentra comúnmente en sistemas Unix como parte de la configuración del sistema. Lo más destacado de este fichero es la lista de discos y particiones disponibles. En ella se indican cómo montar cada dispositivo y qué configuración utilizar.
* **`/etc/mtab`** es un archivo de información del sistema, comúnmente en Unix. Lista todos los sistemas de ficheros montados actualmente junto con sus opciones de inicialización. `mtab` tiene mucho en común con `fstab`, pero la _diferencia principal_ es que este último enumera todos los sistemas de archivos disponibles.
* **`/proc/filesystems`** muestra una lista de los tipos del sistema de archivos soportados actualmente por el kernel.
* **`/proc/mounts`** proporciona una lista de todos los montajes en uso por el sistema. La salida se parece a `/etc/mtab`, excepto que `/proc/mounts` está más actualizado.
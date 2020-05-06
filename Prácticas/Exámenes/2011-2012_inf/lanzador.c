#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

int main( int argc, char *argv[] ) {
    pid_t PID, PID_parent;
    int fd_e, fd_s;
    int aleatorio; char aleatorio_buff[10];
    char ch; char buffer[100];

    if ( argc != 2 ) {
        printf("Uso: ./lanzador <num_slave>\n");
        perror("\nError en argumentos");
        exit(EXIT_FAILURE);
    }

    int num_slave = atoi(argv[1]);

    PID_parent = getpid();

    // desactivamos búfer para printf
	setvbuf(stdout, NULL,_IONBF, 0);

    unlink("FIFOe");
    unlink("FIFOs");
    umask(0);
    mkfifo("FIFOe", 0666);
    mkfifo("FIFOs", 0666);

    if ( (fd_e=open("FIFOe", O_RDWR)) < 0 ) {
        perror("\nError en open() para FIFOe");
        exit(EXIT_FAILURE);
    }

    for ( int i = 0; i < num_slave; i++ ) {
        if ( getpid() == PID_parent )
            switch(fork()) {
                case -1:
                    perror("\nError en fork()");
                    exit(EXIT_FAILURE);
                case 0:
                    if ( dup2(fd_e, STDIN_FILENO) < 0 ) {
                        perror("\nError en dup2()");
                        exit(EXIT_FAILURE);
                    }
                    execlp("./slave", "slave", NULL);
                    break;
                default:
                    break;
            }
    }

    if ( (fd_s=open("FIFOs", O_RDONLY)) < 0 ) {
        perror("\nError en open() para FIFOs");
        exit(EXIT_FAILURE);
    }

    for ( int i = 0; i < num_slave; i++ ) {
        aleatorio = 3;
        printf("[%i] aleatorio=%i\n",i, aleatorio);
        sprintf(aleatorio_buff, "%i\0", aleatorio);
        if ( write(fd_e, aleatorio_buff, strlen(aleatorio_buff)) != strlen(aleatorio_buff) ) {
            perror("\nError en write()");
            exit(EXIT_FAILURE);
        }
    }                    

    int i = 0;
    for ( int i = 0; i < num_slave; i++ ) {
        while ( read(fd_s, &ch, sizeof(ch)) > 0 ) {
            buffer[i] = ch;
            i++;
            if ( ch == '\n' ) {
                printf("%s", buffer);
                i=0;
            }
        }
        if ( write(STDOUT_FILENO, buffer, strlen(buffer)) != strlen(buffer) ) {
            perror("\nError en write()");
            exit(EXIT_FAILURE);
        }
    }

    close(fd_e);
    close(fd_s);

    unlink("FIFOe");
    unlink("FIFOs");
    
    exit(EXIT_SUCCESS);
}
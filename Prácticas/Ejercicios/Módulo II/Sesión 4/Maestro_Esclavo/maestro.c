#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv) {
	if ( argc != 3 ) {
		perror("Fallo argumentos\n");
	}
	
	int min, max;
	
	min = atoi(argv[1]);
	max = atoi(argv[2]);
	
    char string_min[100], string_max[100];
    
    setvbuf(stdout,NULL,_IONBF,0);

    int fd[2];
    pid_t PID[2];

    pipe(fd);

    if ((PID[0]=fork())<0) {

    }
    if (PID[0] != 0) {
        if ((PID[1]=fork())<0) {

        }
    }

    if (PID[0] == 0) {
        close(fd[0]);
        dup2(STDOUT_FILENO, fd[1]);
        sprintf(string_min, "%i", min);
        sprintf(string_max, "%i", max/2);
        execlp("./esclavo", "esclavo", string_min, string_max, NULL);
    } else if (PID[1] == 0) {
        close(fd[0]);
        dup2(STDOUT_FILENO, fd[1]);
        sprintf(string_min, "%i", max/2+1);
        sprintf(string_max, "%i", max);
        execlp("./esclavo", "esclavo", string_min, string_max, NULL);
    } else {
        close(fd[1]);
        dup2(fd[0], STDOUT_FILENO);
    }

	return 0;
}


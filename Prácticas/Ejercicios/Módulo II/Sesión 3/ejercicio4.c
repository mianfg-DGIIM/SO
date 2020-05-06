#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    int i, estado;
    pid_t PID;
    
    // printf() tan pronto como sea posible
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    
    // creación de hijos
    for (i=0; i<5; i++) {
        if ((PID=fork())<0) {
            perror("Error en fork\n");
            exit(-1);
        }
        
        if (PID==0) {
            printf("Soy PID=%i, el hijo de PPID=%i\n", getpid(), getppid());
            exit(0);
        }
    }
    
    // esperamos hijos
    for (i=4; i>=0; i--) {
        PID = wait(&estado);
        printf("Ha finalizado el hijo con PID=%i", PID);
        printf("Solo me quedan %i hijos vivos\n\n", i);
    }
    
    exit(0);
}

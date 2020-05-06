#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int num_procesos = 20;
    pid_t childpid;

    // Jerarquía tipo 1 //
    for (int i=1; i < num_procesos; i++){
        if ( (childpid = fork()) == -1){
            perror("\nNo pudo crearse el hijo\n");
            exit(-1);
        }


        if (childpid){
            printf("Padre: %d, proceso: %d\n", getppid(), getpid());
            break;
        }
    }
}

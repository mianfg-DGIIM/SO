#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static int seniales[31];

void signal_handler(int i) {
    seniales[i]++;
    printf("La señal %i ha sido recibida %i veces\n", i, seniales[i]);
}

int main(int argc, char* argv[]) {
    setvbuf(stdout,NULL,_IONBF,0);

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;

    for ( int i = 0; i < 31; i++ )
        seniales[i] = 0;
    
    for ( int i = 1; i < 31 && i != SIGSTOP && i != SIGKILL; i++ ) {
        if ( sigaction(i, &sa, NULL) == -1 ) {
            printf("Error en sigaction en i=%i\n", i);
        }
    }
    while(1);
}

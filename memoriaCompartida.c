#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    key_t key = 9849;
    int shmId;
    long long a, b, c, *ap;
    int status, cpid, r, i, tope = 12500000, contador = 0;
    
    //crear espacio de memoria compartida
    shmId = shmget(key, tope * sizeof(long long), 0666 | IPC_CREAT);
    if(shmId < 0){
        perror("Error en shmget");
        exit(-1);
    }
    //asociar espacio de memoria creada a este proceso
    ap = (long long *)shmat(shmId, 0, 0);
    pid = fork();

    if(pid == 0){ //hijo
        for(i = 0; i < tope; i++)
            *(ap + i)= rand();
        
    }
    else{ //padre
    }
    //printf("valor fM: %lli", *(ap + tope - 1));
    r = shmdt(ap);  //desasociar espacio de memoria compartida
    return 0;
    
}
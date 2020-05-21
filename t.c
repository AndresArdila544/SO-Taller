#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define CHARLEN 4

int main()
{

    /*
             bytes         tope
    1kb      1000          125
    10 kb    10000         1250
    100 kb   100000        12500
    1 mb     1000000       125000
    10 mb    10000000      1250000
    100 mb   100000000     12500000
    */

    pid_t pid;
    int r;
    int pipefd[2], tope = 12500000, i;
    char buf[11];
    long long *vector, *vector2;
    vector = (long long *)malloc(tope * sizeof(long long));
    vector2 = (long long *)malloc(tope * sizeof(long long));
    for(i = 0; i < tope; i++)
        vector[i] = rand();
    printf("primer escrito: %lli\n", vector[0]);
    printf("ultimo escrito: %lli\n", vector[tope-1]);
    r = pipe(pipefd);
    if(pipefd < 0){ 
        perror("Error pipe() "); 
        exit(-1);
    }
    pid = fork();
    if (pid == -1){  //handle errors
        perror("fork"); 
        exit(EXIT_FAILURE); 
    }
    
    if(pid == 0){
        //hijo escribe pipe - pipefd[1]
        close(pipefd[0]);
        r = write(pipefd[1], &vector, sizeof(vector));
        if(r != sizeof(vector)){   //handle errors
            perror("error writting pipe"); 
        }
        close(pipefd[1]);
        exit(0);    
    }
    else{ 
      //padre lee pipe - pipefd[0]
        close(pipefd[1]);
        r = read(pipefd[0], &vector2, sizeof(vector2));
        if(r != sizeof(vector2)){   //handle errors
            perror("error reading pipe");
        }
        printf("primer escritoP: %lli\n", vector2[0]);
        printf("ultimo leidoP: %lli \n", vector2[tope-1]);
        close(pipefd[0]); 
        //buf[r] = 0;
        
    }

    return 0;
}
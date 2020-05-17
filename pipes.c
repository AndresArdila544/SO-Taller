#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#define TRANSFER 100000000//bytes

int r, dato, lectura;

int sz = sizeof(int);

void parent_read(int p[])
{
    int nread;

    while (1)
    {

        // read call if return -1 then pipe is
        // empty because of fcntl
        nread = read(p[0], &lectura, sz);
        switch (nread)
        {
        case -1:

            // case -1 means pipe is empty and errono
            // set EAGAIN
            if (errno == EAGAIN)
            {
                printf("(pipe empty)\n");
                sleep(1);
                break;
            }

            else
            {
                perror("read");
                exit(4);
            }

        // case 0 means all bytes are read and EOF(end of conv.)
        case 0:
            printf("\nTransfered %i bytes\n", TRANSFER);
            printf("End of conversation\n");

            exit(0);
        default:
            ;
            //printf("Lectura: %i\n", lectura);
        }
    }
}
void child_write(int p[],int j)
{
    for (int i = 0; i < (j/sz); i++)
    {
        dato = rand();
        r = write(p[1], &dato, sz);
        //printf("\nDato: %i \n", dato);
        //printf("\ni: %i \n", i);
        if (r != sizeof(int))
        { //handle errors
            perror("error writting pipe");
            exit(-1);
        }
    }

    exit(0);
}

int main()
{
    pid_t pid;
    int r;
    int pipefd[2];

    r = pipe(pipefd);
    if (pipefd < 0)
    {
        perror("Error pipe() ");
        exit(-1);
    }
    pid = fork();
    if (pid == -1)
    { //handle errors
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        //hijo escribe pipe - pipefd[1]
        close(pipefd[0]);

        child_write(pipefd, TRANSFER);
        
        close(pipefd[1]);
        exit(0);
    }
    else
    {
        //padre lee pipe - pipefd[0]
        close(pipefd[1]);
        parent_read(pipefd);
        close(pipefd[0]);
        
    }

    



}
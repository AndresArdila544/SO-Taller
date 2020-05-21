#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <signal.h> 

#define TRANSFER 100000000 //bytes

int flag = 0;

void sighup()

{
    signal(SIGHUP, sighup); /* reset signal */
    //printf("CHILD: I have received a SIGHUP\n"); 
    flag = 1;
}

int main()
{
    pid_t pid;
    

    // create pipe pair
    int fd[2];
    pipe(fd);
    int sz = sizeof(int);
    int dato, r;

    pid = fork();
    if (pid == 0)
    {
        // child side
        signal(SIGHUP, sighup);
        int *buff = NULL;

        int bt = 0;
        int count = 0;

        // close write side. don't need it.
        close(fd[1]);

        // read at least one byte from the pipe.
        //printf("r, %zi",read(fd[0], &bt, sizeof(int)));

        while (1)
        {
            
            ioctl(fd[0], FIONREAD, &count);
            if(count>0){
                printf("count, %i\n",count);
            }
            
            if (count >= 10000)
            {
                buff = malloc(count + 1);
                buff[0] = bt;
                r=read(fd[0], buff+1, count);
                if (r != count)
                { //handle errors

                    perror("error reading pipe");
                    exit(-1);
                }
            }
            else if (flag == 1)
            {
                //printf("FLAG!!!");
                ioctl(fd[0], FIONREAD, &count);
                buff = malloc(count + 1);
                r=read(fd[0], buff, count);
                if (r != count)
                { //handle errors

                    perror("error reading pipe");
                    exit(-1);
                }
                break;
            }

        }

        // close our side
        close(fd[0]);
        //fprintf(stdout, "Child: Shutting down.\n");
        printf("\nSent: %i bytes \n", TRANSFER); //4095
    }
    else
    { // close read size. don't need it.
        close(fd[0]);
        //sleep(1); // simulate process wait
        //fprintf(stdout, "Parent sending \n");
        for (int i = 0; i < (TRANSFER / sz); i++)
        {
            dato = rand();
            r = write(fd[1], &dato, sz);

            //printf("\nDato: %i \n", dato);
            //printf("\ni: %i \n", i / sz); //4095
            //printf("\nr: %i \n", r);      //4095

            if (r == -1)
            {
                perror("error writting pipe");
                exit(-1);
            }

            if (r != sizeof(int))
            { //handle errors

                perror("error writting pipe");
                exit(-1);
            }
        }
        kill(0, SIGHUP); 
        //sleep(5); // simulate process wait
        //fprintf(stdout, "Parent: sending \"%s\"\n", msg2);
        //write(fd[1], msg2, sizeof(msg2));
        close(fd[1]);
        //fprintf(stdout, "Parent: Shutting down.\n");
    }
    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main () {

    /*
             bytes         tope
    1kb      1000          125
    10 kb    10000         1250
    100 kb   100000        12500
    1 mb     1000000       125000
    10 mb    10000000      1250000
    100 mb   100000000     12500000
    */

    __pid_t pid;
    int i, r,tope = 12500000;
    long long *vector, *vector2;
    vector = (long long *)malloc(tope * sizeof(long long));
    vector2 = (long long *)malloc(tope * sizeof(long long));

    for(i = 0; i < tope; i++)
        vector[i] = rand();

    /*printf("escrito mitad: %lli\n", vector[tope / 2]);
    printf("escrito ultimo: %lli\n\n", vector[tope-1]);*/

    pid = fork();

    if(pid == 0){

        FILE *archivo2;
		archivo2 = fopen ( "125000005.txt", "r" );
        do
            r = fread(&vector2,sizeof(vector2) , 1, archivo2);
        while (r = 0);
        fclose ( archivo2);
        /*printf("leido mitad: %lli\n", vector2[tope / 2]);
        printf("leido ultimo: %lli\n", vector2[tope-1]);*/

    }
    else{

        FILE *archivo;
		archivo = fopen ( "125000005.txt", "w" );
        fwrite(&vector, sizeof(vector), 1, archivo);
        fclose ( archivo );

    }

    return 0;

}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main () {
     __pid_t pid;
    int i, contador = 0, tope = 12500;
    long long dato, bandera, leido;

    pid= fork();

    if(pid == 0){
        FILE *archivo2;
		archivo2 = fopen ( "datos.dat", "rb" );
        while(bandera == 0){
            fseek(archivo2, 0, SEEK_SET);
            fread(&bandera,sizeof(bandera) , 1, archivo2);
            //printf("fuera\n");
        }
        fseek(archivo2, 0, SEEK_SET);
        for(i = 0; i < tope; i++){
            fread(&leido,sizeof(leido) , 1, archivo2);
            //printf("leido: %lld\n", leido);
            contador++;
        }
        fclose ( archivo2);
        //printf("contador %i", contador);
        printf("Se leyeron %i datos.\n%i * 8 bytes = %i bytes.\n", contador, contador, (contador * 8));
    }
    else{
        FILE *archivo;
		archivo = fopen ( "datos.dat", "wb" );
        for(i = 0; i < tope; i++){
            dato = rand();
		    fwrite(&dato, sizeof(dato), 1, archivo);
            //printf("Dato %lld\n", dato);
        }
		fclose ( archivo );
    }
    return 0;
}
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include<signal.h> 

#define PORT 3535 
#define BACKLOG 2
//ACA DICEN EL NUMERO DE BYTES SIN DIVISION
#define size 100000
int client;

void handle_sigint(int sig) 
{ 
    close(client);
    printf("Programa terminado\n"); 
    exit(-1);

} 

void printAr( char * data){
	for(int i=0;i<sizeof(data);i++){
	 	printf("Datos rec: %c\n",data[i]);
	}	
}

int main(int argc,char *argv[]){
	
	signal(SIGINT, handle_sigint); 
	client = socket(AF_INET, SOCK_STREAM, 0);
	
	//address for the socket
	struct sockaddr_in client_add;
	client_add.sin_family= AF_INET;
	client_add.sin_port= htons(PORT);
	inet_aton(argv[1],&client_add.sin_addr);
	
	//bind
	int status=connect(client,(struct sockaddr *)&client_add, sizeof(client_add));
	if(status <0){
		perror("error bind");
		exit(-1);
	}
	
     
	//receive

	static char * data;
	data= (char *) malloc(size);
	int d=0;

	while (d != size){
		d+=recv(client,data, size,0);
		printf("Size of data %ld\n", sizeof(data));
		
	}

	printf("Bytes recibidos %d\n", d);
	close(client);


}






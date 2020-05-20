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
	char * data;
	int bytes = size;
	data = (char *) malloc(bytes);

	int d;
	while((d=recv(client, data, bytes,0)) != bytes){
		if (d<0){
			perror("Error rcv");
		}
	}

	for (int i=0; i<bytes;i++){
		printf("Rec %c\n",data[i]);
	}


	close(client);


}

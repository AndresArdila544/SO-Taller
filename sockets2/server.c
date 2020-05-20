#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<signal.h> 
#define PORT 3535 
#define BACKLOG 2
//ACA DICEN EL NUMERO DE BYTES SIN DIVISION
#define size 100000

int client;
int server;
void handle_sigint(int sig) 
{ 
    close(client);
    close(server);
    printf("Programa terminado\n"); 
    exit(-1);

} 


int main(){

	signal(SIGINT, handle_sigint); 
	server = socket(AF_INET, SOCK_STREAM, 0);
	//address for the socket
	struct sockaddr_in server_add;
	server_add.sin_family= AF_INET;
	server_add.sin_port= htons(PORT);
	server_add.sin_addr.s_addr= INADDR_ANY;
	//bind
	int status=bind(server,(struct sockaddr *)&server_add,sizeof(server_add));
	if(status <0){
		perror("error bind");
		exit(-1);
	}
	//listen
	int r= listen(server,BACKLOG);
	
	if(r<0){
		perror("error listen");
		exit(-1);
	}

	//accept
	struct sockaddr_in client_add;
	int addlen= sizeof(client_add);
	client= accept(server,(struct sockaddr *)&client_add, (socklen_t*)&addlen);
	
	//send

	char * data;
	int bytes = size;
	data = (char *) malloc(bytes);
	for(int i=0;i<bytes;i++){
	 data[i] = 'a';
	 printf("Tengo: %c\n",data[i]);
	}
	int d;
	while((d=send(client,data,bytes,0)) != bytes){
		if(d<0){
		perror("error send");
		}
	}

	close(client);
	close(server);


}

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
//ACA CAMBIAN EL SIZE ASI = #BYTES/8
#define size 1250000
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
	/*
	static long long array[size];
	int d=0;
	while(array[100000]==0){
		printf("hola\n");
		recv(client, &array, sizeof(array) ,0);
	}
	for(int i=0; i< size; i++){
		printf("Recibi %d, %lld\n", i, array[i]);
	}
	*/
	static long long num;

	for (int i=0; i<size ; i++){
		recv(client, &num, sizeof(long long) ,0);
		//printf("Recibi %d, %lld\n", i, num);
	}
	//printf( "Termine :)");
	

	
	close(client);


}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include "menu.h"

void server(char* argv[]);

// gcc -o server server.o menu.o
int main(int argc, char* argv[]){

	server(argv);

	return 0;
}

void errorHandling(char* msg){
	fputs(msg, stderr);
	fputc('\n',stderr);
	exit(1);
}

void server(char* argv[]){
	/*
	socket() -> bind() -> listen()->
	accept() -> read()/write() -> finished? -> close()
	*/

	int serverSocket;

	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;

	serverSocket = socket(PF_INET, SOCK_STREAM,0);
	if(serverSocket == -1){
		errorHandling("Socket error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(atoi(argv[1]));

	if(bind(serverSocket, (struct sockaddr*)&servAddr, sizeof(servAddr))==-1){
		errorHandling("Bind error");
	}

	if(listen(serverSocket, 5)==-1){
		errorHandling("Listen error");		
	}

	socklen_t clntAddrSize = sizeof(clntAddr);
	while(1){
		int clientSocket = accept(serverSocket, (struct sockaddr*)&clntAddr, &clntAddrSize);
		if(clientSocket == -1){
			errorHandling("Accept error");
		}
		// char data[100];
		// sprintf(data,"%d",menu.hambergerIdx);
		// if(write(clientSocket, data, strlen(data)+1)==-1){
		// 	errorHandling("Send error");
		// }
	
		// int i;
		// for(i=0;i<menu.hambergerIdx;i++){
		// 	if(send(clientSocket,(struct Node*)&(menu.hamberger[i]), sizeof(menu.hamberger[i]),0)==-1){
		// 		errorHandling("Send error");
		// 	}	
		// }
		close(clientSocket);
	}
	close(serverSocket);
}	

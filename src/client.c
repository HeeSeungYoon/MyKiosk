#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include "client.h"
#include "menu.h"

void errorHandling(char* msg){
	fputs(msg, stderr);
	fputc('\n',stderr);
	exit(1);
}

int* client(char* argv[]){
	int* clientSocket;
	
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;

	*clientSocket = socket(PF_INET, SOCK_STREAM,0);
	if(*clientSocket == -1){
		errorHandling("Socket error");
	}

	memset((char*)&servAddr, '\0', sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if(connect(*clientSocket, (struct sockaddr *)&servAddr, sizeof(servAddr))== -1){
		errorHandling("Connect error");
	}

	return clientSocket;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include "client.h"
#include "menu.h"

Menu menu;

void errorHandling(char* msg){
	fputs(msg, stderr);
	fputc('\n',stderr);
	exit(1);
}

void client(char* argv[]){
	int clientSocket;
	
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;

	clientSocket = socket(PF_INET, SOCK_STREAM,0);
	if(clientSocket == -1){
		errorHandling("Socket error");
	}

	memset((char*)&servAddr, '\0', sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if(connect(clientSocket, (struct sockaddr *)&servAddr, sizeof(servAddr))== -1){
		errorHandling("Connect error");
	}

	char buff[100];
	read(clientSocket, buff, sizeof(buff));
	menu.hambergerIdx = atoi(buff);
	printf("hambergerIdx = %d\n",menu.hambergerIdx);

	int i;
	for(i=0;i<menu.hambergerIdx;i++){
		if(recv(clientSocket, (struct Node*)&menu.hamberger[i], sizeof(menu.hamberger[i]),0)==-1){
			errorHandling("Receive error");
		}
	}

	for(i=0;i<menu.hambergerIdx;i++){
		printf("%s %s\n",menu.hamberger[i].name, menu.hamberger[i].price);
	}

	printMenu(&menu);

	close(clientSocket);
}
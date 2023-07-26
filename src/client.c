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

void client(char* argv[], char** order_name, int* order_price, int* order_num, int order_cnt, char* today){
	timer_t time;
	int client_socket;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	client_socket = socket(PF_INET, SOCK_STREAM,0);
	if(client_socket == -1){
		errorHandling("Socket error");
	}

	memset((char*)&serv_addr, '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr))== -1){
		errorHandling("Connect error");
	}

	// 오늘 날짜 송신
	if(write(client_socket, today, strlen(today)+1)==-1){
		errorHandling("Send error");
	}
	usleep(1000);

	// 장바구니 index 송신
	int cnt = htonl(order_cnt);
	if(write(client_socket, &cnt, sizeof(cnt))==-1){
		errorHandling("Send error");
	}
	usleep(1000);

	// 구매 가격 송신
	int i;
	int* array_to_send = (int*)malloc(sizeof(int)*order_cnt);
	for(i=0;i<order_cnt;i++){
		array_to_send[i] = htonl(order_price[i]);
	}
	if(write(client_socket, array_to_send, sizeof(int)*order_cnt)==-1){
		errorHandling("Send error");
	}
	usleep(1000);

	// 구매 개수 송신
	for(i=0;i<order_cnt;i++){
		array_to_send[i] = htonl(order_num[i]);
	}
	if(write(client_socket, array_to_send, sizeof(int)*order_cnt)==-1){
		errorHandling("Send error");
	}

	// 구매 이름 송신
	for(i=0;i<order_cnt;i++){
		if(write(client_socket, order_name[i], strlen(order_name[i])+1)==-1){
			errorHandling("Send error");
		}
		usleep(1000);
	}

	close(client_socket);	

}
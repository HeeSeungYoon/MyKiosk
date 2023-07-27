#include <stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <ncurses.h>
#include "serv_init.h"
#include "menu.h"

#define ENTER 10
#define ESC 27

int category_sales[7];
static int sales[12][31];
static int cnt;

char order_name[100][100];
int order_price[100];
int order_num[100];
char today[100];
int order_cnt;

void init(){
    setlocale(LC_ALL, "ko_KR.utf8");
	
	initscr();
	keypad(stdscr, TRUE);
	noecho();

	if(has_colors() == FALSE){
		endwin();
		printf("Your Terminal does not support color\n");
		exit(1);
	}

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_WHITE);
	curs_set(0);
}

void init_sales_and_cart(){
    int i;
    for(i=0;i<7;i++){
        category_sales[i] = 0;
    }
    cnt = 0;
    order_cnt = 0;
    for(i=0;i<100;i++){
        order_price[i] = 0;
        order_num[i] = 0;
    }   
}

void print_order(){
    int i;
    for(i=cnt;i<cnt+order_cnt;i++){
        mvprintw((i%(LINES-5)),COLS/4*(i/(LINES-5)),"%s : %s x%d %d원",today, order_name[i],order_num[i], order_price[i]*order_num[i]);
    }
    cnt = order_cnt;
}

void revenue(int month, int day){
    int category_idx;
    int menu_idx;

    int i=0;
    while(i<order_cnt){
        int flag = 0;
        for(category_idx=0;category_idx<7;category_idx++){
            for(menu_idx=0;menu_idx<menu_num[category_idx];menu_idx++){
                if(strcmp(order_name[i], menu_name[category_idx][menu_idx])==0){
                    category_sales[category_idx] += order_price[i]*order_num[i];
                    sales[month-1][day-1]+=order_price[i]*order_num[i];
                    flag = 1;
                    break;
                }
            }
            if(flag==1) break;
        }
        i++;
    }
}

void print_revenue(int month, int day){
    revenue(month, day);
    clear();
    mvprintw(2, COLS/2-9, "카테고리별 일 매출");
    move(4, COLS/3);
    hline('=',COLS/3);
    int i;
    for(i=0;i<7;i++){
        mvprintw(6+2*i, COLS/3, "%s : ", category_name[i]);
        mvprintw(6+2*i, COLS/3*2-10, "%d원",category_sales[i]);
    }
    move(20, COLS/3);
    hline('=',COLS/3);
    mvprintw(22, COLS/3, "총 매출 :");
    mvprintw(22, COLS/3*2-10, "%d원",sales[month-1][day-1]);
    attrset(COLOR_PAIR(1));
    mvprintw(25, COLS/2, "확인");
    attroff(COLOR_PAIR(1));
    refresh();

    if(getch()==ENTER){
        clear();
        return;
    }
}

void initUI(int month, int day){
    print_order();
    move(LINES-4,0);
    hline('=',COLS);
    attrset(COLOR_PAIR(1));
    mvprintw(LINES-2, COLS/2, "일 매출 정산");
    attroff(COLOR_PAIR(1));
    refresh();

    int key = getch();
    if(key == ENTER){
        print_revenue(month, day);
        init_sales_and_cart();
        return;
    }
}

void errorHandling(char* msg){
	fputs(msg, stderr);
	fputc('\n',stderr);
	exit(1);
}

void server(char* argv[]){

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);  
	int server_socket;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	server_socket = socket(PF_INET, SOCK_STREAM,0);
	if(server_socket == -1){
		errorHandling("Socket error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
		errorHandling("Bind error");
	}

	if(listen(server_socket, 5)==-1){
		errorHandling("Listen error");		
	}

	socklen_t clnt_addr_size = sizeof(clnt_addr);
    
    init();
    init_sales_and_cart();
    int month = tm.tm_mon+1;
    int day = tm.tm_mday;
    while(1){
        print_order();
        move(LINES-4,0);
        hline('=',COLS);
        attrset(COLOR_PAIR(1));
        mvprintw(LINES-2, COLS/2, "일 매출 정산");
        attroff(COLOR_PAIR(1));
        refresh();

        int client_socket = accept(server_socket, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(client_socket == -1){
            errorHandling("Accept error");
        }    
        
        // 오늘 날짜 수신
        if(read(client_socket, today, 100)==-1){
            errorHandling("Recv error");
        }

        // 장바구니 index 수신    
        if(read(client_socket, &order_cnt, sizeof(order_cnt))==-1){
            errorHandling("Recv error");
        }
        order_cnt = ntohl(order_cnt);

        // 구매 가격 수신
        int i;
        int* array_to_recv = (int*)(malloc)(sizeof(int)*order_cnt);
        if(read(client_socket, array_to_recv, sizeof(int)*order_cnt)==-1){
            errorHandling("Recv error");
        }
        for(i=0;i<order_cnt;i++){
            order_price[i] = ntohl(array_to_recv[i]);
        }

        // 구매 개수 수신
        if(read(client_socket, array_to_recv, sizeof(int)*order_cnt)==-1){
            errorHandling("Recv error");
        }
        for(i=0;i<order_cnt;i++){
            order_num[i] = ntohl(array_to_recv[i]);
        }

            // 구매 이름 수신
        for(i=0;i<order_cnt;i++){
            if(read(client_socket, order_name[i], 100)==-1){
                errorHandling("Recv error");
            }
        }
        close(client_socket);
        initUI(month, day);
    }
	close(server_socket);
}	

#include <time.h>
#include <stdio.h>
#include "clnt_init.h"
#include "order.h"
#include "payment.h"
//#include "client.h"

// sudo apt-get install libncurses5-dev libncursesw5-dev 
// gcc -o client client.o init.o -lncursesw

int main(int argc, char* argv[]){

	time_t t = time(NULL);
    struct tm tm = *localtime(&t);

	int order_cnt=0;
	char* order_name[100];
	int order_price[100];
	int order_num[100];
	int order_size[100];

	char* today;

	int mainscr;

	while((mainscr=initUI()) != 1){
		//client(argv);

		order_cnt = order_process(order_name, order_price, order_num, order_size);
		
		if(order_cnt == 0) continue;
		else{
			sprintf(today, "%d-%d-%d %d:%d:%d",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			print_bill(order_name, order_price, order_num, order_size, order_cnt,today);
		}
	}
	return 0;
}

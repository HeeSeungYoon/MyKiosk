#ifndef SERV_INIT_H_
#define SERV_INIT_H_

extern int category_sales[7];

void init();
void init_sales_and_cart();
void print_order();
void revenue(int month, int day);
void print_revenue(int month, int day);
void initUI(int month, int day);
void errorHandling(char* msg);
void server(char* argv[]);

#endif
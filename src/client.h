#ifndef CLIENT_H_
#define CLIENT_H_

void errorHandling(char* msg);
void client(char* argv[], char** order_name, int* order_price, int* order_num, int order_cnt, char* today);

#endif
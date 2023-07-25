#ifndef ORDER_H_
#define ORDER_H_

// 장바구니

void init_cart(char** name, int* price, int* num, int* size);
void print_category(int idx, int color);
void print_one_menu(int category, int idx);
void print_size3(int category, int menu, int* size);
void print_size4(int category, int menu, int* size);
void print_size(int category, int menu, int* size);
void print_num(int* num);
void print_order_complete(int idx, int EXIT);
void print_cart(char** order_name, int* order_size, int* order_num, int cnt);
int order_process(char** name, int* price, int* num, int* size);

#endif
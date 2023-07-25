#ifndef PAYMENT_H_
#define PAYMENT_H_

extern char* membership[3];

int discount(int* total_price, double discount_grade);
int print_discount_grade(int idx);
void print_order(char** order_name, int* order_price, int* order_num, int* order_size, int cnt, int* total_price, int isDiscount);
void print_payment(int idx, int isDiscount);
void print_payment_complete();
void print_bill(char** order_name, int* order_price, int* order_num, int* order_size, int cnt, char* today);

#endif
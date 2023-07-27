#include <ncurses.h>
#include <time.h>
#include <string.h>
#include "menu.h"

#define ENTER 10
#define ESC 27

char* membership[3] = {"Welcome", "Green", "Gold"};
double grade_discount[3] = {0, 0.05, 0.1};

int discount(int* total_price, double discount_grade){
    double discount = (double)(*total_price) * discount_grade;
    return (int)(discount);
}

int print_discount_grade(int idx){
    mvprintw(LINES/2-1,COLS/2, "멤버쉽 등급");
    if(idx == 0){
        attrset(COLOR_PAIR(1));
        mvprintw(LINES/2+1,COLS/4,"Welcome");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES/2+1,COLS/2,"Green");
        mvprintw(LINES/2+1,COLS/4*3,"Gold");
    }else if(idx == 1){
        mvprintw(LINES/2+1,COLS/4,"Welcome");
        attrset(COLOR_PAIR(1));
        mvprintw(LINES/2+1,COLS/2,"Green");
        attroff(COLOR_PAIR(1));
        mvprintw(LINES/2+1,COLS/4*3,"Gold");
    } else if(idx == 2){
        mvprintw(LINES/2+1,COLS/4,"Welcome");
        mvprintw(LINES/2+1,COLS/2,"Green");
        attrset(COLOR_PAIR(1));
        mvprintw(LINES/2+1,COLS/4*3,"Gold");
        attroff(COLOR_PAIR(1));
    }
}

void print_order(char** order_name, int* order_price, int* order_num, int* order_size, int cnt, int* total_price, int isDiscount, int grade){
    int i;
    for(i=0;i<cnt;i++){
        mvprintw(6+2*i, COLS/3, "%s(%s) x%d",order_name[i],menu_size[order_size[i]],order_num[i]);
        mvprintw(6+2*i, COLS/3*2-10, "%d원",order_price[i]*order_num[i]);
    }
    move(8+2*cnt, COLS/3);
    hline('=',COLS/3);
    if(isDiscount == 0){
        mvprintw(10+2*cnt, COLS/3, "총 금액 :");
        mvprintw(10+2*cnt, COLS/3*2-10, "%d원",*total_price);
    }else if(isDiscount==1){
        int discount_price = 0;
        discount_price = discount(total_price, grade_discount[grade]);
        mvprintw(10+2*cnt, COLS/3, "멤버쉽 등급 : %s", membership[grade]);
        mvprintw(11+2*cnt, COLS/3, "할인된 금액 :");
        mvprintw(11+2*cnt, COLS/3+COLS/6-10, "%d원",discount_price);
        mvprintw(11+2*cnt, COLS/3+COLS/6, "총 금액 :");
        mvprintw(11+2*cnt, COLS/3*2-10, "%d원",*total_price-discount_price);
    }
}

void print_payment(int idx, int isDiscount){
    if(isDiscount==0){
        if(idx == 0){
            attrset(COLOR_PAIR(1));
            mvprintw(LINES-2, COLS/3, "멤버쉽 할인");
            attroff(COLOR_PAIR(1));
            mvprintw(LINES-2, COLS/3*2, "계산하기");
        }else if(idx == 1){
            mvprintw(LINES-2, COLS/3, "멤버쉽 할인");
            attrset(COLOR_PAIR(1));
            mvprintw(LINES-2, COLS/3*2, "계산하기");
            attroff(COLOR_PAIR(1));
        }
    }else if(isDiscount==1){
        attrset(COLOR_PAIR(1));
        mvprintw(LINES-2, COLS/2, "계산하기");
        attroff(COLOR_PAIR(1));
    }
   
}

void print_payment_complete(){
    
    mvprintw(LINES/2-3, COLS/2-15, "┌");
    move(LINES/2-3, COLS/2-14);
    hline('-',29);
    mvprintw(LINES/2-3, COLS/2+15, "┐");
    move(LINES/2-2, COLS/2+15);
    vline('|',5);
    mvprintw(LINES/2+3, COLS/2+15, "┘");
    move(LINES/2+3, COLS/2-14);
    hline('-',29);
    mvprintw(LINES/2+3, COLS/2-15, "└");
    move(LINES/2-2, COLS/2-15);
    vline('|',5);
    
    mvprintw(LINES/2, COLS/2-11, "계산이 완료되었습니다.");
    refresh();

    int key = getch();

    if(key == ENTER){
        return;
    }
}

void print_bill(char** order_name, int* order_price, int* order_num, int* order_size, int cnt, char* today){

    int total_price=0;
    int isDiscount = 0;
    int payment_idx = 0;
    int grade = 0;

    int i;
    for(i=0;i<cnt;i++){
        total_price += order_price[i] * order_num[i];
    }
    
    while(1){
        //clear();
        mvprintw(2, COLS/2-2-strlen(today)/2, "주문 내역 %s",today);
        move(4,COLS/3);
        hline('=',COLS/3);
        print_order(order_name, order_price, order_num, order_size, cnt, &total_price, isDiscount, grade);
        print_payment(payment_idx, isDiscount);
        refresh();

        int key = getch();

        if(key == KEY_RIGHT){
            if(payment_idx < 1) payment_idx++;
            else payment_idx = 1;
        }else if(key == KEY_LEFT){
            if(payment_idx <= 0) payment_idx=0;
            else payment_idx--;
        }

        if(key == ENTER && payment_idx == 0){
            while(1){
                print_discount_grade(grade);
                refresh();

                int key = getch();
                if(key == KEY_RIGHT){
                    if(grade > 1) grade = 2;
                    else grade++;
                }else if(key == KEY_LEFT){
                    if(grade <=0) grade =0;
                    else grade--;
                }

                if(key == ENTER){
                    isDiscount = 1;
                    payment_idx = 1;
                    break;
                }else if(key == ESC){
                    isDiscount = 0;
                    payment_idx = 0;
                    break;
                }
            }
            clear();
        }else if(key == ENTER && payment_idx==1){
            print_payment_complete();
            clear();
            return;
        }
    }
}

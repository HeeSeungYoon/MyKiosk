#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "order.h"
#include "menu.h"

#define ENTER 10
#define ESC 27

void init_cart(char** name, int* price, int* num, int* size){
     int i;
     for(i=0;i<100;i++){
        name[i]="";
        price[i] = 0;
        num[i] = 0;
        size[i]=0;
    }
}

void print_category(int idx, int color){
    int i;
    

     for(i=0;i<7;i++){
        if(i == idx && color == 1){
            attrset(COLOR_PAIR(1));
        }else{
            attroff(COLOR_PAIR(1));
        }
        move(0, COLS/7*i);
        printw("%d. %s",i+1, category_name[i]);
    }
    
    attroff(COLOR_PAIR(1));
    move(2,0);
    hline('=',COLS);
    
}

void print_one_menu(int category, int idx){
    int i;
    for(i=0;i<menu_num[category];i++){
        if(category == 6)
            move(4+LINES/18*i, COLS/7*category-7);
        else 
            move(4+LINES/18*i, COLS/7*category);
        if(i == idx){
            attrset(COLOR_PAIR(1));
        }else
            attroff(COLOR_PAIR(1));
        printw("%d. %s",i+1, menu_name[category][i]);

        attroff(COLOR_PAIR(1));
        if(category == 6){
            move(5+LINES/18*i, COLS/7*category);
            printw("%d원(Grande)",menu_price[category][i]); 
        }
        else{
            move(5+LINES/18*i, COLS/7*category+COLS/14);
            if(category == 0 && i>10)
                printw("%d원(Short)",menu_price[category][i]);
            else
                printw("%d원(Tall)",menu_price[category][i]);
        }   
    }
}

void print_size3(int category, int menu, int* size){
    int tall = 0; 
    int grande =0; 
    int venti = 0; 
    if(category == 6){
        tall = menu_price[category][menu]-500;
        grande = menu_price[category][menu];
        venti = menu_price[category][menu]+500;
    }
    else{
        tall = menu_price[category][menu];
        grande = menu_price[category][menu]+500;
        venti = menu_price[category][menu]+1000;
    }
    if(*size <= 1){
        *size = 1;
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",tall);
        attroff(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/2);
        printw("Grande %d원",grande);
        move(5+LINES/18*11, COLS/8*5);
        printw("Venti %d원",venti);
    }else if(*size == 2){
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",tall);
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/2);
        printw("Grande %d원",grande);
        attroff(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*5);
        printw("Venti %d원",venti);
    }else if(*size == 3){
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",tall);
        move(5+LINES/18*11, COLS/2);
        printw("Grande %d원",grande);
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*5);
        printw("Venti %d원",venti);
        attroff(COLOR_PAIR(1));
    }
}
void print_size4(int category, int menu, int* size){
    if(*size == 0){
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8);
        printw("Short %d원",menu_price[category][menu]-500);
        attroff(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",menu_price[category][menu]);
        move(5+LINES/18*11, COLS/8*5);
        printw("Grande %d원",menu_price[category][menu]+500);
        move(5+LINES/18*11, COLS/8*7);
        printw("Venti %d원",menu_price[category][menu]+1000);
    }else if(*size == 1){
        move(5+LINES/18*11, COLS/8);
        printw("Short %d원",menu_price[category][menu]-500);
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",menu_price[category][menu]);
        attroff(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*5);
        printw("Grande %d원",menu_price[category][menu]+500);
        move(5+LINES/18*11, COLS/8*7);
        printw("Venti %d원",menu_price[category][menu]+1000);
    }else if(*size == 2){
        move(5+LINES/18*11, COLS/8);
        printw("Short %d원",menu_price[category][menu]-500);
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",menu_price[category][menu]);
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*5);
        printw("Grande %d원",menu_price[category][menu]+500);
        attroff(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*7);
        printw("Venti %d원",menu_price[category][menu]+1000);
    }else if(*size == 3){
        move(5+LINES/18*11, COLS/8);
        printw("Short %d원",menu_price[category][menu]-500);
        move(5+LINES/18*11, COLS/8*3);
        printw("Tall %d원",menu_price[category][menu]);
        move(5+LINES/18*11, COLS/8*5);
        printw("Grande %d원",menu_price[category][menu]+500);
        attrset(COLOR_PAIR(1));
        move(5+LINES/18*11, COLS/8*7);
        printw("Venti %d원",menu_price[category][menu]+1000);
        attroff(COLOR_PAIR(1));
    }
}
void print_size(int category, int menu, int* size){

    if(category == 0 || category == 3){
        if(menu <= 6){
            print_size4(category, menu, size);
        }else if(menu == 7){
            *size = 1;
            attrset(COLOR_PAIR(1));
            move(5+LINES/18*11, COLS/2-COLS/7);
            printw("Tall %d원",menu_price[category][menu]);
            attroff(COLOR_PAIR(1));
        }else if(7<menu && menu<=10){
             if(*size == 0){
                attrset(COLOR_PAIR(1));
                move(5+LINES/18*11, COLS/3);
                printw("Short %d원",menu_price[category][menu]-500);
                attroff(COLOR_PAIR(1));
                move(5+LINES/18*11, COLS/3*2);
                printw("Tall %d원",menu_price[category][menu]);
            }else if(*size >= 1){
                *size = 1;  
                move(5+LINES/18*11, COLS/3);
                printw("Short %d원",menu_price[category][menu]-500);
                attrset(COLOR_PAIR(1));
                move(5+LINES/18*11, COLS/3*2);
                printw("Tall %d원",menu_price[category][menu]);
                attroff(COLOR_PAIR(1));
            }
        }else if(menu>10){
            *size = 0;
            attrset(COLOR_PAIR(1));
            move(5+LINES/18*11, COLS/2-COLS/7);
            printw("Short %d원",menu_price[category][menu]);
            attroff(COLOR_PAIR(1));
        }
    }else{
        if(category == 1){
            if(menu <= 3){
                print_size3(category, menu, size);
            }else{
                 if(*size <= 1){
                    *size = 1;
                    attrset(COLOR_PAIR(1));
                    move(5+LINES/18*11, COLS/3);
                    printw("Tall %d원",menu_price[category][menu]);
                    attroff(COLOR_PAIR(1));
                    move(5+LINES/18*11, COLS/3*2);
                    printw("Grande %d원",menu_price[category][menu]+500);
                }else if(*size >= 2){
                    *size = 2;
                    move(5+LINES/18*11, COLS/3);
                    printw("Tall %d원",menu_price[category][menu]);
                    attrset(COLOR_PAIR(1));
                    move(5+LINES/18*11, COLS/3*2);
                    printw("Grande %d원",menu_price[category][menu]+500);
                    attroff(COLOR_PAIR(1));
                }
            }
        }else if(category == 6){
            if(menu <= 7){
                print_size3(category, menu, size);
            }else if(menu > 7 && menu <= 14){
                if(*size <= 1){
                    *size = 1;
                    attrset(COLOR_PAIR(1));
                    move(5+LINES/18*11, COLS/3);
                    printw("Tall %d원",menu_price[category][menu]-500);
                    attroff(COLOR_PAIR(1));
                    move(5+LINES/18*11, COLS/3*2);
                    printw("Grande %d원",menu_price[category][menu]);
                }else if(*size >= 2){
                    *size = 2;
                    move(5+LINES/18*11, COLS/3);
                    printw("Tall %d원",menu_price[category][menu]-500);
                    attrset(COLOR_PAIR(1));
                    move(5+LINES/18*11, COLS/3*2);
                    printw("Grande %d원",menu_price[category][menu]);
                    attroff(COLOR_PAIR(1));
                }
            }
            else{
                attrset(COLOR_PAIR(1));
                move(5+LINES/18*11, COLS/2-COLS/7);
                printw("Grande %d원",menu_price[category][menu]);
                attroff(COLOR_PAIR(1));
            }
        }else{
            print_size3(category,menu,size);
        }
    } 
}

void print_num(int* num){
    move(5+LINES/18*11, COLS/2-12);
    printw("구매 개수 : ");
    move(4+LINES/18*11, COLS/2+4);
    printw("▲");
    move(5+LINES/18*11, COLS/2+2);
    printw("%3d",*num);
    move(6+LINES/18*11, COLS/2+4);
    printw("▼");

}

void print_order_complete(int idx, int EXIT){
    if(EXIT == 0){
        if(idx == 0){
            attrset(COLOR_PAIR(1));
            move(LINES-2, COLS/4);
            printw("장바구니 담기");
            attroff(COLOR_PAIR(1));
            move(LINES-2, COLS/2);
            printw("계산하기");
            move(LINES-2, COLS/4*3);
            printw("주문 취소");
        }else if(idx == 1){
            move(LINES-2, COLS/4);
            printw("장바구니 담기");
            attrset(COLOR_PAIR(1));
            move(LINES-2, COLS/2);
            printw("계산하기");
            attroff(COLOR_PAIR(1));
            move(LINES-2, COLS/4*3);
            printw("주문 취소");
        }else if(idx == 2){
            move(LINES-2, COLS/4);
            printw("장바구니 담기");
            move(LINES-2, COLS/2);
            printw("계산하기");
            attrset(COLOR_PAIR(1));
            move(LINES-2, COLS/4*3);
            printw("주문 취소");
            attroff(COLOR_PAIR(1));
        }
    }else if(EXIT == 1){
        if(idx == 1){
            attrset(COLOR_PAIR(1));
            move(LINES-2, COLS/3);
            printw("계산하기");
            attroff(COLOR_PAIR(1));
            move(LINES-2, COLS/3*2);
            printw("주문 취소");
        }else if(idx == 2){
            move(LINES-2, COLS/3);
            printw("계산하기");
            attrset(COLOR_PAIR(1));
            move(LINES-2, COLS/3*2);
            printw("주문 취소");
            attroff(COLOR_PAIR(1));
        }
    }
}

void print_cart(char** order_name, int* order_size, int* order_num, int cnt){
    int i;
    for(i=0;i<cnt;i++){
        move(LINES-4+(i/5),COLS/5*(i%5));
        printw("%s(%s)x%d",order_name[i], menu_size[order_size[i]], order_num[i]);
    }
}

int order_process(char** order_name, int* order_price, int* order_num, int* order_size){

    int cnt=0;
    init_cart(order_name, order_price, order_num, order_size);

    clear();
    
    int category=0;
    int menu = -1;
    int size = 1;
    int num = 1;
    int isColor = 1;

    while(1){
        // 메뉴 선택
        if(menu > -1) isColor=0;
        else isColor = 1;

        clear();
        print_category(category,isColor);
        print_one_menu(category, menu);    
        move(LINES-5,0);
        hline('=',COLS);
        print_cart(order_name, order_size, order_num, cnt);
        refresh();

        int key = getch();

         if(key == ESC && cnt == 0){
            clear();
            break;
        }

        if(key == KEY_RIGHT){
            menu = -1;
            if(category>5) category = 6;
            else category++;
        }else if(key == KEY_LEFT){
            menu = -1;
            if(category > 0) category--;
            else category=0;
        }else if(key == KEY_DOWN){
            if(menu >= menu_num[category]-1){
                menu = menu_num[category]-1;
            }else
                menu++;
        }else if(key == KEY_UP){
            if(menu < 0){
                menu = -1;
            }else{
                menu--;
            }
        }

        int EXIT = 0;
        int order = 0;    
        
        if(key == ENTER && menu > -1){       
            // 사이즈 선택
            while(1){
                print_category(category,0);
                print_one_menu(category,-1);    
                move(LINES-5,0);
                hline('=',COLS);
                print_cart(order_name, order_size, order_num, cnt);
                print_size(category, menu, &size);
                refresh();

                key = getch();
                
                if(key == KEY_RIGHT){
                    if(size > 2) size = 3;
                    else size++;
                }
                else if(key == KEY_LEFT){
                    if(size <= 0) size = 0;
                    else size--;
                }
                
                if(key == ESC){
                    EXIT = 1;
                    break;
                }
                
                if(key == ENTER){           
                    break;
                }
            }
            if(EXIT == 1) continue;

            // 개수 선택
            while(1){
                clear();
                print_category(category,0);
                print_one_menu(category,-1);    
                move(LINES-5,0);
                hline('=',COLS);
                print_cart(order_name, order_size, order_num, cnt);
                print_num(&num);
                refresh();

                key = getch();

                if(key == KEY_UP){
                    num++;
                }else if(key == KEY_RIGHT){
                    num+=10;
                }else if(key == KEY_LEFT){
                    if(num >= 11) num -=10;
                }
                else if(key == KEY_DOWN){
                    if(num <= 1) num = 1;
                    else num--;
                }

                if(key == ESC){
                    EXIT = 1;
                    break;
                }
                if(key == ENTER){
                    break;
                }
            }
            if(EXIT == 1) continue;

            // 계산하러 가기    
            while(1){
                clear();
                print_category(category,0);
                print_one_menu(category,-1);    
                move(LINES-5,0);
                hline('=',COLS);
                print_cart(order_name, order_size, order_num, cnt);
                print_order_complete(order,EXIT);            
                refresh();

                key = getch();
                if(key == KEY_RIGHT){
                    if(order > 1) order = 2;
                    else order++;
                }else if(key == KEY_LEFT){
                    if(order <= 0) order = 0;
                    else order--;
                }   

                if(order == 0 && key == ENTER){
                    clear();
                    order_name[cnt] = menu_name[category][menu];
                    if(category == 6) order_price[cnt] = menu_price[category][menu]+500*(size-2);
                    else if(category == 0 && menu > 10) order_price[cnt] = menu_price[category][menu];
                    else order_price[cnt] = menu_price[category][menu]+500*(size-1);
                    order_size[cnt] = size;
                    order_num[cnt] = num;
                    cnt++;
                    break;
                }else if(order == 1 && key == ENTER){
                    clear();
                    order_name[cnt] = menu_name[category][menu];
                    if(category == 6) order_price[cnt] = menu_price[category][menu]+500*(size-2);
                    else if(category == 0 && menu > 10) order_price[cnt] = menu_price[category][menu];
                    else order_price[cnt] = menu_price[category][menu]+500*(size-1);
                    order_size[cnt] = size;
                    order_num[cnt] = num;
                    cnt++;
                    return cnt;
                }
                else if(order == 2 && key == ENTER){
                    clear();
                    cnt = 0;
                    break;
                }
            }
        }

        if(key == ESC && cnt > 0){
            EXIT = 1;
            order = 1;
            while(1){
                clear();
                print_category(category,0);
                print_one_menu(category,-1);    
                move(LINES-5,0);
                hline('=',COLS);
                print_cart(order_name, order_size, order_num, cnt);
                print_order_complete(order, EXIT);
                refresh();
                
                key = getch();

                if(key == KEY_RIGHT){
                    if(order > 1) order=2;
                    else order++;
                }else if(key == KEY_LEFT){
                    if(order <= 1) order = 1;
                    else order--;
                }

                if(key == ENTER && order == 1){
                    clear();
                    return cnt;
                }else if(key == ENTER && order == 2){
                    cnt = 0;
                    clear();
                    break;
                }
            }
        }

        if(order == 0){
            size = category == 6 ? 2 : 1;
            num = 1;
            continue;
        }
        else if(order == 2) break;
    }

    return cnt;
}

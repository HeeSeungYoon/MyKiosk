#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include "menu.h"

#define ENTER 10
#define ESC 27

void print_start(int idx){
	if(idx == 0){
		attrset(COLOR_PAIR(1));
		mvprintw(LINES-2, COLS/3, "주문하기");
		attroff(COLOR_PAIR(1));
		mvprintw(LINES-2, COLS/3*2, "종료");
	}else if(idx == 1){
		mvprintw(LINES-2, COLS/3, "주문하기");
		attrset(COLOR_PAIR(1));
		mvprintw(LINES-2, COLS/3*2, "종료");
		attroff(COLOR_PAIR(1));
	}
}

int initUI(){
	
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

	int EXIT = 0;
	
	while(1){
		print_menu();
		print_start(EXIT);
		refresh();

		int key = getch();

		if(key == KEY_LEFT){ 
			if(EXIT <= 0) EXIT=0;
			else EXIT--;
		}
		else if(key == KEY_RIGHT){
			if(EXIT > 0) EXIT = 1;
			else EXIT++;
		}

		if(key == ENTER && EXIT == 0){
			return EXIT;
		}
		if(key == ENTER && EXIT == 1){
			break;
		}else if(key == ESC){
			EXIT =1;
			break;
		}
	}
	endwin();

	return EXIT;
}


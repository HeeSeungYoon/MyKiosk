#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>

int EXIT = 0;

int init(){
	
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

	move(LINES/2-2, COLS/2-4);
	attrset(COLOR_PAIR(1));
	printw("주문하기");
	
	attroff(COLOR_PAIR(1));
	move(LINES/2+2, COLS/2-4);
	printw("종료");

	int key = getch();
	
	while(10!=key){ // 10 : ENTER
		if(key == KEY_UP){ 
			clear();
			move(LINES/2-2, COLS/2-4);
			attrset(COLOR_PAIR(1));
			printw("주문하기");
			
			attroff(COLOR_PAIR(1));
			move(LINES/2+2, COLS/2-4);
			printw("종료");

			EXIT=0;

		}
		if(key == KEY_DOWN){
			clear();
			move(LINES/2+2, COLS/2-4);
			attrset(COLOR_PAIR(1));
			printw("종료");
			
			attroff(COLOR_PAIR(1));
			move(LINES/2-2, COLS/2-4);
			printw("주문하기");	

			EXIT = 1;
		}

		refresh();
		key = getch();
	}
	endwin();

	return EXIT;
}



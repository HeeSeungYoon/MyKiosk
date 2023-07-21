#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

void initMenu(Menu* menu){
	
	addHamberger(menu,"빅맥",5900);
	addHamberger(menu,"와퍼",6500);
	addHamberger(menu,"새우버거",4500);
	addHamberger(menu,"싸이버거",5000);
	addHamberger(menu,"콰트로치즈와퍼",7500);
	addHamberger(menu,"쉑쉑버거",9000);
	addHamberger(menu,"베이컨토마토디럭스",6900);
	addHamberger(menu,"치즈버거",4500);
	addHamberger(menu,"밥버거",2500);

	addSide(menu,"감자튀김",2000);
	addSide(menu,"치즈스틱",2500);
	addSide(menu,"코울슬로",1500);
	addSide(menu,"맥너겟",2500);
	addSide(menu,"너겟킹",3000);
	addSide(menu,"양파링",1500);
	
	addDrink(menu,"콜라",1500);
	addDrink(menu,"사이다",1500);
	addDrink(menu,"제로콜라",1500);
	addDrink(menu,"오렌지주스",1500);
	addDrink(menu,"밀크쉐이크",2000);
	addDrink(menu,"아메리카노",1500);
	addDrink(menu,"환타",1500);
	
}

void printMenu(Menu* menu){

	printf("%-30s%-10s| ","햄버거","가격");
	printf("%-30s%-10s| "," 사이드","가격");
	printf("%-30s%-10s|\n"," 음료","가격");
	printf("=============================================================================================================\n");
	int i=0;
	while(i<menu->hambergerIdx || i<menu->sideIdx || i<menu->drinkIdx){
		if(i<menu->hambergerIdx){
			printf("%-30s%-10s| ",menu->hamberger[i].name, menu->hamberger[i].price);
		}
		else{
			printf("%-30s%-10s| "," "," ");
		}
		if(i<menu->sideIdx){
			printf("%-30s%-10s| ",menu->side[i].name, menu->side[i].price);
		}
		else{
			printf("%-30s%-10s| "," "," ");
		}
		if(i<menu->drinkIdx){
			printf("%-30s%-10s|\n", menu->drink[i].name, menu->drink[i].price);
		}
		else{
			printf("%-30s%-10s|\n"," "," ");
		}
		i++;
	}
}

void addHamberger(Menu* menu, char* hamberger, int price){
	strcpy(menu->hamberger[menu->hambergerIdx].name,hamberger);
	sprintf(menu->hamberger[menu->hambergerIdx].price,"%d",price);
	menu->hambergerIdx++;
}

void addSide(Menu* menu, char* side, int price){
	strcpy(menu->side[menu->sideIdx].name, side);
	sprintf(menu->side[menu->sideIdx].price,"%d",price);
	menu->sideIdx++;
}

void addDrink(Menu* menu, char* drink, int price){
	strcpy(menu->drink[menu->drinkIdx].name, drink);
	sprintf(menu->drink[menu->drinkIdx].price,"%d",price);
	menu->drinkIdx++;
}

void deleteHamberger(Menu* menu, char* hamberger){
	int newIdx = 0;
	for(int i=0;i<menu->hambergerIdx;i++){
		if(strcmp(menu->hamberger[i].name, hamberger)==0){
			newIdx = i;
			break;	
		}
	}
	while(newIdx<menu->hambergerIdx-1){
		menu->hamberger[newIdx] = menu->hamberger[newIdx+1];
	}
	menu->hambergerIdx--;
}

void deleteSide(Menu* menu, char* side){
	int newIdx=0;
	for(int i=0;i<menu->sideIdx;i++){
		if(strcmp(menu->side[i].name, side)==0){
			newIdx = i;
			break;
		}
	}
	while(newIdx<menu->sideIdx-1){
		menu->side[newIdx] = menu->side[newIdx+1];
	}
	menu->sideIdx--;
}

void deleteDrink(Menu* menu, char* drink){
	int newIdx=0;
	for(int i=0;i<menu->drinkIdx;i++){
		if(strcmp(menu->drink[i].name, drink)==0){
			newIdx=i;
			break;
		}
	}
	while(newIdx<menu->drinkIdx-1){
		menu->drink[newIdx] = menu->drink[newIdx+1];
	}
	menu->drinkIdx--;
}

#include <stdio.h>
typedef struct Node{
	char name[50];
	char price[10];
}Node;

typedef struct Menu{
	Node hamberger[20];
	Node side[20];
	Node drink[20];
	int hambergerIdx;
	int sideIdx;
	int drinkIdx;
} Menu;

void initMenu(Menu* menu);
void printMenu(Menu* menu);
void addHamberger(Menu* menu, char* hamberger,int price);
void addSide(Menu* menu, char* side, int price);
void addDrink(Menu* menu, char* drink,int price);
void deleteHamberger(Menu* menu, char* hamberger);
void deleteSide(Menu* menu, char* side);
void deleteDrink(Menu* menu, char* drink);


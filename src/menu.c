#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "menu.h"

char* category_name[7] = {"에스프레소","콜드 브루","프라푸치노","브루드 커피","블렌디드","피지오","티"};

// 카테고리 중에 메뉴가 가장 많은 개수 만큼 배열 생성
// 메뉴 이름 
char* menu_name[7][18] = {
    // 에스프레소
    {"아메리카노","카페라떼","카푸치노","카라멜 마키야또","화이트 초콜릿 모카","카페모카",\
    "스타벅스 돌체라떼","바닐라 플랫 화이트","에스프레소","에스프레소 마키야또","에스프레소 콘 파나",\
    "커피스타벅스 더블샷","바닐라 스타벅스 더블샷","헤이즐넛 스타벅스 더블샷"},
    // 콜드 브루
    {"콜드 브루 오트라떼","돌체콜드브루","바닐라크림콜드브루","콜드브루","나이트로 바닐라크림","나이트로 콜드브루"},
    // 프라푸치노
    {"더블 에스프레소 칩 프라푸치노","제주 유기농 말차로 만든 크림 프라푸치노","자바 칩 프라푸치노",\
    "초콜릿 크림칩 프라푸치노","화이트 초콜릿 모카 프라푸치노","모카 프라푸치노","카라멜 프라푸치노", \
    "에스프레소 프라푸치노","바닐라크림 프라푸치노"},
    // 브루드 커피
    {"오늘의 커피","아이스 커피"},
    // 블렌디드
    {"민트 초콜릿 칩 블렌디드","딸기 딜라이트 요거트 블렌디드","피치 & 레몬 블렌디드", \
    "망고 바나나 블렌디드", "망고 패션 프루트 블렌디드"},
    // 피지오
    {"클라임 피지오","블랙티 레모네이드 피지오","패션 탱고 티 레모네이드 피지오"},
    //  티
    {"뉴이어 시트러스 티", "돌체 블랙 밀크티","유자 민트 티","패션 프루트 티", \
    "제주 유기농 말차로 만든 라떼", "차이 티 라떼","라임 패션 티","자몽 허니 블랙티",\
    "제주 유기 녹차","잉글리쉬 브랙퍼스트 티","얼그레이 티","유스베리 티","히비스커스 블렌드 티",\
    "민트 블렌드 티","캐모마일 블렌드 티","별궁 오미자 유스베리 티","아이스 푸를 청귤 민트 티", \
    "허니 얼그레이 밀크 티"}
};

// 메뉴 가격 
int menu_price[7][18]={
    // 에스프레소 Tall
    {4500, 4500, 5000, 5900, 5900, 5500, 5900, 5900, 4500, 4500, 4700, 5100, 5100, 5100},
    // 콜드 브루 Tall
    {5800, 6000, 5800, 4900, 6100, 6000},
    // 프라푸치노 Tall
    {6300, 6300, 6300, 6000, 6000, 6000, 5900, 5500, 5500},
    // 브루드 커피 Tall
    {4200, 5000},
    // 블렌디드 Tall
    {6300, 6300, 6300, 6300, 5400},
    // 피지오 Tall
    {5900, 5400, 5400},
    // 티 Grande
    {6600, 6400, 6400, 6400, 6600, 6000, 6400, 6200, 5800, 5000, 5000, 5000, 5000, 5000, 5000, \
    7000,7000,6900}
};

// 카테고리별 메뉴 개수
int menu_num[7] = {14, 6, 9, 2, 5, 3, 18};

// 메뉴 사이즈
char* menu_size[4] = {"Short", "Tall", "Grande", "Venti"};

char* substr(char* str, int start, int end){
	char* new = (char*)malloc((end-start+2)*sizeof(char));
	strncpy(new, str+start, end-start+1);
	new[end-start+1] = '\0';
	return new;
}

void print_menu()
{
    //system("cls");

    int i, j;
	char* line = (char*)(malloc)(sizeof(char)*COLS/7);
	for(i=0;i<COLS/7;i++){
		line[i] = '=';
	}

     for(i=0;i<7;i++){
			move(0, COLS/7*i);
            printw("%d. %s",i+1, category_name[i]);
			move(2,COLS/7*i);
			printw("%s",line);
        }

		int height = 4;
        for(i=0;i<18;i++){
            for(j=0;j<7;j++){
                if(menu_name[j][i] == NULL || menu_name[j][i]==""){
                    continue;
                }else{
					move(height,COLS/7*j);
					if(strlen(menu_name[j][i])>COLS/7){
						char* substr = (char*)malloc(COLS/7+1);
						substr = strncpy(substr, menu_name[j][i],COLS/7);
						substr[COLS/7+1] = '\0';
						printw("%d. %s...",i+1,substr);
					}
					else printw("%d. %s",i+1,menu_name[j][i]);
					move(height+1,COLS/7*j+COLS/14);
					if(j==0 && i>10) 
                    	printw("%d원(Short)",menu_price[j][i]);
                    else if(j<6) printw("%d원(Tall)",menu_price[j][i]);
                    else printw("%d원(Grande)",menu_price[j][i]);
                }
            }
			height = 4+LINES/18*(i+1);
			
        }
}
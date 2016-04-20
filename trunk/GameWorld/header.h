#ifndef _HEADER_HEADER_
#define _HEADER_HEADER_

#include <stdio.h>
//#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define SPACE 32
#define ENTER 13

struct Point{
	int x,y;
};

void gotoxy(int x, int y);
void RemoveCursor(void);

#define randomize() srand((unsigned)time(NULL))		// 난수 발생기 초기화
#define random(n) (rand() % (n))					//0~n까지의 난수 발생

void gotoxy(int x, int y)  
{ 
    COORD XY = {x, y}; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY); 
} 
void RemoveCursor(void)
{
    CONSOLE_CURSOR_INFO curInfo;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
	curInfo.bVisible=FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&curInfo);
}
void SetColor(int col)
{
	SetConsoleTextAttribute ( GetStdHandle(STD_OUTPUT_HANDLE),col);
}


#endif // TURBOC_HEADER
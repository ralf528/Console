#pragma once

#include "record.h"

#define s_z 122
#define B_Z 90
#define Bd_X 20
#define Bd_Y 2
#define Bd_W 10
#define Bd_H 22				//게임판을 그릴 위치와 크기

void DrawScreen();			//전체 게임화면을 그림
void DrawBoard();			//게임판을 그림
int KeyInput();				//키를 입력받음
void PrintBlock(BOOL bl);	//블록을 그려주는 함수
void NextBlock(BOOL bl);	//다음에 나올 블록을 그려주는 함수
void PrintBottom(BOOL bl);
int TestAround(int bx,int by,int b,int r);	//블록 주위를 검사
BOOL MoveDown();			//아래로 한칸씩 이동, 바닥에 닿으면 TestFull함수 호출수 TRUE 리턴
void TestFull();			//수평이 완성된 줄을 찾아 삭제
void Pause();				//잠시 정지 기능
void Hold();


Point BlockS[7][4][4]=
{
	{ {-1,0,0,0,1,0,2,0}, {0,0,0,1,0,-1,0,2}, {-1,1,0,1,1,1,2,1}, {1,-1,1,0,1,1,1,2} },		// -자 블록.

	{ {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1} },				// ㅁ자 블록.

	{ {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1}, {0,0,1,0,-1,1,0,1}, {0,0,1,0,0,-1,1,1} }, // S자 블록.

	{ {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1}, {0,0,-1,0,0,1,1,1}, {0,0,1,0,1,-1,0,1} },	// Z자 블록.

	{ {0,0,-1,0,1,0,-1,-1}, {0,0,0,-1,0,1,-1,1}, {0,0,-1,0,1,0,1,1}, {0,0,0,-1,0,1,1,-1} },		// ㄴ자 블록.

	{ {0,0,1,0,-1,0,1,-1}, {0,0,0,1,0,-1,-1,-1}, {0,0,1,0,-1,0,-1,1}, {0,0,0,-1,0,1,1,1} },		// ㄱ자 블록.

	{ {0,0,-1,0,1,0,0,1}, {0,0,0,-1,0,1,1,0}, {0,0,-1,0,1,0,0,-1}, {0,0,-1,0,0,-1,0,1} },		// ㅗ자 블록.
};

int board[Bd_W+2][Bd_H+2];				//게임판을 해당크기만큼 배열에 저장
int blcX,blcY;							//블록의 좌표
int block,next_block,rot;				//블록,다음블록,회전상태
int hold_block,temp;					//홀드블록, 템프
int hold_state=0;						//홀드상태  0 : 빈 상태, 1 : 담겨있는 중, 2: 홀드가 눌려짐
bool b=true;							// true : 홀드가능, false : 홀드불가 (다음턴에 사용 가능)
int nStay,nFrame=40;					//블록이 바닥에 내려오는 속도

void Tetris()
{

	int bx,by;				//게임판의 좌표

	RemoveCursor();			//커서 제거
	randomize();			//랜덤 초기화
	system("cls");			//화면 모두지움

	for(bx=0;bx<Bd_W+2;bx++){
		for(by=0;by<Bd_H+2;by++){
			board[bx][by]=(bx==0 || bx==Bd_W+1 || by==Bd_H+1 || by==0 || by==Bd_H-1) ? 1:0;
			//테두리는 1(벽), 나머지 안쪽은 0(빈칸)
		}
	}
	DrawScreen();

	block=random(7);		//7가지 블럭중 랜덤으로 1개 선택

	while(1){				//루프1:게임전체가 반복실행되는 루프
		blcX=Bd_W/2;	
		blcY=Bd_Y;			//새로운 벽돌을 게임판 중앙 위쪽으로 위치
		rot=0;				//rot를 최초 회전되지 않는 상태로 초기화

		if(hold_state==2)
		{
			hold_state--;
		}
		else
		{
			NextBlock(FALSE);		//next 칸의 블록을 지움
			block=next_block;		//새로운 블럭으로 next에 있던 블럭이 옴
			next_block=random(7);	//다음블록을 새로 랜덤초기화
			NextBlock(TRUE);		//새로 생성된 다음블록을 next칸에 그려줌
		}
		PrintBlock(TRUE);		//게임판에 새 블록을 그림		

		if(TestAround(blcX,blcY,block,rot)!=0) {
			break;
		}
		//새로 생성된 블록 주위가 막혀있으면 루프 탈출(게임 종료)

		nStay=(int)nFrame/2;				//20부터 역카운트
		while(2)					//루프2:블록이 바닥에 닿을때까지의 루프
		{
			if(--nStay==0)
			{
				nStay=(int)nFrame/2;		//다시 20으로 만듬
				if(MoveDown())		//블록을 한칸 내림 
					break;			//바닥에 닿으면 루프2 종료
			}
			if(KeyInput()) break;	//사용자가 블록을 바닥으로 내리면
			//TRUE가 리턴되어 루프2 종료(>다음블록 생성)
			Sleep(50);
		}//while(2)--------------------------------------------------------
	}//while(1)------------------------------------------------------------
	gotoxy(24,12);
	SetColor(10);
	puts("G A M E  O V E R");
	Sleep(1500);
	gotoxy(48,20);Record(1);
	gotoxy(40,23);
}

void DrawScreen()
{
	int x,y;
	SetColor(15);
	for (x=0; x<Bd_W+2; x++) {
		for (y=0; y<Bd_H+2; y++) {
			gotoxy(Bd_X+x*2,Bd_Y+y);

			puts(board[x][y]? "□":"  ");
		}
	}

	gotoxy(2,17);puts("←→:이동");
	gotoxy(2,18);puts("↑:회전,↓:내림");
	gotoxy(2,19);puts("SPACE : 떨굼");
	gotoxy(2,20);puts("ESC : pause");

	gotoxy(48,14);puts("이전 최고기록:");
	gotoxy(48,15);printf("- ");
	SetColor(12);load_Record(1);

	SetColor(15);
	gotoxy(48,17);puts("S C O R E");
	gotoxy(48,18);puts("- ");

	


	gotoxy(2,3);
	printf(" H O L D ");
	gotoxy(2,5);
	printf("□□□□□□□□");
	gotoxy(2,6);
	printf("□            □");
	gotoxy(2,7);
	printf("□            □");
	gotoxy(2,8);
	printf("□            □");
	gotoxy(2,9);
	printf("□            □");
	gotoxy(2,10);
	printf("□            □");
	gotoxy(2,11);
	printf("□□□□□□□□");

	gotoxy(46,3);
	printf(" N E X T ");
	gotoxy(46,5);
	printf("□□□□□□□□");
	gotoxy(46,6);
	printf("□            □");
	gotoxy(46,7);
	printf("□            □");
	gotoxy(46,8);
	printf("□            □");
	gotoxy(46,9);
	printf("□            □");
	gotoxy(46,10);
	printf("□            □");
	gotoxy(46,11);
	printf("□□□□□□□□");
}

void DrawBoard()
{
	int x,y;
	SetColor(3);
	for(x=1;x<Bd_W+1;x++){
		for(y=1;y<Bd_H-1;y++){
			gotoxy(Bd_X+x*2,Bd_Y+y);	//게임판 안쪽으로 커서이동
			puts(board[x][y]? "■":"  ");
		}
	}
	gotoxy(50,18);
	SetColor(10);
	printf("%d",score);
}

int TestAround(int bx,int by,int b,int r)
{
	int i,around=0;
	for(i=0;i<4;i++)
	{
		around=max(around,board[bx+BlockS[b][r][i].x][by+BlockS[b][r][i].y]);
	}	//board 배열에서 0,1,2 중 가장 큰값을 around에 대입해서 리턴
	return around;
}

void PrintBlock(BOOL bl)
{
	int i;
	SetColor(block+9);
	for(i=0;i<4;i++)
	{
		gotoxy(Bd_X+(BlockS[block][rot][i].x+blcX)*2,Bd_Y+BlockS[block][rot][i].y+blcY);
		puts(bl ? "■":"  ");
	}
	PrintBottom(bl);

}
void NextBlock(BOOL bl)
{
	int j;
	SetColor(next_block+9);
	for (j=0;j<4;j++) 
	{
		gotoxy(42+(BlockS[next_block][rot][j].x+blcX)*2,6+BlockS[next_block][rot][j].y+blcY);

		puts(bl ? "■":"  ");		//  ■를 출력해준다.
	}

}
void PrintBottom(BOOL bl)
{
	int i;
	SetColor(block+9);
	for(i=0;i<4;i++)
	{
		gotoxy(Bd_X+(BlockS[block][rot][i].x+blcX)*2,Bd_Y+Bd_H);
		puts(bl ? "□":"  ");
	}
}
BOOL KeyInput(){
	int ch,trot;

	if (_kbhit()) 
	{
		ch=_getch();
		if(ch== 0xE0 || ch==0)
		{
			ch=_getch();
			switch (ch) 
			{
			case LEFT:
				if (TestAround(blcX-1,blcY,block,rot) == 0) 
				{	
					PrintBlock(FALSE);
					blcX--;				
					PrintBlock(TRUE);	
				}
				break;

			case RIGHT:									
				if (TestAround(blcX+1,blcY,block,rot) == 0) {

					PrintBlock(FALSE);
					blcX++;	
					PrintBlock(TRUE);
				}
				break;
			case UP:
				trot=(rot+1)%4;
				// ㅡ 자 블럭이 아닐 경우
				if(block!=0)
				{
					if (TestAround(blcX,blcY,block,trot) == 0) {

						PrintBlock(FALSE);
						rot=trot;
						PrintBlock(TRUE);	
					}
					else if(TestAround(blcX-1,blcY,block,rot) != 0)
					{
						if(TestAround(blcX+1,blcY,block,rot) != 0){break;}
						PrintBlock(FALSE);
						blcX++;
						rot=trot;
						PrintBlock(TRUE);
					}
					else if(TestAround(blcX+1,blcY,block,rot) != 0)
					{
						if(TestAround(blcX-1,blcY,block,rot) != 0){break;}
						PrintBlock(FALSE);
						blcX--;
						rot=trot;
						PrintBlock(TRUE);
					}
				}
				//ㅡ자 블럭일 경우
				else
				{
					if(TestAround(blcX,blcY,block,trot) == 0) {

							PrintBlock(FALSE);
							rot=trot;
							PrintBlock(TRUE);	
					}
					else if(rot==1)
					{
						if(TestAround(blcX-1,blcY,block,rot) != 0)
						{
							if(TestAround(blcX+1,blcY,block,trot) != 0){break;}
							PrintBlock(FALSE);
							blcX++;
							rot=trot;
							PrintBlock(TRUE);

						}
						else if(TestAround(blcX+1,blcY,block,rot) != 0 || TestAround(blcX+2,blcY,block,rot) != 0)
						{
							if(TestAround(blcX-2,blcY,block,trot) != 0){break;}
							PrintBlock(FALSE);
							if(TestAround(blcX+1,blcY,block,rot) != 0){blcX--;}
							blcX--;
							rot=trot;
							PrintBlock(TRUE);

						}
					}
					else if(rot==3)
					{
						if(TestAround(blcX-1,blcY,block,rot) != 0 || TestAround(blcX-2,blcY,block,rot) != 0)
						{
							if(TestAround(blcX+2,blcY,block,trot) != 0){break;}
							PrintBlock(FALSE);
							if(TestAround(blcX-1,blcY,block,rot) != 0){blcX++;}
							blcX++;
							rot=trot;
							PrintBlock(TRUE);
						}
						else if(TestAround(blcX+1,blcY,block,rot) != 0)
						{
							if(TestAround(blcX-1,blcY,block,trot) != 0){break;}
							PrintBlock(FALSE);
							blcX--;
							rot=trot;
							PrintBlock(TRUE);
						}
					}
				}
				break;
			case DOWN:									

				if (MoveDown()) 
				{
					return TRUE;
				}
				break;
			}
		}//if---------------------------------
		else{
			switch(ch){

			case SPACE:
				while(MoveDown()==FALSE) {;}
				return TRUE;
			
			case ESC:
				Pause();
				break;
			case s_z:
				if(b!=true){break;}
					Hold();
				b=false;
				return TRUE;
			case B_Z:
				if(b!=true){break;}
					Hold();
				b=false;
				return TRUE;
			}
		}//else-------------------------------

	}//if(kbhit())--------------------------
	return FALSE;
}
BOOL MoveDown(){
	if (TestAround(blcX,blcY+1,block,rot) != 0) {		// 바닥에 닿으면
		TestFull();										// TestFull함수 실행
		PrintBottom(FALSE);
		DrawBoard();
		return TRUE;									// TRUE 리턴 -> 다음블럭출현
	}
	PrintBlock(FALSE);			
	blcY++;
	PrintBlock(TRUE);									// 한칸 아래로 이동			
	return FALSE;										// FALSE 리턴 -> 다시 MoveDown 실행
}
void TestFull()		// 줄 없애는 함수.
{
	b=true;
	int i,x,y,temp_y;
	for (i=0;i<4;i++) 
	{
		board[blcX+BlockS[block][rot][i].x][blcY+BlockS[block][rot][i].y]=2;		
	}
	for (y=0;y<Bd_H+1;y++) {				
		for (x=1;x<Bd_W+1;x++) { 
			if (board[x][y] != 2) break; //하나라도 블록이 아니면 break, 모두 블록이면 아래문장실행
		}
		if (x == Bd_W+1) 
		{
			score=score+100;
			if(nFrame>4){	nFrame--;}
			if(score>10000){	nFrame=2;}
			for (temp_y=y;temp_y>1;temp_y--) 
			{
				for (x=1;x<Bd_W+1;x++) {	
					board[x][temp_y]=board[x][temp_y-1];
				}
			}
			Sleep(5);
			DrawBoard();
		}
	}
}

void Pause()
{
	int x,y,c=10;
	for(x=1;x<Bd_W+1;x++){
		for(y=1;y<Bd_H-1;y++){
			gotoxy(Bd_X+x*2,Bd_Y+y);
			puts("  ");
		}
	}	
	while(_kbhit()!=1)
	{
		c=(c==10? 0:10);
		SetColor(c);
		gotoxy(23,10);
		printf("--- P A U S E ---");
		gotoxy(23,13);
		printf("아무키나 누르시오.");
		Sleep(100);
	}
	DrawBoard();
}

void Hold()
{
	PrintBlock(FALSE);			//기존 블록을 지워줌
	if(hold_state>0){
		for(int j=0;j<4;j++)
		{
			gotoxy(8+(BlockS[hold_block][0][j].x)*2,8+BlockS[hold_block][0][j].y);
			puts("  ");
		}
	}
	hold_state++;				//hold키가 눌러지면 홀드상태를 증가시켜줌(0->1,2)

	if(hold_state==2)			//hold기능이 실행되면 기존 블록과 바꿔줌
	{
		temp=block;
		block=hold_block;
		hold_block=temp;
	}
	else
	{
		hold_block=block;
	}
	
	SetColor(hold_block+9);		//hold된 블록을 그려줌
	for(int j=0;j<4;j++)
	{
		gotoxy(8+(BlockS[hold_block][0][j].x)*2,8+BlockS[hold_block][0][j].y);
		puts("■");
	}
};
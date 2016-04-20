#pragma once

#include "record.h"

#define s_z 122
#define B_Z 90
#define Bd_X 20
#define Bd_Y 2
#define Bd_W 10
#define Bd_H 22				//�������� �׸� ��ġ�� ũ��

void DrawScreen();			//��ü ����ȭ���� �׸�
void DrawBoard();			//�������� �׸�
int KeyInput();				//Ű�� �Է¹���
void PrintBlock(BOOL bl);	//����� �׷��ִ� �Լ�
void NextBlock(BOOL bl);	//������ ���� ����� �׷��ִ� �Լ�
void PrintBottom(BOOL bl);
int TestAround(int bx,int by,int b,int r);	//��� ������ �˻�
BOOL MoveDown();			//�Ʒ��� ��ĭ�� �̵�, �ٴڿ� ������ TestFull�Լ� ȣ��� TRUE ����
void TestFull();			//������ �ϼ��� ���� ã�� ����
void Pause();				//��� ���� ���
void Hold();


Point BlockS[7][4][4]=
{
	{ {-1,0,0,0,1,0,2,0}, {0,0,0,1,0,-1,0,2}, {-1,1,0,1,1,1,2,1}, {1,-1,1,0,1,1,1,2} },		// -�� ���.

	{ {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1} },				// ���� ���.

	{ {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1}, {0,0,1,0,-1,1,0,1}, {0,0,1,0,0,-1,1,1} }, // S�� ���.

	{ {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1}, {0,0,-1,0,0,1,1,1}, {0,0,1,0,1,-1,0,1} },	// Z�� ���.

	{ {0,0,-1,0,1,0,-1,-1}, {0,0,0,-1,0,1,-1,1}, {0,0,-1,0,1,0,1,1}, {0,0,0,-1,0,1,1,-1} },		// ���� ���.

	{ {0,0,1,0,-1,0,1,-1}, {0,0,0,1,0,-1,-1,-1}, {0,0,1,0,-1,0,-1,1}, {0,0,0,-1,0,1,1,1} },		// ���� ���.

	{ {0,0,-1,0,1,0,0,1}, {0,0,0,-1,0,1,1,0}, {0,0,-1,0,1,0,0,-1}, {0,0,-1,0,0,-1,0,1} },		// ���� ���.
};

int board[Bd_W+2][Bd_H+2];				//�������� �ش�ũ�⸸ŭ �迭�� ����
int blcX,blcY;							//����� ��ǥ
int block,next_block,rot;				//���,�������,ȸ������
int hold_block,temp;					//Ȧ����, ����
int hold_state=0;						//Ȧ�����  0 : �� ����, 1 : ����ִ� ��, 2: Ȧ�尡 ������
bool b=true;							// true : Ȧ�尡��, false : Ȧ��Ұ� (�����Ͽ� ��� ����)
int nStay,nFrame=40;					//����� �ٴڿ� �������� �ӵ�

void Tetris()
{

	int bx,by;				//�������� ��ǥ

	RemoveCursor();			//Ŀ�� ����
	randomize();			//���� �ʱ�ȭ
	system("cls");			//ȭ�� �������

	for(bx=0;bx<Bd_W+2;bx++){
		for(by=0;by<Bd_H+2;by++){
			board[bx][by]=(bx==0 || bx==Bd_W+1 || by==Bd_H+1 || by==0 || by==Bd_H-1) ? 1:0;
			//�׵θ��� 1(��), ������ ������ 0(��ĭ)
		}
	}
	DrawScreen();

	block=random(7);		//7���� ���� �������� 1�� ����

	while(1){				//����1:������ü�� �ݺ�����Ǵ� ����
		blcX=Bd_W/2;	
		blcY=Bd_Y;			//���ο� ������ ������ �߾� �������� ��ġ
		rot=0;				//rot�� ���� ȸ������ �ʴ� ���·� �ʱ�ȭ

		if(hold_state==2)
		{
			hold_state--;
		}
		else
		{
			NextBlock(FALSE);		//next ĭ�� ����� ����
			block=next_block;		//���ο� ������ next�� �ִ� ���� ��
			next_block=random(7);	//��������� ���� �����ʱ�ȭ
			NextBlock(TRUE);		//���� ������ ��������� nextĭ�� �׷���
		}
		PrintBlock(TRUE);		//�����ǿ� �� ����� �׸�		

		if(TestAround(blcX,blcY,block,rot)!=0) {
			break;
		}
		//���� ������ ��� ������ ���������� ���� Ż��(���� ����)

		nStay=(int)nFrame/2;				//20���� ��ī��Ʈ
		while(2)					//����2:����� �ٴڿ� ������������ ����
		{
			if(--nStay==0)
			{
				nStay=(int)nFrame/2;		//�ٽ� 20���� ����
				if(MoveDown())		//����� ��ĭ ���� 
					break;			//�ٴڿ� ������ ����2 ����
			}
			if(KeyInput()) break;	//����ڰ� ����� �ٴ����� ������
			//TRUE�� ���ϵǾ� ����2 ����(>������� ����)
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

			puts(board[x][y]? "��":"  ");
		}
	}

	gotoxy(2,17);puts("���:�̵�");
	gotoxy(2,18);puts("��:ȸ��,��:����");
	gotoxy(2,19);puts("SPACE : ����");
	gotoxy(2,20);puts("ESC : pause");

	gotoxy(48,14);puts("���� �ְ���:");
	gotoxy(48,15);printf("- ");
	SetColor(12);load_Record(1);

	SetColor(15);
	gotoxy(48,17);puts("S C O R E");
	gotoxy(48,18);puts("- ");

	


	gotoxy(2,3);
	printf(" H O L D ");
	gotoxy(2,5);
	printf("���������");
	gotoxy(2,6);
	printf("��            ��");
	gotoxy(2,7);
	printf("��            ��");
	gotoxy(2,8);
	printf("��            ��");
	gotoxy(2,9);
	printf("��            ��");
	gotoxy(2,10);
	printf("��            ��");
	gotoxy(2,11);
	printf("���������");

	gotoxy(46,3);
	printf(" N E X T ");
	gotoxy(46,5);
	printf("���������");
	gotoxy(46,6);
	printf("��            ��");
	gotoxy(46,7);
	printf("��            ��");
	gotoxy(46,8);
	printf("��            ��");
	gotoxy(46,9);
	printf("��            ��");
	gotoxy(46,10);
	printf("��            ��");
	gotoxy(46,11);
	printf("���������");
}

void DrawBoard()
{
	int x,y;
	SetColor(3);
	for(x=1;x<Bd_W+1;x++){
		for(y=1;y<Bd_H-1;y++){
			gotoxy(Bd_X+x*2,Bd_Y+y);	//������ �������� Ŀ���̵�
			puts(board[x][y]? "��":"  ");
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
	}	//board �迭���� 0,1,2 �� ���� ū���� around�� �����ؼ� ����
	return around;
}

void PrintBlock(BOOL bl)
{
	int i;
	SetColor(block+9);
	for(i=0;i<4;i++)
	{
		gotoxy(Bd_X+(BlockS[block][rot][i].x+blcX)*2,Bd_Y+BlockS[block][rot][i].y+blcY);
		puts(bl ? "��":"  ");
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

		puts(bl ? "��":"  ");		//  �Ḧ ������ش�.
	}

}
void PrintBottom(BOOL bl)
{
	int i;
	SetColor(block+9);
	for(i=0;i<4;i++)
	{
		gotoxy(Bd_X+(BlockS[block][rot][i].x+blcX)*2,Bd_Y+Bd_H);
		puts(bl ? "��":"  ");
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
				// �� �� ���� �ƴ� ���
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
				//���� ���� ���
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
	if (TestAround(blcX,blcY+1,block,rot) != 0) {		// �ٴڿ� ������
		TestFull();										// TestFull�Լ� ����
		PrintBottom(FALSE);
		DrawBoard();
		return TRUE;									// TRUE ���� -> ����������
	}
	PrintBlock(FALSE);			
	blcY++;
	PrintBlock(TRUE);									// ��ĭ �Ʒ��� �̵�			
	return FALSE;										// FALSE ���� -> �ٽ� MoveDown ����
}
void TestFull()		// �� ���ִ� �Լ�.
{
	b=true;
	int i,x,y,temp_y;
	for (i=0;i<4;i++) 
	{
		board[blcX+BlockS[block][rot][i].x][blcY+BlockS[block][rot][i].y]=2;		
	}
	for (y=0;y<Bd_H+1;y++) {				
		for (x=1;x<Bd_W+1;x++) { 
			if (board[x][y] != 2) break; //�ϳ��� ����� �ƴϸ� break, ��� ����̸� �Ʒ��������
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
		printf("�ƹ�Ű�� �����ÿ�.");
		Sleep(100);
	}
	DrawBoard();
}

void Hold()
{
	PrintBlock(FALSE);			//���� ����� ������
	if(hold_state>0){
		for(int j=0;j<4;j++)
		{
			gotoxy(8+(BlockS[hold_block][0][j].x)*2,8+BlockS[hold_block][0][j].y);
			puts("  ");
		}
	}
	hold_state++;				//holdŰ�� �������� Ȧ����¸� ����������(0->1,2)

	if(hold_state==2)			//hold����� ����Ǹ� ���� ��ϰ� �ٲ���
	{
		temp=block;
		block=hold_block;
		hold_block=temp;
	}
	else
	{
		hold_block=block;
	}
	
	SetColor(hold_block+9);		//hold�� ����� �׷���
	for(int j=0;j<4;j++)
	{
		gotoxy(8+(BlockS[hold_block][0][j].x)*2,8+BlockS[hold_block][0][j].y);
		puts("��");
	}
};
#ifndef _ROCORD_HEADER_
#define _ROCORD_HEADER_

char str[40];
int score=0;
int r_score=0;

void load_Record(int i)	//이전 기록을 불러옴
{
	FILE *fp;

	switch (i) {
		case 1:
			fopen_s(&fp,"TT_record.txt","r");
			break;
		case 2:
			fopen_s(&fp,"SN_record.txt","r");
			break;
		case 3:
			fopen_s(&fp,"RF_record.txt","r");
			break;
	}

	if(fp==NULL)	//NULL일 경우 기록없음 출력
	{
		printf("기록없음\n");
		return;
	}

	rewind(fp);
	fscanf_s(fp,"%d",&r_score);
	rewind(fp);
	fgets(str,sizeof(str),fp);
	printf(str);
}
void Rec_Name(char name[])
{
	SetColor(13);
	gotoxy(46,14);
	printf("축하합니다!!    ");
	gotoxy(46,15);
	printf("신기록입니다. 이름을 입력하세요:");
	gotoxy(48,16);
	gets_s(name,20);
	gotoxy(48+strlen(name),16);printf(" .");Sleep(500);printf(" .");Sleep(500);printf(" .");Sleep(1000);
}

void Record(int i)
{
	FILE *fp;
	
	switch (i) {
		case 1:
			fopen_s(&fp,"TT_record.txt","r");
			break;
		case 2:
			fopen_s(&fp,"SN_record.txt","r");
			break;
		case 3:
			fopen_s(&fp,"RF_record.txt","r");
			break;
	}
	
	if(score>r_score)
	{		
		char name[20];
		Rec_Name(name);
		fprintf(fp,"%d 。 [ %s ]",score,name);
	}
	else
		fprintf(fp,"%s",str);
	fclose(fp);
	
}

#endif
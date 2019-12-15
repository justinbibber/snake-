
#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h> 
#include<math.h>

#define _CRT_SECURE_NO_WARNINGS
#define up   'w'
#define down 's'
#define left 'a'
#define right 'd'
#define stop 'q'
#define status click
#define width 1000
#define longth 550

//����˵��
void Newgame();//��ʼ����
void creatmap();
void  ImageLoading();//ͼƬ�Ķ���
//void cantcrosswall();//�ж��Ƿ�ײǽ
void initsnake();//�ߵĳ�ʼ��
void Drawsnake();//��ͷ
void creatfood();//����ʳ��
void  movesnake();//����
void keyboardcontrol();//����ָ��
void speedup();//����
void speeddown();//����
void creatseed();//�������           
void halfsnake();//�������
void minedie();//���ڵ���

void creatmine();//���춾��
void eatseed();//�Ե�����
void clearseed();//�������
void seedss();//������˸

int judge();//�����ж�
void eatitself();//ҧ���Լ�
void wall();//���ײǽ
void enternext();//��һ��
void gameover();//��Ϸ����
//ͼƬ�Ķ���
IMAGE Plot1, Plot2;
IMAGE snake1, background1, background2;
IMAGE mine0;
IMAGE seed0;

//�ṹ��Ķ���
typedef struct food {
	int x, y;
	int s;
}food;

typedef struct snake {
	int x, y;
	snake *next;
	snake* pre;
	int c;
}snake;

typedef struct seed {
	int x, y, s;

}seed;

typedef struct mine
{
	int x, y, c;
}mine;

//ȫ�ֱ���
snake* head;
snake*tail;
food *food1;
seed *seed1;
mine *mine1;
char  click;
int sleeptime = 100;
int score = 0;
int gamestatues = 0;
int add = 10;
int count = 0;
int c = 0;

//***ͼƬ������
void ImageLoading() {
	loadimage(&Plot1, _T("1fen.jpg"));
	loadimage(&Plot2, _T("С��3.png"));
	loadimage(&background1, _T("�ݵ�.png"));
	loadimage(&background2, _T("Ц��.png"));
	loadimage(&mine0, _T("����3.png"));
	loadimage(&seed0, _T("��2.png"));
	loadimage(&snake1, _T("�ɰ��Ŀ�ʼ1.png"));
}

//***��ʼ�������ĥ������
void  Newgame() {
	initgraph(width, longth, SHOWCONSOLE);
	putimage(0, 0, &snake1);
	settextcolor(BLACK);
	settextstyle(25, 0, L"����");
/*	setbkmode(TRANSPARENT);
	outtextxy(400, 200, L"��˳��Ĵ�����");
	outtextxy(400, 230, L"1.��ʼ��Ϸ");
	outtextxy(400, 260, L"2.��Ϸ˵��");
	outtextxy(400, 290, L"3.�˳���Ϸ");
	outtextxy(400, 320, L"��ѡ�� 1 2 3:");*/
	_getch();
	creatmap();
	/*	int n;
		scanf("%d", &n);

		switch(n) {
		case 1:

		case 2:

		case 3:

		}*/
		/*	setfillcolor(CYAN);
		HRGN rgn_r = CreateRectRgn(700, 0, 1000,550);
		setcliprgn(rgn_r);
		DeleteObject(rgn_r);
		solidrectangle(700, 0, 1000, 550);
		settextcolor(BLACK);
		settextstyle(25,0,L"����");
		setbkmode(TRANSPARENT);
		outtextxy(750, 40, L"̰����");
		settextstyle(15, 0, L"����");
		RECT rect = { 750,100,950,450 };
		drawtext(_T("����Ϸ˵����\n\nwasd�������Ʒ���\n\
					F5    �����¿�ʼ\nesc�� ���˳���Ϸ\
					"), &rect, DT_WORDBREAK);
		setfillcolor(RGB(61,225, 174));//��ɫ��****�޸ģ�����
		HRGN rgn_l = CreateRectRgn(0, 0,1000, 600);
		setcliprgn(rgn_l);
		DeleteObject(rgn_l);
		solidrectangle(0, 0, 1000, 600);
		int i,j;
		for (i = 0; i <= 1000;) {

			if(i==0||i==1000)
			{
				for (j = 0; j <= 550; )
				{
					setfillcolor(RGB(219, 90, 108));
					solidrectangle(i, j, i + 10, j + 10);
					j += 10;
				}
			}
			for (j = 0; j <550; ) {
				setfillcolor(RGB(61, 225, 174));
				solidrectangle(i, j, i + 10, j + 10);
				j += 10;
			}
			i += 10;
		}*/
}
//�����ͼ
void creatmap() {
	cleardevice();
	setfillcolor(RGB(68, 206, 245));
	fillrectangle(0, 0, 1000, 10);
	fillrectangle(0, 0, 10, 550);
	fillrectangle(0, 540, 1000, 550);
	fillrectangle(990, 0, 1000, 550);
	setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
	solidrectangle(11, 11, 990, 540);
}

//��ʼ����
void initsnake() {
	tail = (snake*)malloc(sizeof(snake));
	snake*p1;
	p1 = (snake*)malloc(sizeof(snake));
	tail->x = 20;
	tail->y = 20;
	tail->next = NULL;
	head = tail;
	int i;
	for (i = 0; i < 5; i++) {
		p1 = (snake*)malloc(sizeof(snake));
		p1->x = head->x + 10;
		p1->y = head->y;
		p1->next = head;
		p1->pre = NULL;
		head->pre = p1;
		head = p1;
	}
	Drawsnake();
}
//����
void Drawsnake() {
	snake* temp = (snake*)malloc(sizeof(snake));
	temp = head;
	while ((temp->next) != NULL) {		
		setfillcolor(RGB(112, 242, 255));
		fillrectangle(temp->x, temp->y, temp->x + 10, temp->y + 10);
		temp = temp->next;
	}
}


//����
void  movesnake() {

	snake*q;
	q = (snake*)malloc(sizeof(snake));
	snake*p;
	p = (snake*)malloc(sizeof(snake));
	//	cantcrosswall();
	snake*nexthead;
	nexthead = (snake*)malloc(sizeof(snake));
	switch (click)
	{
	case up:
	{   nexthead->x = head->x;        //����ǰ��ʱ��x���겻����y����-10
	nexthead->y = head->y - 10;
	head->pre=nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //ָ��qָ����ͷ
	if (nexthead->x == food1->x  && nexthead->y == food1->y)	//�����һ����ʳ�� ��һ��λ�õ������ʳ���������ͬ
	{
		while (q != NULL)
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;
			if (q != NULL)
				q->c += 1;
		}
		count++;
		score=score+add;        //����һ��ʳ����ܷ��ϼ���ʳ��ķ�
		speedup(); //����ʳ��
		creatfood();
	}
	else if (q->x == seed1->x&&q->y == seed1->y)//˵���Ե�������
	{
		halfsnake();		
		}
	else if(q->x == mine1->x&&q->y == mine1->y|| (q->x == mine1->x+10&&q->y == mine1->y+10) || (q->x == mine1->x + 10 && q->y == mine1->y ) || (q->x == mine1->x && q->y == mine1->y + 10)){
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//���û����ʳ��            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //���������������
			q->c += 1;
		}
		setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);	
		q->next = NULL;
	}

	break; }
	case down:
	{	nexthead->x = head->x;        //����ǰ��ʱ��x���겻����y����-10
	nexthead->y = head->y + 10;
	head->pre = nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //ָ��qָ����ͷ
	if (nexthead->x == food1->x  && nexthead->y == food1->y)	//�����һ����ʳ�� ��һ��λ�õ������ʳ���������ͬ
	{

		while (q != NULL)
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;
			if (q != NULL)
				q->c += 1;
		}
		count++;
		score = score + add;        //����һ��ʳ����ܷ��ϼ���ʳ��ķ�
		speedup();
		creatfood();//����ʳ��
	}
	else if (q->x == seed1->x&&q->y == seed1->y)//˵���Ե�������
	{
		halfsnake();
	}
	else if (q->x == mine1->x&&q->y == mine1->y || (q->x == mine1->x + 10 && q->y == mine1->y + 10) || (q->x == mine1->x + 10 && q->y == mine1->y) || (q->x == mine1->x && q->y == mine1->y + 10)) {
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//���û����ʳ��            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //���������������
			q->c += 1;
		}
		setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);
		q->next = NULL;
	}
	break;
	}
	case left:
	{nexthead->x = head->x - 10;        //����ǰ��ʱ��x���겻����y����-10
	nexthead->y = head->y;
	head->pre = nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //ָ��qָ����ͷ
	if (nexthead->x == food1->x  && nexthead->y == food1->y)//�����һ����ʳ�� ��һ��λ�õ������ʳ���������ͬ
	{
		while (q != NULL)
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;
			if (q != NULL)
				q->c += 1;
		}
		count++;
		score = score + add;        //����һ��ʳ����ܷ��ϼ���ʳ��ķ�
		speedup();
		creatfood();//����ʳ��
	}
	else if (q->x == seed1->x&&q->y == seed1->y)//˵���Ե�������
	{
		halfsnake();
		}
	else if (q->x == mine1->x&&q->y == mine1->y || (q->x == mine1->x + 10 && q->y == mine1->y + 10) || (q->x == mine1->x + 10 && q->y == mine1->y) || (q->x == mine1->x && q->y == mine1->y + 10)) {
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//���û����ʳ��            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //���������������
			q->c += 1;
		}
		setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);
		q->next = NULL;
	}
	break;
	}
	case right:
	{nexthead->x = head->x + 10;        //����ǰ��ʱ��x���겻����y����-10
	nexthead->y = head->y;
	head->pre = nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //ָ��qָ����ͷ
	if (nexthead->x == food1->x  && nexthead->y == food1->y)	//�����һ����ʳ�� ��һ��λ�õ������ʳ���������ͬ
	{
		while (q != NULL)
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;
			if (q != NULL)
				q->c += 1;
		}
		count++;
					score=score+add;        //����һ��ʳ����ܷ��ϼ���ʳ��ķ�
					speedup();
		creatfood();//����ʳ��
	}
	else if(q->x == seed1->x&&q->y == seed1->y)//˵���Ե�������
	{
		halfsnake();
		}
	else if (q->x == mine1->x&&q->y == mine1->y || (q->x == mine1->x + 10 && q->y == mine1->y + 10) || (q->x == mine1->x + 10 && q->y == mine1->y) || (q->x == mine1->x && q->y == mine1->y + 10)) {
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//���û����ʳ��            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //���������������
		}
		setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);
		q->next = NULL;

	}
	break; }
	}
}
//���̿���
void keyboardcontrol() {
	status = right;
   	while (1)
	{
		if (_kbhit())
			status = _getch();
		if (GetAsyncKeyState(VK_UP) && status != down)            //GetAsyncKeyState���������жϺ�������ʱָ���������״̬
		{
			status = up;           //����߲�������ǰ����ʱ�򣬰��ϼ���ִ������ǰ������
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != up)     //����߲�������ǰ����ʱ�򣬰��¼���ִ������ǰ������
		{
			status = down;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != right)      //����߲�������ǰ����ʱ�򣬰������ִ������ǰ��
		{
			status = left;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != left)     //����߲�������ǰ����ʱ�򣬰��Ҽ���ִ������ǰ��
		{
			status = right;
		}

		if (GetAsyncKeyState(VK_SPACE))		//����ͣ����ִ��pause��ͣ����
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))      //���ո����ͣ
				{
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			gamestatues = 3;    //��esc����ֱ�ӵ���������
			break;
		}
		else if (GetAsyncKeyState(VK_F1))    //��F1��������
		{
			speedup();
		}
		else if (GetAsyncKeyState(VK_F2))    //��F2��������
		{
			speeddown();
		}
		Sleep(sleeptime);
		if (judge() != 1)
		{
			break;
		}
		movesnake();
	}
}

//����ʳ��
void creatfood() {
	snake* p = (snake*)malloc(sizeof(snake));
	p = head;
	srand((unsigned)time(NULL));
	food1 = (food*)malloc(sizeof(food));
	food1->x = rand() % 990;
	food1->y = rand() % 540;
	while (food1->x % 10 != 0 || food1->y % 10 != 0) {
		food1->x = rand() % 990;
		food1->y = rand() % 540;
	}
	while (p->next == NULL) {
		if (p->x == food1->x && p->y == food1->y) //�ж������Ƿ���ʳ���غ�   
		{
			free(food1);               //��������ʳ���غϣ���ô�ͷ�ʳ��ָ��
			creatfood();               //���´���ʳ��     
		}
		p = p->next;
	}
	setfillcolor(RGB(112, 242, 255));
	fillrectangle(food1->x, food1->y, food1->x + 10, food1->y + 10);
}
//�������
void creatseed() {
	snake* p = (snake*)malloc(sizeof(snake));
	
	srand((unsigned)time(NULL));
	seed1 = (seed*)malloc(sizeof(seed));
	if (count == 2)
	{
	again:
		p = head;
		seed1->x = rand() % 960+10;
		seed1->y = rand() % 520+10;
		while (seed1->x % 10 != 0 || seed1->y % 10 != 0) {
			seed1->x = rand() % 960+10;
			seed1->y = rand() % 520+10;
		}
		if (p->x == seed1->x && p->y == seed1->y)
			goto again;
		if (food1->x == seed1->x&&food1->y == seed1->y)
			goto again;
	}
	else {
	Again:
		p = head;
		seed1->x = rand() % 960+10;
		seed1->y = rand() % 520+10;
		while (seed1->x % 10 != 0 || seed1->y % 10 != 0) {
			seed1->x = rand() % 960+10;
			seed1->y = rand() % 520+10;
		}
		if (p != NULL)
		{
			while (p->next != NULL) {
				if (p->x == seed1->x && p->y == seed1->y) //�ж������Ƿ��붾���غ�   
				{
					goto Again;
				}
				p = p->next;

			}
			if (food1->x == seed1->x&&food1->y == seed1->y)
			{
				goto Again;
			}
		}
	else 
	gamestatues = 4;
	}
	putimage(seed1->x, seed1->y, &mine0);
}
//���춾��
void creatmine() {
	snake* p;
	srand((unsigned)time(NULL));
	mine1 = (mine*)malloc(sizeof(mine));	
	Again:
		p = head;
		mine1->x = rand() % 960 + 10;
		mine1->y = rand() % 520 + 10;
		while (mine1->x % 10 != 0 || mine1->y % 10 != 0) {
			mine1->x = rand() % 960 + 10;
			mine1->y = rand() % 520 + 10;
		}
		
			while (p->next != NULL) {
				if (p->x == seed1->x && p->y == seed1->y) //�ж������Ƿ��붾���غ�   
				{
					goto Again;
				}
				p = p->next;
			}
			if (food1->x == mine1->x&&food1->y == mine1->y)
			{
				goto Again;
			}
			if (mine1->x == seed1->x&&mine1->y == seed1->y)
			{
				goto Again;
			}
	putimage(mine1->x, mine1->y, &seed0);
}



//�������
void halfsnake() {
	int  n, i;
	count = 0;
	snake *p, *temp;
	p = head;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	n = count / 2;
	p = head;
	if (count <= 3)
		gamestatues = 4;
	else {
		for (i = 0; i < n - 1; i++)
			p = p->next;
		temp = p;
		while (p != NULL)
		{
			setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
			solidrectangle(p->x, p->y, p->x + 10, p->y + 10);
			p = p->next;
		}
		temp->next = tail->next;
		creatseed();
	}
}
//�Ե�����
void eatseed(){
	int  n, i;
	count = 0;
	snake *p, *temp;
	p = head;
	while (p != NULL)
	{
		count++;
		p = p->next;
	}
	n = count-1;
	p = head;
	if (count <= 3)
		gamestatues = 5;
	else {
		for (i = 0; i < n - 2; i++)
			p = p->next;
		temp = p;
		while (p != NULL)
		{
			setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
			solidrectangle(p->x, p->y, p->x + 10, p->y + 10);
			p = p->next;
		}
		temp->next = tail->next;
		creatmine();
	}
	clearseed();
}

void clearseed() {
	mine *p;
	p = mine1;
	setfillcolor(RGB(239, 222, 176));//��ɫ��****�޸ģ�����
	solidrectangle(p->x, p->y, p->x + 20, p->y + 20);
	creatmine();
}

void seedss() {

}



//�ж�
int judge() {
	snake *self;            //����selfΪ�����ϵ�һ���ڵ�    
	self = head->next;        //self����ͷ֮��������ϵĽڵ�   
	while (self != NULL)
	{
		if (self->x == head->x && self->y == head->y)    //���self�������ϵĽڵ��غ�        
		{
			gamestatues = 1;
		}
		self = self->next;
	}
	self = head;
	if (head->x == 0 || head->x == 990 || head->y == 0 || head->y == 540)//ײǽ
		gamestatues = 2;

	if (gamestatues != 0)
	{
		return 0;
	}
	return 1;
}

//��Ϸ����
void gameover() {
	putimage(0, 0, &background1);
	settextcolor(BLUE);
	settextstyle(20, 0, L"����");
	setbkmode(TRANSPARENT);
	outtextxy(200, 100, L"+-----------------------.@.@---------------------------+");
	outtextxy(300, 120, L"--.--");
	outtextxy(280, 140, L"\--\--\--\--\--\--|--/--/--/");
	outtextxy(300, 160, L"(_)");
	outtextxy(300, 180, L"(oOOo)");
	if (gamestatues == 1)
		eatitself();
	else if (gamestatues == 2)
		wall();
	else if (gamestatues == 3)
		enternext();
	else if (gamestatues == 4||gamestatues==5)
		minedie();
}

//ҧ���Լ�
void eatitself() {
	settextstyle(20, 0, L"����");
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, L"��Ե��Լ���");
	outtextxy(300, 250, L"��Ϸ����������");
	outtextxy(300, 300, L"�����¿�ʼ");
	_getch();
}

//ײǽ
void wall() {
	settextstyle(20, 0, L"����");
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, L"ײ��ǽ��");
	outtextxy(300, 250, L"��Ϸ����������");
	outtextxy(300, 300, L"�����¿�ʼ");
	_getch();
}

//��һ��
void enternext() {
	putimage(0, 0, &background1);
	settextcolor(BLACK);
	settextstyle(20, 0, L"����");
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, L"��ͨ������һ��");
	outtextxy(300, 250, L"������һ��");
	_getch();
}

//ը����
void minedie() {
	putimage(0, 0, &Plot1);
	settextstyle(20, 0, L"����");
	setbkmode(TRANSPARENT);
	if(gamestatues==4)
	outtextxy(300, 200, L"��ը�ˣ�");
	else if(gamestatues==5)
		outtextxy(300, 200, L"���ж���");
	outtextxy(300, 250, L"��Ϸ����������");
	outtextxy(300, 300, L"��ѡ���Ƿ����¿�ʼ");
	_getch();
}

//����
void speedup() {
	if (sleeptime >= 50)
	{
		sleeptime = sleeptime - 10;
		add = add + 2;
	}
}

//����
void speeddown() {
	if (sleeptime < 350)               //���ʱ����С��350    
	{
		sleeptime = sleeptime + 30;     //ʱ��������30        
		add = add - 2;                  //ÿ��һ��ʳ��ĵ÷ּ�2     
	}
}




int main() {
	ImageLoading();
	Newgame();
	initsnake();
	creatfood();
	creatseed();
	creatmine();
	keyboardcontrol();
	gameover();
	return 0;
}
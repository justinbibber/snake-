
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

//函数说明
void Newgame();//开始界面
void creatmap();
void  ImageLoading();//图片的定义
//void cantcrosswall();//判断是否撞墙
void initsnake();//蛇的初始化
void Drawsnake();//画头
void creatfood();//创造食物
void  movesnake();//动蛇
void keyboardcontrol();//输入指令
void speedup();//加速
void speeddown();//减速
void creatseed();//创造地雷           
void halfsnake();//身体减半
void minedie();//死于地雷

void creatmine();//创造毒草
void eatseed();//吃到毒草
void clearseed();//清除毒草
void seedss();//毒草闪烁

int judge();//结束判断
void eatitself();//咬到自己
void wall();//检测撞墙
void enternext();//下一关
void gameover();//游戏结束
//图片的定义
IMAGE Plot1, Plot2;
IMAGE snake1, background1, background2;
IMAGE mine0;
IMAGE seed0;

//结构体的定义
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

//全局变量
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

//***图片的引用
void ImageLoading() {
	loadimage(&Plot1, _T("1fen.jpg"));
	loadimage(&Plot2, _T("小人3.png"));
	loadimage(&background1, _T("草地.png"));
	loadimage(&background2, _T("笑脸.png"));
	loadimage(&mine0, _T("地雷3.png"));
	loadimage(&seed0, _T("火花2.png"));
	loadimage(&snake1, _T("可爱的开始1.png"));
}

//***起始界面需打磨！！！
void  Newgame() {
	initgraph(width, longth, SHOWCONSOLE);
	putimage(0, 0, &snake1);
	settextcolor(BLACK);
	settextstyle(25, 0, L"楷体");
/*	setbkmode(TRANSPARENT);
	outtextxy(400, 200, L"武顺天的聪明蛇");
	outtextxy(400, 230, L"1.开始游戏");
	outtextxy(400, 260, L"2.游戏说明");
	outtextxy(400, 290, L"3.退出游戏");
	outtextxy(400, 320, L"请选择 1 2 3:");*/
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
		settextstyle(25,0,L"楷体");
		setbkmode(TRANSPARENT);
		outtextxy(750, 40, L"贪吃蛇");
		settextstyle(15, 0, L"宋体");
		RECT rect = { 750,100,950,450 };
		drawtext(_T("【游戏说明】\n\nwasd键：控制方向\n\
					F5    ：重新开始\nesc键 ：退出游戏\
					"), &rect, DT_WORDBREAK);
		setfillcolor(RGB(61,225, 174));//调色板****修改！！！
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
//创造地图
void creatmap() {
	cleardevice();
	setfillcolor(RGB(68, 206, 245));
	fillrectangle(0, 0, 1000, 10);
	fillrectangle(0, 0, 10, 550);
	fillrectangle(0, 540, 1000, 550);
	fillrectangle(990, 0, 1000, 550);
	setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
	solidrectangle(11, 11, 990, 540);
}

//初始化蛇
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
//画蛇
void Drawsnake() {
	snake* temp = (snake*)malloc(sizeof(snake));
	temp = head;
	while ((temp->next) != NULL) {		
		setfillcolor(RGB(112, 242, 255));
		fillrectangle(temp->x, temp->y, temp->x + 10, temp->y + 10);
		temp = temp->next;
	}
}


//动蛇
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
	{   nexthead->x = head->x;        //向上前进时，x坐标不动，y坐标-10
	nexthead->y = head->y - 10;
	head->pre=nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //指针q指向蛇头
	if (nexthead->x == food1->x  && nexthead->y == food1->y)	//如果下一个有食物 下一个位置的坐标和食物的坐标相同
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
		score=score+add;        //吃了一个食物，在总分上加上食物的分
		speedup(); //创建食物
		creatfood();
	}
	else if (q->x == seed1->x&&q->y == seed1->y)//说明吃到毒草了
	{
		halfsnake();		
		}
	else if(q->x == mine1->x&&q->y == mine1->y|| (q->x == mine1->x+10&&q->y == mine1->y+10) || (q->x == mine1->x + 10 && q->y == mine1->y ) || (q->x == mine1->x && q->y == mine1->y + 10)){
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//如果没遇到食物            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //继续输出整个蛇身
			q->c += 1;
		}
		setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);	
		q->next = NULL;
	}

	break; }
	case down:
	{	nexthead->x = head->x;        //向上前进时，x坐标不动，y坐标-10
	nexthead->y = head->y + 10;
	head->pre = nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //指针q指向蛇头
	if (nexthead->x == food1->x  && nexthead->y == food1->y)	//如果下一个有食物 下一个位置的坐标和食物的坐标相同
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
		score = score + add;        //吃了一个食物，在总分上加上食物的分
		speedup();
		creatfood();//创建食物
	}
	else if (q->x == seed1->x&&q->y == seed1->y)//说明吃到毒草了
	{
		halfsnake();
	}
	else if (q->x == mine1->x&&q->y == mine1->y || (q->x == mine1->x + 10 && q->y == mine1->y + 10) || (q->x == mine1->x + 10 && q->y == mine1->y) || (q->x == mine1->x && q->y == mine1->y + 10)) {
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//如果没遇到食物            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //继续输出整个蛇身
			q->c += 1;
		}
		setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);
		q->next = NULL;
	}
	break;
	}
	case left:
	{nexthead->x = head->x - 10;        //向上前进时，x坐标不动，y坐标-10
	nexthead->y = head->y;
	head->pre = nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //指针q指向蛇头
	if (nexthead->x == food1->x  && nexthead->y == food1->y)//如果下一个有食物 下一个位置的坐标和食物的坐标相同
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
		score = score + add;        //吃了一个食物，在总分上加上食物的分
		speedup();
		creatfood();//创建食物
	}
	else if (q->x == seed1->x&&q->y == seed1->y)//说明吃到毒草了
	{
		halfsnake();
		}
	else if (q->x == mine1->x&&q->y == mine1->y || (q->x == mine1->x + 10 && q->y == mine1->y + 10) || (q->x == mine1->x + 10 && q->y == mine1->y) || (q->x == mine1->x && q->y == mine1->y + 10)) {
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//如果没遇到食物            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //继续输出整个蛇身
			q->c += 1;
		}
		setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);
		q->next = NULL;
	}
	break;
	}
	case right:
	{nexthead->x = head->x + 10;        //向上前进时，x坐标不动，y坐标-10
	nexthead->y = head->y;
	head->pre = nexthead;
	nexthead->next = head;
	head = nexthead;
	q = head;                 //指针q指向蛇头
	if (nexthead->x == food1->x  && nexthead->y == food1->y)	//如果下一个有食物 下一个位置的坐标和食物的坐标相同
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
					score=score+add;        //吃了一个食物，在总分上加上食物的分
					speedup();
		creatfood();//创建食物
	}
	else if(q->x == seed1->x&&q->y == seed1->y)//说明吃到毒草了
	{
		halfsnake();
		}
	else if (q->x == mine1->x&&q->y == mine1->y || (q->x == mine1->x + 10 && q->y == mine1->y + 10) || (q->x == mine1->x + 10 && q->y == mine1->y) || (q->x == mine1->x && q->y == mine1->y + 10)) {
		eatseed();
	}
	else {
		while (q->next->next != NULL)	//如果没遇到食物            
		{
			setfillcolor(RGB(112, 242, 255));
			fillrectangle(q->x, q->y, q->x + 10, q->y + 10);
			q = q->next;           //继续输出整个蛇身
		}
		setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
		solidrectangle(q->next->x, q->next->y, q->next->x + 10, q->next->y + 10);
		q->next = NULL;

	}
	break; }
	}
}
//键盘控制
void keyboardcontrol() {
	status = right;
   	while (1)
	{
		if (_kbhit())
			status = _getch();
		if (GetAsyncKeyState(VK_UP) && status != down)            //GetAsyncKeyState函数用来判断函数调用时指定虚拟键的状态
		{
			status = up;           //如果蛇不是向下前进的时候，按上键，执行向上前进操作
		}
		else if (GetAsyncKeyState(VK_DOWN) && status != up)     //如果蛇不是向上前进的时候，按下键，执行向下前进操作
		{
			status = down;
		}
		else if (GetAsyncKeyState(VK_LEFT) && status != right)      //如果蛇不是向右前进的时候，按左键，执行向左前进
		{
			status = left;
		}
		else if (GetAsyncKeyState(VK_RIGHT) && status != left)     //如果蛇不是向左前进的时候，按右键，执行向右前进
		{
			status = right;
		}

		if (GetAsyncKeyState(VK_SPACE))		//按暂停键，执行pause暂停函数
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(VK_SPACE))      //按空格键暂停
				{
					break;
				}
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			gamestatues = 3;    //按esc键，直接到结束界面
			break;
		}
		else if (GetAsyncKeyState(VK_F1))    //按F1键，加速
		{
			speedup();
		}
		else if (GetAsyncKeyState(VK_F2))    //按F2键，减速
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

//创造食物
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
		if (p->x == food1->x && p->y == food1->y) //判断蛇身是否与食物重合   
		{
			free(food1);               //如果蛇身和食物重合，那么释放食物指针
			creatfood();               //重新创建食物     
		}
		p = p->next;
	}
	setfillcolor(RGB(112, 242, 255));
	fillrectangle(food1->x, food1->y, food1->x + 10, food1->y + 10);
}
//创造地雷
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
				if (p->x == seed1->x && p->y == seed1->y) //判断蛇身是否与毒草重合   
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
//创造毒草
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
				if (p->x == seed1->x && p->y == seed1->y) //判断蛇身是否与毒草重合   
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



//身体减半
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
			setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
			solidrectangle(p->x, p->y, p->x + 10, p->y + 10);
			p = p->next;
		}
		temp->next = tail->next;
		creatseed();
	}
}
//吃到毒草
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
			setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
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
	setfillcolor(RGB(239, 222, 176));//调色板****修改！！！
	solidrectangle(p->x, p->y, p->x + 20, p->y + 20);
	creatmine();
}

void seedss() {

}



//判断
int judge() {
	snake *self;            //定义self为蛇身上的一个节点    
	self = head->next;        //self是蛇头之外的蛇身上的节点   
	while (self != NULL)
	{
		if (self->x == head->x && self->y == head->y)    //如果self和蛇身上的节点重合        
		{
			gamestatues = 1;
		}
		self = self->next;
	}
	self = head;
	if (head->x == 0 || head->x == 990 || head->y == 0 || head->y == 540)//撞墙
		gamestatues = 2;

	if (gamestatues != 0)
	{
		return 0;
	}
	return 1;
}

//游戏结束
void gameover() {
	putimage(0, 0, &background1);
	settextcolor(BLUE);
	settextstyle(20, 0, L"楷体");
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

//咬到自己
void eatitself() {
	settextstyle(20, 0, L"楷体");
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, L"你吃到自己了");
	outtextxy(300, 250, L"游戏结束！！！");
	outtextxy(300, 300, L"请重新开始");
	_getch();
}

//撞墙
void wall() {
	settextstyle(20, 0, L"楷体");
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, L"撞到墙了");
	outtextxy(300, 250, L"游戏结束！！！");
	outtextxy(300, 300, L"请重新开始");
	_getch();
}

//下一关
void enternext() {
	putimage(0, 0, &background1);
	settextcolor(BLACK);
	settextstyle(20, 0, L"楷体");
	setbkmode(TRANSPARENT);
	outtextxy(300, 200, L"你通过了这一关");
	outtextxy(300, 250, L"进入下一关");
	_getch();
}

//炸死了
void minedie() {
	putimage(0, 0, &Plot1);
	settextstyle(20, 0, L"楷体");
	setbkmode(TRANSPARENT);
	if(gamestatues==4)
	outtextxy(300, 200, L"你炸了！");
	else if(gamestatues==5)
		outtextxy(300, 200, L"你有毒！");
	outtextxy(300, 250, L"游戏结束！！！");
	outtextxy(300, 300, L"请选择是否重新开始");
	_getch();
}

//加速
void speedup() {
	if (sleeptime >= 50)
	{
		sleeptime = sleeptime - 10;
		add = add + 2;
	}
}

//减速
void speeddown() {
	if (sleeptime < 350)               //如果时间间隔小于350    
	{
		sleeptime = sleeptime + 30;     //时间间隔加上30        
		add = add - 2;                  //每吃一次食物的得分减2     
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
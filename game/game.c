#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROW 29 //游戏区行数
#define COL 60 //游戏区列数
#define KONG 0 //标记空（什么也没有）
#define WALL 1 //标记墙
#define FOOD 2 //标记食物
#define HEAD 3 //标记蛇头
#define BODY 4 //标记蛇身
#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //暂停
#define ESC 27 //退出
#define FONE 83 //F1加速
#define FTWO 68 //F2减速

//蛇的结构体
//头
struct Snake {
	int len; //记录蛇身长度
	int x; //蛇头横坐标
	int y; //蛇头纵坐标
} snake;

//蛇身结构体
struct Body {
	int x; //蛇身横坐标
	int y; //蛇身纵坐标
} body[ROW * COL]; //开辟足以存储蛇身的结构体数组

int face[ROW][COL]; //标记游戏区各个位置的状态
int max, grade;

int fen[2] = { 1, 1 }, shijian = 3000, t; //全局变量
//int a = rand()% 5; //初始蛇的长度随机数a

void game1();
//画字符蛇
void printSnake();
//游戏欢迎界面
int welcometogame();
//游戏帮助界面
int aboutGame(void);
//隐藏光标
void HideCursor();
//光标跳转
void CursorJump(int x, int y);
//游戏区设计
void InitInterface();
//颜色函数
int color(int c);
//读取最高分
void WriteGrade();
//最高分写入
int writeFile(int grade);
//初始化蛇
void InitSnake();
//随机生成食物
void RandFood();
//判断得分与结束
void JudgeFunc(int x, int y);
//打印蛇与覆盖蛇
void DrawSnake(int flag);
//移动蛇
void MoveSnake(int x, int y);
//执行按键
void run(int x, int y);
//游戏主体逻辑函数
void Game();
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main() {
#pragma warning (disable:4996) //消除警告
	int n, a = 0;
	//system("cls");
	while (1) {
		//清屏
		n = welcometogame();

		switch (n) {
			//开始游戏
		case 1:
			system("cls");
			system("title 贪吃蛇"); //设置cmd窗口的名字
			system("mode con cols=124 lines=30");;//设置控制台的宽高
			game1();
			break;

			//游戏说明
		case 2:
			aboutGame();
			//printf("游戏说明\n");
			//跳出switch结构
			break;

			//退出游戏
		case 3:
			//结束程序
			exit(0);
			break;

		default: {
			color(12);
			CursorJump(37, 30);
			printf("请在【1-3】内选择，按回车键重新选择");
		}
			   //等待用户输入任意一个字符
			   getchar();
		}
	}
	system("pause");
	return 0;
}
void game1() {
	HideCursor(); //隐藏光标
	WriteGrade(); //从文件读取最高分到max变量
	system("cls");
	InitInterface(); //初始化界面
	InitSnake(); //初始化蛇
	srand((unsigned int)time(NULL)); //设置随机数生成起点
	RandFood(); //随机生成食物
	DrawSnake(1); //打印蛇
	Game(); //开始游戏
}

//画字符蛇 从上到下 从左到右
void printSnake() {
	//清屏
	system("cls");

	CursorJump(35, 1);
	color(6);
	printf("/^\\/ ^\\");      //蛇眼

	CursorJump(34, 2);
	printf("|_0|  0|");      //蛇眼

	CursorJump(33, 2);
	color(2);
	printf("_");

	CursorJump(25, 3);
	color(12);
	printf("\\/");        //蛇信

	CursorJump(31, 3);
	color(2);
	printf("/");

	CursorJump(38, 3);
	color(6);
	printf("\\_/");       //蛇眼

	CursorJump(41, 3);
	color(10);
	printf("\\");

	CursorJump(26, 4);
	color(12);
	printf("\\____"); //舌头

	CursorJump(31, 4);
	color(2);
	printf("|");

	CursorJump(32, 4);
	printf("_________/");

	CursorJump(42, 4);
	color(10);
	printf("\\");

	CursorJump(31, 5);
	color(2);
	printf("\\_______");     //蛇嘴

	CursorJump(43, 5);
	color(10);
	printf("\\");

	CursorJump(38, 6);
	printf(" |    |                               \\");
	//下面都是画蛇身

	CursorJump(38, 7);
	printf(" /    /                               \\ \\");

	CursorJump(37, 8);
	printf(" /    /                                \\  \\");

	CursorJump(36, 9);
	printf(" /    /                                  \\  \\");

	CursorJump(35, 10);
	printf(" /    /                                    \\  \\");

	CursorJump(34, 11);
	printf(" /    /                _----_                \\  \\");

	CursorJump(33, 12);
	printf(" /    /             _--~       --_            |   |");

	CursorJump(33, 13);
	printf("(    (        _----~     _--_      --_      _/    |");

	CursorJump(34, 14);
	printf("\\    ~-——-~     --~---    ~--      ~-_-~       /");

	CursorJump(35, 15);
	printf("\\           -—~              ~—-         -—~");

	CursorJump(36, 16);
	printf("~—-----—~                      ~—---—~        ");


}

//游戏欢迎界面
int welcometogame() {
	int i = 0, j = 0;
	int n = 0;
	printSnake();
	color(14);
	CursorJump(54, 18);
	printf("贪吃蛇游戏\n");
	//打印游戏选项边框
	color(14);
	for (i = 20; i <= 28; i++) {              //控制行
		for (j = 35; j <= 82; j++) {         //控制列
			CursorJump(j, i);
			if (i == 20 || i == 28) {
				printf("-");
			}
			else if (j == 35 || j == 82) {
				printf("|");
			}
			else {
				printf(" ");
			}
		}
	}
	//打印游戏选项
	color(15);
	CursorJump(39, 22);
	printf("1. 来一把！开始游戏！（请先阅读游戏说明）");
	CursorJump(39, 24);
	printf("2. 瞅瞅历史最高分及游戏说明");
	CursorJump(39, 26);
	printf("3. 退出游戏");
	CursorJump(37, 29);
	printf("请选择 [1 or 2 or 3]:");
	scanf("%d", &n);
	getchar();
	return n;
}
//游戏帮助界面
int aboutGame(void) {
	int i = 0;
	int j = 0;

	//清屏
	system("cls");

	color(13);
	CursorJump(54, 3);
	printf("游戏说明");

	color(2);
	//画出边框
	//6~25行   20~75列
	for (i = 6; i <= 27; i++) {
		for (j = 30; j <= 85; j++) {
			CursorJump(j, i);
			//画上下边框
			if (i == 6 || i == 27) {
				printf("=");
			}
			else if (j == 30 || j == 85) {
				printf("||");
			}
		}
	}

	color(3);
	CursorJump(40, 8);
	printf("★ 1.不能撞到墙壁，不能咬到自己");

	color(5);
	CursorJump(40, 11);
	printf("★ 2.F1加速前进 F2减速前进");

	color(11);
	CursorJump(40, 14);
	printf("★ 3.使用空格暂停游戏和继续游戏");

	color(13);
	CursorJump(40, 17);
	printf("★ 4.使用方向键控制前进的方向");

	color(14);
	CursorJump(40, 20);
	printf("★ 5.按下ESC键退出游戏");

	color(10);
	CursorJump(40, 23);
	printf("★ 6.按下r或者R回到游戏欢迎界面");

	color(14);
	CursorJump(40, 26);
	printf("★ 7.历史最高分：%d", max);


	color(12);
	CursorJump(30, 28);
	printf("按下回车键返回主界面...");

	getchar();

	return 0;
}

//最高分写入
int writeFile(int grade) {
	FILE* fp = NULL;
	//打开文件
	fp = fopen("贪吃蛇最高分.txt", "w");
	if (NULL == fp) {
		printf("打开文件失败..\n");
		return -1;
	}
	//写文件
	fwrite(&grade, sizeof(int), 1, fp);
	//关闭文件
	fclose(fp);
	fp = NULL;
	//文件指针及时置空
	return grade;
}
//读取最高分
void WriteGrade() {
	FILE* pf = fopen("贪吃蛇最高得分记录.txt", "w"); //以只写的方式打开文件
	if (pf == NULL) { //打开文件失败
		printf("保存最高得分记录失败\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf); //将本局游戏得分写入文件当中
	fclose(pf); //关闭文件
	pf = NULL; //文件指针及时置空
}

//隐藏光标(emmm,buhuizuo)
void HideCursor() {
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
	curInfo.dwSize = 1; //如果没赋值的话，光标隐藏无效
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}

//光标跳转
//设置光标位置，将光标移动到屏幕指定位置
//在屏幕的左上角被定义为光标的坐标原点 (0, 0)
//横向为 X 轴，纵向为 Y 轴
void CursorJump(int x, int y) {
	COORD pos; //定义光标位置的结构体变量
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos); //设置光标位置
}

void InitInterface() {
	color(6); //颜色为土黄色
	for (int i = 0; i < ROW; i++) { //双层循环设计墙的位置
		for (int j = 0; j < COL; j++) {
			if (j == 0 || j == COL - 1) {
				face[i][j] = WALL; //标记该位置为墙
				CursorJump(2 * j, i); //一个方块占两个横坐标和一个纵坐标
				printf("■");//打印方块
			}
			else if (i == 0 || i == ROW - 1) { //首尾
				face[i][j] = WALL; //标记该位置为墙
				CursorJump(2 * j, i);
				printf("■");//打印方块
			}
			else {
				face[i][j] = KONG; //标记该位置为空

			}
		}
	}
	color(7); //颜色设置为白色
	CursorJump(0, ROW);
	printf("当前得分:%d", grade);
	CursorJump(COL, ROW);
	printf("历史最高得分:%d", max);
}
//颜色函数
int color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}
//初始化蛇
void InitSnake() {

	snake.len = 4; //蛇的身体长度初始化为2
	snake.x = COL / 2; //蛇头位置的横坐标
	snake.y = ROW / 2; //蛇头位置的纵坐标
	//蛇身坐标的初始化
	for (int i = 0; i <= 3; i++) {
		body[i].x = COL / 2 - 1 - i;
		body[i].y = ROW / 2;

	}
	//将蛇头和蛇身位置进行标记
	face[snake.y][snake.x] = HEAD;
	face[body[0].y][body[0].x] = BODY;
	face[body[1].y][body[1].x] = BODY;

}

//随机生成食物
void RandFood() { //rand是典型随机函数
	int i, j;
	do {
		//随机生成食物的横纵坐标
		i = rand() % ROW;
		j = rand() % COL;
	} while (face[i][j] != KONG); //确保生成食物的位置为空，若不为空则重新生成
	face[i][j] = FOOD; //将食物位置进行标记
	color(12); //颜色设置为红色
	CursorJump(2 * j, i); //光标跳转到生成的随机位置处
	printf("■"); //打印食物
}

//判断得分与结束
void JudgeFunc(int x, int y) {

	//若蛇头即将到达的位置是食物，则得分
	if (face[snake.y + y][snake.x + x] == FOOD) {
		shijian -= 100;
		snake.len++; //蛇身加长
		grade += fen[1]; //更新当前得分
		color(7); //颜色设置为白色
		CursorJump(0, ROW);
		printf("当前得分:%d", grade); //重新打印当前得分
		RandFood(); //重新随机生成食物
	}
	//若蛇头即将到达的位置是墙或者蛇身，则游戏结束
	else if (face[snake.y + y][snake.x + x] == WALL || face[snake.y + y][snake.x + x] == BODY) {
		Sleep(1000); //留给玩家反应时间
		system("cls"); //清空屏幕
		color(7); //颜色设置为白色
		CursorJump(2 * (COL / 3), ROW / 2 - 3);
		if (grade > max) {
			printf("恭喜你打破最高记录，最高记录更新为%d", grade);
			max = writeFile(grade);
		}
		else if (grade == max) {
			printf("与最高记录持平，加油再创佳绩", grade);
		}
		else {
			printf("请继续加油，当前与最高记录相差%d", max - grade);
		}
		CursorJump(2 * (COL / 3), ROW / 2);
		printf("GAME OVER······");
		grade = 0;
		while (1) { //询问玩家是否再来一局
			char ch;
			CursorJump(2 * (COL / 3), ROW / 2 + 3);
			printf("(回到主界面请按下r)");
			CursorJump(2 * (COL / 3), ROW / 2 + 5);
			printf("要再耍一把么?(y/n):");
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y') {
				system("cls");
				getchar();
				game1();
			}
			else if (ch == 'r' || ch == 'R') {
				system("cls");
				getchar();
				main();
			}
			else if (ch == 'n' || ch == 'N') {
				CursorJump(2 * (COL / 3), ROW / 2 + 7);
				exit(0);
			}
			else {
				CursorJump(2 * (COL / 3), ROW / 2 + 5);
				printf("选择错误，请再次选择");
			}
		}
	}
}

//执行按键
void run(int x, int y) {
	int t = 0;
	while (1) {
		if (t == 0 && fen[1] == 1)
			t = shijian; //这里t越小，蛇移动速度越快（可以根据次设置游戏难度）
		else if (fen[1] > fen[0])
			t = shijian - (fen[1] - fen[0]) * 100;
		if (fen[1] < fen[0])
			t = shijian + (fen[0] - fen[1]) * 100;
		/*if (t == 0)
			t = 3500;*/ //这里t越小，蛇移动速度越快（可以根据次设置游戏难度）
		while (--t) {
			if (_kbhit() != 0) //若键盘被敲击，则退出循环
				break;
		}
		if (t == 0) { //键盘未被敲击
			JudgeFunc(x, y); //判断到达该位置后，是否得分与游戏结束
			MoveSnake(x, y); //移动蛇
		}
		else { //键盘被敲击
			break; //返回Game函数读取键值
		}
	}
}
//游戏主体逻辑函数
void Game() {
	int n = RIGHT; //开始游戏时，默认向右移动
	int tmp = 0; //记录蛇的移动方向
	goto first; //第一次进入循环先向默认方向前进
	while (1) {
		n = _getch(); //读取键值
		//在执行前，需要对所读取的按键进行调整
		switch (n) {
		case UP:
		case DOWN: //如果敲击的是“上”或“下”
			if (tmp != LEFT && tmp != RIGHT) { //并且上一次蛇的移动方向不是“左”或“右”
				n = tmp; //那么下一次蛇的移动方向设置为上一次蛇的移动方向
			}
			break;
		case LEFT:
		case RIGHT: //如果敲击的是“左”或“右”
			if (tmp != UP && tmp != DOWN) { //并且上一次蛇的移动方向不是“上”或“下”
				n = tmp; //那么下一次蛇的移动方向设置为上一次蛇的移动方向
			}
			//case 'S':
			//case 's':
			//	/*fen[1] = fen[0] + 2;
			//	fen[0] = fen[1];*/
			//case 'd':
			//case 'D':
			/*if (fen[1] - 2 <= 0)
			{
			fen[1] = 1;
			fen[0] = fen[1];
			}
				else
			{
			fen[1] = fen[0] - 2;
			fen[0] = fen[1];
			}*/

		case SPACE:
		case ESC:
		case 'r':
		case 'R':
			break; //这四个无需调整
		default:
			n = tmp; //其他键无效，默认为上一次蛇移动的方向
			break;
		}
	first: //第一次进入循环先向默认方向前进
		switch (n) {
		case UP: //方向键：上
			run(0, -1); //向上移动
			tmp = UP; //记录当前蛇的移动方向
			break;
		case DOWN: //方向键：下
			run(0, 1); //向下移动
			tmp = DOWN; //记录当前蛇的移动方向
			break;
		case LEFT: //方向键：左
			run(-1, 0); //向左移动
			tmp = LEFT; //记录当前蛇的移动方向
			break;
		case RIGHT: //方向键：右
			run(1, 0); //向右移动
			tmp = RIGHT; //记录当前蛇的移动方向
			break;
		case 'S':
		case 's':
			t = shijian - (fen[1] - fen[0]) * 100;
			break;
		case 'd':
		case 'D':
			t = shijian + (fen[0] - fen[1]) * 100;
			break;
		case SPACE: //暂停
			system("pause>nul"); //暂停后按任意键继续
			break;
		case ESC: //退出
			system("cls"); //清空屏幕
			color(7); //颜色设置为白色
			CursorJump(COL - 8, ROW / 2);
			printf("  游戏结束  ");
			CursorJump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //重新开始
			system("cls"); //清空屏幕
			main(); //重新执行主函数
		}
	}
}

//打印和行走的蛇
void DrawSnake(int flag) {
	if (flag == 1) { //打印蛇
		color(14); //设置为黄色五角星
		CursorJump(2 * snake.x, snake.y);
		printf("★"); //打印蛇头
		for (int i = 0; i < snake.len; i++) {
			CursorJump(2 * body[i].x, body[i].y);
			printf("★"); //打印蛇身
		}
	}
	else { //覆盖蛇
		if (body[snake.len - 1].x != 0) { //防止len++后将(0, 0)位置的墙覆盖
			//将蛇尾覆盖为空格即可
			CursorJump(2 * body[snake.len - 1].x, body[snake.len - 1].y);
			printf("  ");
		}
	}
}

//移动蛇
void MoveSnake(int x, int y) {
	DrawSnake(0); //先覆盖当前所显示的蛇
	face[body[snake.len - 1].y][body[snake.len - 1].x] = KONG; //蛇移动后蛇尾重新标记为空
	face[snake.y][snake.x] = BODY; //蛇移动后蛇头的位置变为蛇身
	//蛇移动后各个蛇身位置坐标需要更新
	for (int i = snake.len - 1; i > 0; i--) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	//蛇移动后蛇头位置变为第0个蛇身的位置
	body[0].x = snake.x;
	body[0].y = snake.y;
	//蛇头的位置更改
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	DrawSnake(1); //打印移动后的蛇
}

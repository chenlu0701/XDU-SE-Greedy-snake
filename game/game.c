#define _CRT_SECURE_NO_WARNINGS 1

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define ROW 29 //��Ϸ������
#define COL 60 //��Ϸ������
#define KONG 0 //��ǿգ�ʲôҲû�У�
#define WALL 1 //���ǽ
#define FOOD 2 //���ʳ��
#define HEAD 3 //�����ͷ
#define BODY 4 //�������
#define UP 72 //���������
#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������
#define SPACE 32 //��ͣ
#define ESC 27 //�˳�
#define FONE 83 //F1����
#define FTWO 68 //F2����

//�ߵĽṹ��
//ͷ
struct Snake {
	int len; //��¼������
	int x; //��ͷ������
	int y; //��ͷ������
} snake;

//����ṹ��
struct Body {
	int x; //���������
	int y; //����������
} body[ROW * COL]; //�������Դ洢����Ľṹ������

int face[ROW][COL]; //�����Ϸ������λ�õ�״̬
int max, grade;

int fen[2] = { 1, 1 }, shijian = 3000, t; //ȫ�ֱ���
//int a = rand()% 5; //��ʼ�ߵĳ��������a

void game1();
//���ַ���
void printSnake();
//��Ϸ��ӭ����
int welcometogame();
//��Ϸ��������
int aboutGame(void);
//���ع��
void HideCursor();
//�����ת
void CursorJump(int x, int y);
//��Ϸ�����
void InitInterface();
//��ɫ����
int color(int c);
//��ȡ��߷�
void WriteGrade();
//��߷�д��
int writeFile(int grade);
//��ʼ����
void InitSnake();
//�������ʳ��
void RandFood();
//�жϵ÷������
void JudgeFunc(int x, int y);
//��ӡ���븲����
void DrawSnake(int flag);
//�ƶ���
void MoveSnake(int x, int y);
//ִ�а���
void run(int x, int y);
//��Ϸ�����߼�����
void Game();
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
int main() {
#pragma warning (disable:4996) //��������
	int n, a = 0;
	//system("cls");
	while (1) {
		//����
		n = welcometogame();

		switch (n) {
			//��ʼ��Ϸ
		case 1:
			system("cls");
			system("title ̰����"); //����cmd���ڵ�����
			system("mode con cols=124 lines=30");;//���ÿ���̨�Ŀ��
			game1();
			break;

			//��Ϸ˵��
		case 2:
			aboutGame();
			//printf("��Ϸ˵��\n");
			//����switch�ṹ
			break;

			//�˳���Ϸ
		case 3:
			//��������
			exit(0);
			break;

		default: {
			color(12);
			CursorJump(37, 30);
			printf("���ڡ�1-3����ѡ�񣬰��س�������ѡ��");
		}
			   //�ȴ��û���������һ���ַ�
			   getchar();
		}
	}
	system("pause");
	return 0;
}
void game1() {
	HideCursor(); //���ع��
	WriteGrade(); //���ļ���ȡ��߷ֵ�max����
	system("cls");
	InitInterface(); //��ʼ������
	InitSnake(); //��ʼ����
	srand((unsigned int)time(NULL)); //����������������
	RandFood(); //�������ʳ��
	DrawSnake(1); //��ӡ��
	Game(); //��ʼ��Ϸ
}

//���ַ��� ���ϵ��� ������
void printSnake() {
	//����
	system("cls");

	CursorJump(35, 1);
	color(6);
	printf("/^\\/ ^\\");      //����

	CursorJump(34, 2);
	printf("|_0|  0|");      //����

	CursorJump(33, 2);
	color(2);
	printf("_");

	CursorJump(25, 3);
	color(12);
	printf("\\/");        //����

	CursorJump(31, 3);
	color(2);
	printf("/");

	CursorJump(38, 3);
	color(6);
	printf("\\_/");       //����

	CursorJump(41, 3);
	color(10);
	printf("\\");

	CursorJump(26, 4);
	color(12);
	printf("\\____"); //��ͷ

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
	printf("\\_______");     //����

	CursorJump(43, 5);
	color(10);
	printf("\\");

	CursorJump(38, 6);
	printf(" |    |                               \\");
	//���涼�ǻ�����

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
	printf("\\    ~-����-~     --~---    ~--      ~-_-~       /");

	CursorJump(35, 15);
	printf("\\           -��~              ~��-         -��~");

	CursorJump(36, 16);
	printf("~��-----��~                      ~��---��~        ");


}

//��Ϸ��ӭ����
int welcometogame() {
	int i = 0, j = 0;
	int n = 0;
	printSnake();
	color(14);
	CursorJump(54, 18);
	printf("̰������Ϸ\n");
	//��ӡ��Ϸѡ��߿�
	color(14);
	for (i = 20; i <= 28; i++) {              //������
		for (j = 35; j <= 82; j++) {         //������
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
	//��ӡ��Ϸѡ��
	color(15);
	CursorJump(39, 22);
	printf("1. ��һ�ѣ���ʼ��Ϸ���������Ķ���Ϸ˵����");
	CursorJump(39, 24);
	printf("2. �����ʷ��߷ּ���Ϸ˵��");
	CursorJump(39, 26);
	printf("3. �˳���Ϸ");
	CursorJump(37, 29);
	printf("��ѡ�� [1 or 2 or 3]:");
	scanf("%d", &n);
	getchar();
	return n;
}
//��Ϸ��������
int aboutGame(void) {
	int i = 0;
	int j = 0;

	//����
	system("cls");

	color(13);
	CursorJump(54, 3);
	printf("��Ϸ˵��");

	color(2);
	//�����߿�
	//6~25��   20~75��
	for (i = 6; i <= 27; i++) {
		for (j = 30; j <= 85; j++) {
			CursorJump(j, i);
			//�����±߿�
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
	printf("�� 1.����ײ��ǽ�ڣ�����ҧ���Լ�");

	color(5);
	CursorJump(40, 11);
	printf("�� 2.F1����ǰ�� F2����ǰ��");

	color(11);
	CursorJump(40, 14);
	printf("�� 3.ʹ�ÿո���ͣ��Ϸ�ͼ�����Ϸ");

	color(13);
	CursorJump(40, 17);
	printf("�� 4.ʹ�÷��������ǰ���ķ���");

	color(14);
	CursorJump(40, 20);
	printf("�� 5.����ESC���˳���Ϸ");

	color(10);
	CursorJump(40, 23);
	printf("�� 6.����r����R�ص���Ϸ��ӭ����");

	color(14);
	CursorJump(40, 26);
	printf("�� 7.��ʷ��߷֣�%d", max);


	color(12);
	CursorJump(30, 28);
	printf("���»س�������������...");

	getchar();

	return 0;
}

//��߷�д��
int writeFile(int grade) {
	FILE* fp = NULL;
	//���ļ�
	fp = fopen("̰������߷�.txt", "w");
	if (NULL == fp) {
		printf("���ļ�ʧ��..\n");
		return -1;
	}
	//д�ļ�
	fwrite(&grade, sizeof(int), 1, fp);
	//�ر��ļ�
	fclose(fp);
	fp = NULL;
	//�ļ�ָ�뼰ʱ�ÿ�
	return grade;
}
//��ȡ��߷�
void WriteGrade() {
	FILE* pf = fopen("̰������ߵ÷ּ�¼.txt", "w"); //��ֻд�ķ�ʽ���ļ�
	if (pf == NULL) { //���ļ�ʧ��
		printf("������ߵ÷ּ�¼ʧ��\n");
		exit(0);
	}
	fwrite(&grade, sizeof(int), 1, pf); //��������Ϸ�÷�д���ļ�����
	fclose(pf); //�ر��ļ�
	pf = NULL; //�ļ�ָ�뼰ʱ�ÿ�
}

//���ع��(emmm,buhuizuo)
void HideCursor() {
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ�����
	curInfo.dwSize = 1; //���û��ֵ�Ļ������������Ч
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}

//�����ת
//���ù��λ�ã�������ƶ�����Ļָ��λ��
//����Ļ�����ϽǱ�����Ϊ��������ԭ�� (0, 0)
//����Ϊ X �ᣬ����Ϊ Y ��
void CursorJump(int x, int y) {
	COORD pos; //������λ�õĽṹ�����
	pos.X = x; //������
	pos.Y = y; //������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}

void InitInterface() {
	color(6); //��ɫΪ����ɫ
	for (int i = 0; i < ROW; i++) { //˫��ѭ�����ǽ��λ��
		for (int j = 0; j < COL; j++) {
			if (j == 0 || j == COL - 1) {
				face[i][j] = WALL; //��Ǹ�λ��Ϊǽ
				CursorJump(2 * j, i); //һ������ռ�����������һ��������
				printf("��");//��ӡ����
			}
			else if (i == 0 || i == ROW - 1) { //��β
				face[i][j] = WALL; //��Ǹ�λ��Ϊǽ
				CursorJump(2 * j, i);
				printf("��");//��ӡ����
			}
			else {
				face[i][j] = KONG; //��Ǹ�λ��Ϊ��

			}
		}
	}
	color(7); //��ɫ����Ϊ��ɫ
	CursorJump(0, ROW);
	printf("��ǰ�÷�:%d", grade);
	CursorJump(COL, ROW);
	printf("��ʷ��ߵ÷�:%d", max);
}
//��ɫ����
int color(int c) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}
//��ʼ����
void InitSnake() {

	snake.len = 4; //�ߵ����峤�ȳ�ʼ��Ϊ2
	snake.x = COL / 2; //��ͷλ�õĺ�����
	snake.y = ROW / 2; //��ͷλ�õ�������
	//��������ĳ�ʼ��
	for (int i = 0; i <= 3; i++) {
		body[i].x = COL / 2 - 1 - i;
		body[i].y = ROW / 2;

	}
	//����ͷ������λ�ý��б��
	face[snake.y][snake.x] = HEAD;
	face[body[0].y][body[0].x] = BODY;
	face[body[1].y][body[1].x] = BODY;

}

//�������ʳ��
void RandFood() { //rand�ǵ����������
	int i, j;
	do {
		//�������ʳ��ĺ�������
		i = rand() % ROW;
		j = rand() % COL;
	} while (face[i][j] != KONG); //ȷ������ʳ���λ��Ϊ�գ�����Ϊ������������
	face[i][j] = FOOD; //��ʳ��λ�ý��б��
	color(12); //��ɫ����Ϊ��ɫ
	CursorJump(2 * j, i); //�����ת�����ɵ����λ�ô�
	printf("��"); //��ӡʳ��
}

//�жϵ÷������
void JudgeFunc(int x, int y) {

	//����ͷ���������λ����ʳ���÷�
	if (face[snake.y + y][snake.x + x] == FOOD) {
		shijian -= 100;
		snake.len++; //����ӳ�
		grade += fen[1]; //���µ�ǰ�÷�
		color(7); //��ɫ����Ϊ��ɫ
		CursorJump(0, ROW);
		printf("��ǰ�÷�:%d", grade); //���´�ӡ��ǰ�÷�
		RandFood(); //�����������ʳ��
	}
	//����ͷ���������λ����ǽ������������Ϸ����
	else if (face[snake.y + y][snake.x + x] == WALL || face[snake.y + y][snake.x + x] == BODY) {
		Sleep(1000); //������ҷ�Ӧʱ��
		system("cls"); //�����Ļ
		color(7); //��ɫ����Ϊ��ɫ
		CursorJump(2 * (COL / 3), ROW / 2 - 3);
		if (grade > max) {
			printf("��ϲ�������߼�¼����߼�¼����Ϊ%d", grade);
			max = writeFile(grade);
		}
		else if (grade == max) {
			printf("����߼�¼��ƽ�������ٴ��Ѽ�", grade);
		}
		else {
			printf("��������ͣ���ǰ����߼�¼���%d", max - grade);
		}
		CursorJump(2 * (COL / 3), ROW / 2);
		printf("GAME OVER������������");
		grade = 0;
		while (1) { //ѯ������Ƿ�����һ��
			char ch;
			CursorJump(2 * (COL / 3), ROW / 2 + 3);
			printf("(�ص��������밴��r)");
			CursorJump(2 * (COL / 3), ROW / 2 + 5);
			printf("Ҫ��ˣһ��ô?(y/n):");
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
				printf("ѡ��������ٴ�ѡ��");
			}
		}
	}
}

//ִ�а���
void run(int x, int y) {
	int t = 0;
	while (1) {
		if (t == 0 && fen[1] == 1)
			t = shijian; //����tԽС�����ƶ��ٶ�Խ�죨���Ը��ݴ�������Ϸ�Ѷȣ�
		else if (fen[1] > fen[0])
			t = shijian - (fen[1] - fen[0]) * 100;
		if (fen[1] < fen[0])
			t = shijian + (fen[0] - fen[1]) * 100;
		/*if (t == 0)
			t = 3500;*/ //����tԽС�����ƶ��ٶ�Խ�죨���Ը��ݴ�������Ϸ�Ѷȣ�
		while (--t) {
			if (_kbhit() != 0) //�����̱��û������˳�ѭ��
				break;
		}
		if (t == 0) { //����δ���û�
			JudgeFunc(x, y); //�жϵ����λ�ú��Ƿ�÷�����Ϸ����
			MoveSnake(x, y); //�ƶ���
		}
		else { //���̱��û�
			break; //����Game������ȡ��ֵ
		}
	}
}
//��Ϸ�����߼�����
void Game() {
	int n = RIGHT; //��ʼ��Ϸʱ��Ĭ�������ƶ�
	int tmp = 0; //��¼�ߵ��ƶ�����
	goto first; //��һ�ν���ѭ������Ĭ�Ϸ���ǰ��
	while (1) {
		n = _getch(); //��ȡ��ֵ
		//��ִ��ǰ����Ҫ������ȡ�İ������е���
		switch (n) {
		case UP:
		case DOWN: //����û����ǡ��ϡ����¡�
			if (tmp != LEFT && tmp != RIGHT) { //������һ���ߵ��ƶ������ǡ��󡱻��ҡ�
				n = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
			}
			break;
		case LEFT:
		case RIGHT: //����û����ǡ��󡱻��ҡ�
			if (tmp != UP && tmp != DOWN) { //������һ���ߵ��ƶ������ǡ��ϡ����¡�
				n = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
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
			break; //���ĸ��������
		default:
			n = tmp; //��������Ч��Ĭ��Ϊ��һ�����ƶ��ķ���
			break;
		}
	first: //��һ�ν���ѭ������Ĭ�Ϸ���ǰ��
		switch (n) {
		case UP: //���������
			run(0, -1); //�����ƶ�
			tmp = UP; //��¼��ǰ�ߵ��ƶ�����
			break;
		case DOWN: //���������
			run(0, 1); //�����ƶ�
			tmp = DOWN; //��¼��ǰ�ߵ��ƶ�����
			break;
		case LEFT: //���������
			run(-1, 0); //�����ƶ�
			tmp = LEFT; //��¼��ǰ�ߵ��ƶ�����
			break;
		case RIGHT: //���������
			run(1, 0); //�����ƶ�
			tmp = RIGHT; //��¼��ǰ�ߵ��ƶ�����
			break;
		case 'S':
		case 's':
			t = shijian - (fen[1] - fen[0]) * 100;
			break;
		case 'd':
		case 'D':
			t = shijian + (fen[0] - fen[1]) * 100;
			break;
		case SPACE: //��ͣ
			system("pause>nul"); //��ͣ�����������
			break;
		case ESC: //�˳�
			system("cls"); //�����Ļ
			color(7); //��ɫ����Ϊ��ɫ
			CursorJump(COL - 8, ROW / 2);
			printf("  ��Ϸ����  ");
			CursorJump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //���¿�ʼ
			system("cls"); //�����Ļ
			main(); //����ִ��������
		}
	}
}

//��ӡ�����ߵ���
void DrawSnake(int flag) {
	if (flag == 1) { //��ӡ��
		color(14); //����Ϊ��ɫ�����
		CursorJump(2 * snake.x, snake.y);
		printf("��"); //��ӡ��ͷ
		for (int i = 0; i < snake.len; i++) {
			CursorJump(2 * body[i].x, body[i].y);
			printf("��"); //��ӡ����
		}
	}
	else { //������
		if (body[snake.len - 1].x != 0) { //��ֹlen++��(0, 0)λ�õ�ǽ����
			//����β����Ϊ�ո񼴿�
			CursorJump(2 * body[snake.len - 1].x, body[snake.len - 1].y);
			printf("  ");
		}
	}
}

//�ƶ���
void MoveSnake(int x, int y) {
	DrawSnake(0); //�ȸ��ǵ�ǰ����ʾ����
	face[body[snake.len - 1].y][body[snake.len - 1].x] = KONG; //���ƶ�����β���±��Ϊ��
	face[snake.y][snake.x] = BODY; //���ƶ�����ͷ��λ�ñ�Ϊ����
	//���ƶ����������λ��������Ҫ����
	for (int i = snake.len - 1; i > 0; i--) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
	//���ƶ�����ͷλ�ñ�Ϊ��0�������λ��
	body[0].x = snake.x;
	body[0].y = snake.y;
	//��ͷ��λ�ø���
	snake.x = snake.x + x;
	snake.y = snake.y + y;
	DrawSnake(1); //��ӡ�ƶ������
}

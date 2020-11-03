#define _CRT_SECURE_NO_WARNINGS 1
#include <conio.h> //用于getch（）
#include <math.h>
#include <stdio.h>
#include <stdlib.h> //用于rand
#include <string.h>
#include <time.h>
#include <windows.h>
//■□
/*-------------------------
程序名： 俄罗斯方块Tetris Plus
程序作者： 404name
日志：
·人物移动格外算时间，有下降加快更新，上升同样，这时候不算随机数，平常走动随机数
·win画面更新。开头介绍，胜利。下降时间控制
-----------------------*/

int map[500][500] = { 0 };
int color_map[500][500] = { 0 };
int check_sum[500][2] = { 0 };
int if_full;
//下标按顺序为  总分  应该下降的层数
//逻辑顺序是谁  check_sun储存对应map层数的和，当满的时候，他向上的有值的层数就要增加相应的该降层数。
int height, width, top;
int start_x, start_y, tx, ty, x, y, times, cnt_time, old_index0, index0;
int if_change, if_death, reduce_time;
int now_turn, next_turn, next_next_turn;
int next_position_x[2] = { 1, 1 }, next_position_y[2] = { 10, 2 }, show_next, show_first;
int now_color, next_color, next_next_color;
int man_x, man_y, v, man_up_down;
char man_top_right[3], man_buttom_left[3], man_top_left[3], man_buttom_right[3];

char commom_man[5][3] = { // 0ω0
	{ "Θ" },                //老头
	{ "Θ" },
	{ "老" },
	{ "头" } };

char going_to_die_man[5][3] = { //
	{ "凉" },                     //
	{ "凉" },
	{ "老" },
	{ "头" } };
int death_line = 8;
char message[7][20] = {
	{ "[][][][][]" },
	{ "[Tetris  ]" },
	{ "[    plus]" },
	{ "[俄罗斯  ]" },
	{ "[方块plus]" },
	{ "[][][][][]" } };
struct Pass
{
	char ss[10][11];
} pass[20] = {
	{ { { "0000000000" }, //1
	{ "0000000000" },
	{ "0000000000" },
	{ "0000000000" },
	{ "1110000020" },
	{ "1111101111" },
	{ "0000000000" },
	{ "0000000000" } } },

	{ { { "0000000000" }, //2
	{ "0000000000" },
	{ "0000000000" },
	{ "0000000000" },
	{ "0000000000" },
	{ "0001201000" },
	{ "0001111000" },
	{ "0001111000" } } },

	{ { { "0000000000" }, //3
	{ "0000000000" },
	{ "0000000000" },
	{ "0000000000" },
	{ "0000200000" },
	{ "0111111110" },
	{ "0111111110" },
	{ "0111111110" } } },

	{ { { "0000000000" }, //4
	{ "0000000000" },
	{ "0000000000" },
	{ "0000200000" },
	{ "0000110000" },
	{ "0001001000" },
	{ "0010000100" },
	{ "0100000010" } } },

	{ { { "0000000000" }, //5
	{ "0000000000" },
	{ "0001001000" },
	{ "0010000100" },
	{ "0010200100" },
	{ "0001111000" },
	{ "0001001000" },
	{ "0001001000" } } },

	{ { { "0000000000" }, //6
	{ "0000020000" },
	{ "0000001000" },
	{ "0000011100" },
	{ "0000111110" },
	{ "0001111111" },
	{ "0011111111" },
	{ "0111111111" } } },

	{ { { "0000000000" }, //7
	{ "0000200000" },
	{ "0001111100" },
	{ "0011111110" },
	{ "0111111111" },
	{ "0111111110" },
	{ "0111111110" },
	{ "0011111100" } } },

	{ { { "0000000000" }, //8
	{ "0000200000" },
	{ "0000110000" },
	{ "0001111111" },
	{ "0011011111" },
	{ "0111111111" },
	{ "0000000000" },
	{ "0000000000" } } },

	{ { { "0000000000" }, //9
	{ "0000002000" },
	{ "0000011111" },
	{ "0101011111" },
	{ "0000011111" },
	{ "0000011111" },
	{ "0000011111" },
	{ "0000011111" } } },

	{ { { "0000000000" }, //10
	{ "0000000000" },
	{ "0000000020" },
	{ "1000000001" },
	{ "0100000010" },
	{ "0010000100" },
	{ "0001001000" },
	{ "0000110000" } } },

	{ { { "0000010000" }, //11
	{ "0000011000" },
	{ "0000011100" },
	{ "0000010110" },
	{ "0020010010" },
	{ "0111110000" },
	{ "0111100000" },
	{ "0011000000" } } },

	{ { { "0000000000" }, //12
	{ "0000000000" },
	{ "0100200010" },
	{ "0011111100" },
	{ "0000110000" },
	{ "0000110000" },
	{ "0000110000" },
	{ "0001111000" } } },

	{ { { "0000000000" }, //13
	{ "0000000000" },
	{ "0000000000" },
	{ "0010000100" },
	{ "0100200010" },
	{ "0010100100" },
	{ "0000010000" },
	{ "0000100000" } } },

	{ { { "0000000000" }, //14
	{ "0000020000" },
	{ "0001111100" },
	{ "0000000010" },
	{ "0011111010" },
	{ "0100000010" },
	{ "0100000010" },
	{ "0000000000" } } },

	{ { { "0000200000" }, //15
	{ "0011111100" },
	{ "0111111110" },
	{ "0111111110" },
	{ "0111111110" },
	{ "0111001110" },
	{ "1011001101" },
	{ "0101111010" } } },

	{ { { "0000000000" }, //16
	{ "0000000000" },
	{ "0000200000" },
	{ "0000000000" },
	{ "1010101010" },
	{ "0101010101" },
	{ "1010101010" },
	{ "0101010101" } } } };
int now_pass;

int T[30][4] = {              //7种4*4状态，对应的数据是4位数对应4种情况（有效数前面不能为零不然会认为其他进制）
	{ 0000, 1011, 0000, 0000 }, //T
	{ 1101, 1111, 111, 0000 },
	{ 0000, 1110, 0000, 0000 },
	{ 0000, 0000, 0000, 0000 },

	{ 0000, 0000, 0000, 0000 }, //田
	{ 0000, 1111, 1111, 0000 },
	{ 0000, 1111, 1111, 0000 },
	{ 0000, 0000, 0000, 0000 },

	{ 1111, 1010, 1010, 1010 }, //l
	{ 101, 0000, 0000, 0000 },
	{ 101, 0000, 0000, 0000 },
	{ 101, 0000, 0000, 0000 },

	{ 1000, 1010, 1, 0000 }, //右L
	{ 101, 1111, 101, 0000 },
	{ 100, 1010, 10, 0000 },
	{ 0000, 0000, 0000, 0000 },

	{ 0001, 1010, 10, 0000 }, //左L
	{ 101, 1111, 101, 0000 },
	{ 1000, 1010, 100, 0000 },
	{ 0000, 0000, 0000, 0000 },

	{ 0000, 1111, 101, 0000 }, //右与
	{ 101, 1111, 1010, 0000 },
	{ 0000, 0000, 1010, 0000 },
	{ 0000, 0000, 0000, 0000 },

	{ 101, 1111, 0000, 0000 }, //左与
	{ 1010, 1111, 101, 0000 },
	{ 1010, 0000, 0000, 0000 },
	{ 0000, 0000, 0000, 0000 } };

void HideCursor();
int show(int out, int in, int if_auto, int class0);
void init_brick();
void death_line_drop(int turn);
void man_move();
void check();
void HideCursor() //光标隐藏
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //后边的0代表光标不可见
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y) //坐标函数
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void init_brick()
{
	now_color = next_color;
	next_color = next_next_color;
	next_next_color = rand() % 9;
	if (next_next_color == 0)
		next_next_color = 1;
	x = start_x;
	y = start_y;
	tx = x, ty = y;
	now_turn = next_turn;
	next_turn = next_next_turn;
	next_next_turn = rand() % 7;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), next_color);
	show_next = 1; //打印下下个
	show(1, 1, 1, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), next_next_color);
	show_next = 2; //打印下个
	show(1, 1, 1, 1);
	show_next = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), now_color);
	show_first = 1;
	show(1, 1, 1, 1);
	show_first = 0;
}

void init(int pass0)
{
	int i, j;
	HideCursor(); //隐藏光标
	system("cls");
	times = 500;
	cnt_time = 0;
	index0 = 1;
	x = start_x, y = start_y;
	tx = x, ty = y;
	top = 5;
	death_line = 8;
	height = 26;
	width = 23;
	if_full = 0, if_change = 0, if_death = 0, reduce_time = 0;
	next_turn = rand() % 7;
	next_next_turn = rand() % 7;
	now_turn = rand() % 7;
	v = 2, man_up_down = 0;
	start_x = 6, start_y = 10;
	show_first = 0;
	strcpy(man_top_left, commom_man[0]);
	strcpy(man_top_right, commom_man[1]);
	strcpy(man_buttom_left, commom_man[2]);
	strcpy(man_buttom_right, commom_man[3]);
	//游戏开始样式
	for (i = 0; i <= height; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 8 + 1);
		for (j = 0; j <= width; j = j + 2)
		{
			gotoxy(j, i);
			if (i == 0 || i == height || j == 0 || j == width - 1)
				printf("■");
			else
				printf("□");
		}
	}
	gotoxy(6, height / 2 - 2);
	printf("[Pass: No%2d]", pass0);
	gotoxy(6, height / 2);
	printf("[Start game]");
	getchar();
	//点击开始
	gotoxy(0, 0);
	//构建地图
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	for (i = 0; i <= height; i++)
	{
		check_sum[i][0] = 0;
		check_sum[i][1] = 0;
		for (j = 0; j <= width; j++)
		{
			if (i == 0 || j == 0 || j == 1 || i == height || j == width || j == width - 1 || i == top)
			{
				map[i][j] = 2;
			}
			else
				map[i][j] = 0;
			color_map[i][j] = 3;
		}
	}
	for (i = 0; i <= height; i++)
	{
		for (j = 0; j <= width; j = j + 2)
		{
			if (map[i][j] == 2)
			{
				printf("[]");
			}
			//这里是从17行开始打印8行关卡。
			else if (i >= (height - 8) && pass[pass0 - 1].ss[i - (height - 8)][j / 2 - 1] != '0' && pass0 != 0)
			{
				if (pass[pass0 - 1].ss[i - (height - 8)][j / 2 - 1] == '1')
				{
					map[i][j] = 2;
					check_sum[i][0] += 2;
					printf("■");
				}
				else if (pass[pass0 - 1].ss[i - (height - 8)][j / 2 - 1] == '2')
				{
					man_x = i;
					man_y = j;
					printf("  ");
				}
				else
					printf("??");
			}
			else
				printf("  ");
		}
		Sleep(50);
		printf("\n");
	}
	for (i = 1; i <= 4; i++)
	{
		gotoxy(8, i);
		printf("[]");
		gotoxy(16, i);
		printf("[]");
	}
	for (i = 0; i < 6; i++)
	{
		gotoxy(18, i);
		printf("%s", message[i]);
	}
	for (i = 6; i <= height; i++)
	{
		gotoxy(24, i);
		if (i != height)
			printf("  []");
		else
			printf("[][]");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (i = 6; i <= death_line; i++)
	{
		gotoxy(26, i);
		printf("[]");
	}
	death_line_drop(1);
	srand(time(NULL));
	next_turn = rand() % 7;
	next_next_turn = rand() % 7;
	init_brick();
	if (now_pass != 0)
		man_move();
	getch();
}

void end()
{
	int i, j;
	system("cls");
	for (i = 0; i <= height; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 8 + 1);
		for (j = 0; j <= width; j = j + 2)
		{
			gotoxy(j, i);
			if (i == 0 || i == height || j == 0 || j == width - 1)
			{
				printf("■");
			}
			else
				printf("□");
		}
		Sleep(50);
	}
	gotoxy(8, height / 2 + 2);
	printf("Gameover");
	gotoxy(8, height / 2);
	printf("Gameover");
	gotoxy(8, height / 2 - 2);
	printf("Gameover");
	getchar();
	init(now_pass);
}

void gameover()
{
	int i, j;
	system("cls");
	for (i = 0; i <= height; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 8 + 1);
		for (j = 0; j <= width; j = j + 2)
		{
			gotoxy(j, i);
			if (i == 0 || i == height || j == 0 || j == width - 1)
			{
				printf("■");
			}
			else
				printf("□");
		}
		Sleep(50);
	}
	gotoxy(2, height / 2 - 6);
	printf("  ！！！恭喜！！！  ");
	getchar();
	gotoxy(2, height / 2 - 4);
	printf("  ！！！恭喜！！！  ");
	getchar();
	gotoxy(2, height / 2 - 2);
	printf("  神奇！居然通关了  ");
	getchar();
	gotoxy(2, height / 2);
	printf("  想要解锁更多关卡  ");
	getchar();
	gotoxy(2, height / 2 + 2);
	printf("  可以期待后续更新  ");
	getchar();
	gotoxy(2, height / 2 + 4);
	printf("  也可以自己去魔改  ");
	getchar();
	gotoxy(2, height / 2 + 6);
	printf("    游戏到此结束    ");
	getchar();
	system("cls");
	exit(0);
}
void death_line_drop(int turn) //0对应下降 1对应打印
{
	int i;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	gotoxy(0, death_line);
	printf("[]");
	gotoxy(width - 1, death_line);
	printf("[]  ");
	for (i = 2; i <= width - 2; i = i + 2)
	{
		gotoxy(i, death_line);
		if (map[death_line][i] != 1)
			printf("  ");
	}
	if (turn == 1)
		death_line++;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	gotoxy(0, death_line);
	printf("{}");
	gotoxy(width - 1, death_line);
	printf("{}--[]");
	check_sum[death_line][0] = 0;
	for (i = 2; i <= width - 2; i = i + 2)
	{
		if (map[death_line][i] == 2)
		{
			map[death_line][i] = 0;
		}
		gotoxy(i, death_line);
		if (map[death_line][i] != 1)
			printf("--");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), now_color);
	check();
}

void delete_line()
{
	int i, j, temp = 0;
	HideCursor(); //隐藏光标
	for (i = height - 1; i >= death_line; i--)
	{
		if (check_sum[i][0] == 20)
		{
			check_sum[i][0] = 0;
			for (j = i - 1; j >= death_line; j--)
			{

				check_sum[j][1]++;
				if (man_x == j)
				{
					temp++;
				}
			}
		}
	}
	man_x += temp;
	//下降
	for (i = height - 1; i >= death_line; i--)
	{
		if (check_sum[i][1])
		{
			check_sum[i + check_sum[i][1]][0] = check_sum[i][0];
			check_sum[i][0] = 0;
			gotoxy(2, i + check_sum[i][1]);
			for (j = 2; j <= width - 2; j = j + 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_map[i][j]);
				map[i][j] == 2 ? printf("■") : printf("  ");
				map[i + check_sum[i][1]][j] = map[i][j];
			}
			gotoxy(2, i);
			for (j = 2; j <= width - 2; j = j + 2)
			{
				map[i][j] = 0;
				printf("  ");
			}
			check_sum[i][1] = 0;
		}
	}
	check();
	if (now_pass != 0)
		man_move();
	Sleep(50);
	death_line_drop(0);
}

int get_index0_num(int res, int index0)
{
	int ans = 0;
	while (res && index0)
	{
		ans = res % 10;
		index0--;
		res /= 10;
	}
	if (index0)
		return 0;
	return ans;
}

void man_move()
{
	HideCursor();
	if (man_x <= death_line || man_x - 1 <= death_line)
	{
		if_death = 1;
		end();
		return;
	}
	if (map[man_x][man_y] == 0)
	{
		gotoxy(man_y, man_x);
		printf("  ");
	}
	if (map[man_x][man_y + 2] == 0)
	{
		gotoxy(man_y + 2, man_x);
		printf("  ");
	}
	if (map[man_x - 1][man_y] == 0)
	{
		gotoxy(man_y, man_x - 1);
		printf("  ");
	}
	if (map[man_x - 1][man_y + 2] == 0)
	{
		gotoxy(man_y + 2, man_x - 1);
		printf("  ");
	}
	if (map[man_x][man_y] != 2 && map[man_x][man_y + 2] != 2 && map[man_x + 1][man_y] != 2 && map[man_x + 1][man_y + 2] != 2)
	{
		man_x++;
		man_up_down = 1;
		/*if (man_x != height - 1)
		{
		man_move();
		Sleep(50);
		}*/
	}
	else if (map[man_x][man_y] == 2 || map[man_x][man_y + 2] == 2 || map[man_x - 1][man_y] == 2 || map[man_x - 1][man_y + 2] == 2)
	{
		man_x--;
		man_up_down = 1;
		/* man_move();
		Sleep(50);*/
	}
	else
	{
		man_up_down = 0;
		if (v > 0)
		{
			if (map[man_x][man_y + 4] != 2 && map[man_x - 1][man_y + 4] != 2)
				man_y += v;
			else
				v = -v;
		}
		else
		{
			if (map[man_x][man_y - 2] != 2 && map[man_x - 1][man_y - 2] != 2)
				man_y += v;
			else
				v = -v;
		}
	}
	if (death_line - man_x <= 4)
		man_up_down = 1;
	if (man_x - death_line <= 4)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		strcpy(man_top_left, going_to_die_man[0]);
		strcpy(man_top_right, going_to_die_man[1]);
		strcpy(man_buttom_left, going_to_die_man[2]);
		strcpy(man_buttom_right, going_to_die_man[3]);
	}
	else
	{
		if (strcmp(man_top_left, going_to_die_man[0]) == 0)
		{
			strcpy(man_top_left, commom_man[0]);
			strcpy(man_top_right, commom_man[1]);
			strcpy(man_buttom_left, commom_man[2]);
			strcpy(man_buttom_right, commom_man[3]);
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), rand() % 8 + 1);
	}
	if (map[man_x][man_y + 2] == 0)
	{
		gotoxy(man_y + 2, man_x);
		printf("%2s", man_buttom_right);
	}
	if (map[man_x][man_y] == 0)
	{
		gotoxy(man_y, man_x);
		printf("%2s", man_buttom_left);
	}
	if (map[man_x - 1][man_y + 2] == 0)
	{
		gotoxy(man_y + 2, man_x - 1);
		printf("%2s", man_top_right);
	}
	if (map[man_x - 1][man_y] == 0)
	{
		gotoxy(man_y, man_x - 1);
		printf("%2s", man_top_left);
	}
	if (man_x == height - 1)
	{
		gotoxy(8, height / 2);
		printf("YOU WIN");
		getchar();
		now_pass++;
		if (now_pass > 15)
		{
			gameover();
		}
		init(now_pass);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), now_color);
}

int show(int out, int in, int if_auto, int class0) //是否清除 是否加载 是否自动下落  赋值类型（1在移动 2定位的）
{
	int i, j;
	int temp_x;
	int temp_y;
	int temp_tx;
	int temp_ty;
	int temp_now_turn;
	if (show_next == 1 || show_next == 2)
	{
		temp_now_turn = now_turn;
		temp_x = x;
		temp_y = y;
		temp_tx = tx;
		temp_ty = ty;
		x = next_position_x[show_next - 1];
		y = next_position_y[show_next - 1];
		now_turn = (show_next == 2 ? next_next_turn : next_turn);
		tx = x, ty = y;
	}
	if (out == 1) //清除
	{
		for (i = tx; i < tx + 4; i++)
		{
			for (j = ty; j < ty + 4; j++)
			{

				if (i <= height && 2 * j - ty <= width && map[i][2 * j - ty] == 1)
				{
					gotoxy(2 * j - ty, i);
					map[i][2 * j - ty] = 0;
					if (i == death_line)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("--");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), now_color);
					}
					else
						printf("  ");
				}
			}
		}
	}
	if (in == 1) //打印
	{
		int now_turn_index = now_turn * 4, ttx, tty; //对应到的初始下标
		for (i = x; i < x + 4; i++)
		{
			for (j = y; j < y + 4; j++)
			{
				if (i <= height && 2 * j - y <= width && get_index0_num(T[i - x + now_turn_index][j - y], index0) == 1 && map[i][2 * j - y] == 0)
				{
					gotoxy(2 * j - y, i);
					if (!(class0 == 2 && i <= death_line))
						map[i][2 * j - y] = class0;
					if (class0 == 2 && i > death_line)
					{
						check_sum[i][0] += 2;
						if (check_sum[i][0] == 20)
						{
							if_full = 1;
						}
						color_map[i][2 * j - y] = now_color;
					}
					if (!(class0 == 2 && i <= death_line))
						printf("■");
				}
				else if (i <= height && 2 * j - y <= width && get_index0_num(T[i - x + now_turn_index][j - y], index0) == 1 && map[i][2 * j - y] == 2 && if_auto == 1) //失败则回退
				{
					if (show_first)
					{
						if_death = 1;
						end();
					}
					x = tx;
					y = ty;
					show(1, 1, 1, 2);
					Sleep(300);
					init_brick();
					show(1, 1, 1, 1);
					return 0;
				}
				else if (i <= height && 2 * j - y <= width && get_index0_num(T[i - x + now_turn_index][j - y], index0) == 1 && map[i][2 * j - y] == 2) //失败则回退
				{
					ttx = tx;
					tty = ty;
					tx = x;
					ty = y;
					show(1, 0, 0, 0);
					x = ttx;
					y = tty;
					if (if_change == 1)
					{
						index0 = old_index0;
						show(1, 1, 0, 1);
					}
					else if (if_auto == 0)
					{
						show(1, 1, 0, 1);
					}
					return 0;
				}

				if (get_index0_num(T[i - x + now_turn_index][j - y], index0) == 1 && map[i + 1][2 * j - y] == 2)
					reduce_time = 1;
			}
		}
		check();
		tx = x;
		ty = y;
	}
	if (show_next == 1 || show_next == 2)
	{
		x = temp_x;
		y = temp_y;
		tx = temp_tx;
		ty = temp_ty;
		now_turn = temp_now_turn;
	}
	return 1;
}

void check()
{
	int i;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	for (i = 6; i < height; i++)
	{
		gotoxy(24, i);
		if (i != death_line)
			printf("[%02d]", check_sum[i][0] / 2);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), now_color);
}

void manchange() //人为输入更新
{
	char ch, ch1, ch2;
	if (kbhit())
	{
		ch = getch();
		if (ch != ' ' && ch != 'w' && ch != 's' && ch != 'a' && ch != 'd' && ch != -32 && ch != 'p' && ch != 'b')
			return;
		if (ch == -32)
		{ //同时启用wasd  和上下左右键
			ch1 = getch();
			switch (ch1)
			{
			case 72:
				ch = 'w';
				break;
			case 75:
				ch = 'a';
				break;
			case 80:
				ch = 's';
				break;
			case 77:
				ch = 'd';
				break;
			}
		}
		if (ch == 'a' || ch == 's' || ch == 'd' || ch == 'w' || ch == ' ' || ch == 'p' || ch == 'b')
		{
			switch (ch)
			{
			case 'a':
				y = y - 2, show(1, 1, 0, 1);
				break;
			case 'd':
				y = y + 2, show(1, 1, 0, 1);
				break;
			case 's':
				x++, show(1, 1, 0, 1);
				break;
			case 'w':
			{
						if_change = 1;
						old_index0 = index0;
						index0 = (index0 + 1) % 5;
						if (index0 == 0)
							index0 = 1;
						show(1, 1, 0, 1);
						if_change = 0;
						break;
			}
			}
		}
	}
}
void autochange() //自动更新
{
	times--;
	if (times == 0)
	{
		cnt_time++;
		if (rand() % 2 == 0 || man_up_down == 1) //正常走路随机走，上升/下降/死亡线接近时加速
		if (now_pass != 0)
			man_move();
		times = 15000;
		x++;
		show(1, 1, 1, 1);
		reduce_time = 0;
		if (if_full == 1)
		{
			if_full = 0;
			delete_line();
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), now_color);
		if (reduce_time == 1)
			times = 8000;
		if (cnt_time == 20 && now_pass != 0)
		{
			cnt_time = 0;
			death_line_drop(1);
		}
	}
}
int main()
{
	int temp_pass = 1;
	char choose;
	system("mode con cols=50 lines=28");
	HideCursor();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("******   游戏名：  俄罗斯方块Tetris Plus   ******\n");
	printf("******                                     ******\n");
	printf("******   程序作者： 404name                ******\n");
	printf("******                                     ******\n");
	printf("******   操作方式： ←左移动               ******\n");
	printf("******   操作方式： →右移动               ******\n");
	printf("******   操作方式： ↑上旋转               ******\n");
	printf("******   操作方式： ↓加速下降             ******\n");
	printf("******   操作方式： 回车确认键             ******\n");
	printf("******   建议游戏字号大小为26号            ******\n");
	getchar();
	gotoxy(0, 0);
	printf("********************游戏介绍*********************\n");
	printf("******                                     ******\n");
	printf("******   一共15关，解救老人即可进入下一关  ******\n");
	printf("******                                     ******\n");
	printf("******   （ 老人降落到第一层即为成功）     ******\n");
	printf("******                                     ******\n");
	printf("******       正常启动：按两下回车          ******\n");
	printf("******       跳关启动：按T再回车           ******\n");
	printf("******    (选择0关对应的是无尽模式)        ******\n");
	printf("********************游戏介绍*********************\n");
	now_pass = 1;
	choose = getchar();
	getchar();
	if (choose == 'T' || choose == 't')
	{
		printf("请输入开始关卡");
		scanf("%d", &temp_pass);
		if (temp_pass > 15 || temp_pass < 0)
		{
			temp_pass = 16; //彩蛋关卡
			printf("即将进入彩蛋关卡");
			Sleep(1000);
		}
		now_pass = temp_pass;
	}
	next_color = 3;
	next_next_color = 4;
	system("mode con cols=28 lines=28");
	system("color 07");
	gotoxy(0, 0);
	init(now_pass);
	while (1)
	{
		autochange();
		manchange();
	}
}



//#include<stdio.h>
//int sum(int a)
//{
//	int c = 0;
//	static int b = 3;
//	c += 1;
//	b += 2;
//	return(a + b + c);
//}
//int main()
//{
//	int i;
//	int a = 2;
//	for (i = 0; i < 5; i++)
//	{
//		printf("%d\t", sum(a));
//	}
//	return 0;
//}



//
//#include<stdio.h>
//void AddOne()
//{
//	auto int a = 1;
//	a = a + 1;
//	printf("%d\n", a);
//}
//int main()
//{
//	printf("第一次调用：");
//	AddOne();
//	printf("第二次调用：");
//	AddOne();
//	return 0;
//}


//#include<stdio.h>
//int main()
//{
//	int c, b, i, j;
//	int a[10];
//	printf("请输入十个数：\n");
//	for (i = 0; i < 10; i++)
//	{
//		printf("a[%d]=", i);
//		scanf("%d", &a[i]);
//	}
//	for (i = 0; i < 10; i++)
//	{
//		b = a[i];
//		c = i;
//		for (j = i + 1; j < 10; j++)
//		{
//			if (a[j] < b)
//			{
//				b = a[j];
//				c = j;
//			}
//		}
//		a[c] = a[i];
//		a[i] = b;
//
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d\t", a[i]);
//		if (i == 4)
//		  printf("\n");
//	}
//	return 0;
//}

//#include<stdio.h>
//int main()
//{
//	int i, j;
//	int a[10];
//	int temp;
//	int pos;
//	printf("请输入十个数：\n");
//	for (i = 0; i < 10; i++)
//	{
//		printf("a[%d]=", i);
//		scanf("%d", &a[i]);
//	}
//	for (i = 0; i < 10; i++)
//	{
//		temp = a[i];
//		pos = i;
//		for (j = i + 1; j < 10; j++)
//		{
//			if (a[j]<temp)
//			{
//				temp=a[j];
//				pos=j;
//			}
//		}
//		a[pos] = a[i];
//		a[i] = temp;
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d\t", a[i]);
//		if (i == 4)
//		{
//			printf("\n");
//		}
//	}
//	return 0;
//
//}

//#include<stdio.h>
//#include<stdlib.h>
//int main()
//{
//	int counter;
//	for (counter = 0; counter < 10; counter++)
//	{
//		srand(counter + 1);
//		printf("Random number %d is:%d\n", counter, rand());
//	}
//	return 0;
//}
//#include<stdio.h>
//#include<time.h>
//int main()
//{
//	time_t seconds;
//	seconds = time(NULL);
//	printf("%ld\n", seconds / 3600);
//	return 0;
//}
//#include<stdio.h>
//int main()
//{
//	int num = 1, sum = 0;
//	for (num = 1; num < 11; num++)
//	{
//		sum = sum + num;
//	}
//	printf("一到十的和为:%d\n",sum);
//	return 0;
//}

//#include<stdio.h>
//int main()
//{
//	int sum = 0;
//	int num = 1;
//	do
//	{
//		sum = sum + num;
//		num++;
//	} while (num <= 10);
//	printf("一到十的和为%d", sum);
//	return 0;
//}
//#include<stdio.h>
//int main()
//{
//	char grade = 'B';
//	switch (grade)
//	{
//	case'A':printf("90-100\n");
//	case'B':printf("80-90\n");
//	case'C':printf("70-80\n");
//	case'D':printf("60-70\n"); break;
//	case'E':printf("<60\n");
//	default:printf("error!\n");
//	}
//	return 0;
//}



//#include<stdio.h>
//#define Max 1000;
//int main()
//{
//	int a = Max;
//	printf("%d\n", a);
//	return 0;
//}

//#include<stdio.h>
//int main()
//{
//	printf("the string is: %s\n", "sdfghjk");
//	return 0;
//}

//#include<stdio.h>
//int main()
//{
//	char cstring[30];
//	gets(cstring);
//	puts(cstring);
//	return 0;
//}


//#include<stdio.h>
//int main()
//{
//	char a;
//	printf("请输入一个小写字母：");
//	a=getchar();
//	printf("转换为大写字母：");
//	putchar(a-32);
//	printf("\n");
//	return 0;
//}



//#include<stdio.h>
//int main()
//{
//	int chinese, english;
//	printf("please erter chinese score:");
//	printf("\n");
//	scanf("%d", &chinese);
//	printf("please enter english score:");
//	scanf("%d", &english);
//	if (chinese > english)
//	{
//		printf("chinese is better than english\n");
//	}
//	else
//	{
//		printf("english is batter than chinese\n");
//	}
//	return 0;
//}

//#include<stdio.h>
//int main()
//{
//	int a = 3;
//	float b;
//	b = (float)a;
//	printf("%f", b);
//	return 0;
//}

//#include<stdio.h>
//int Add(int num1, int num2)
//{
//	int sum;
//	sum = num1 + num2;
//	return sum;
//}
//int main()
//{
//	int num1;
//	int num2;
//	int sum;
//	printf("请输入两个数：\n");
//	scanf("%d%d", &num1, &num2);
//	sum = Add(num1, num2);
//	printf("两个数的和sum=%d", sum);
//	return 0;
//}



//#include <stdio.h>
//int main()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//	int i = 0;
//	int k = 7;//要找的数字
//	int sz = sizeof(arr) /sizeof(arr[0]);//计算元素的个数
//	printf("sz=%d\n",sz);
//	while (i<sz)
//	{
//		if (arr[i] != k)
//		{
//			i++;
//		printf("%d\n", i);
//			if (arr[i] == k)
//			{
//				printf("找到了%d\n", arr[i]);
//			}
//		}
//		
//	}
//	return 0;
//}
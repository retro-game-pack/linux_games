#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include "tetris.h"


#define double_for(y, x, n) for(int y=0;y<n;y++) for(int x=0;x<n;x++)


block_data background[HEIGHT_TETRIS][WIDTH_TETRIS]; 	// 0,0 is main(left top)
							// [y][x]
block_data current_block[4][4];
int current_block_type;

int cur_x=0;
int cur_y=0;


int getkey() // terminal func
{
	int character;
	struct termios orig_term_attr;
	struct termios new_term_attr;

	/* set the terminal to raw mode */
	tcgetattr(fileno(stdin), &orig_term_attr);
	memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
	new_term_attr.c_lflag &= ~(ECHO|ICANON);
	new_term_attr.c_cc[VTIME] = 0;
	new_term_attr.c_cc[VMIN] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

	/* read a character from the stdin stream without blocking */
	/*   returns EOF (-1) if no character is available */
	character = fgetc(stdin);

	/* restore the original terminal attributes */
	tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

	return character;
}

void change_line(void) // terminal func
{
printf("%s",CMD_FORE_DEFAULT);
printf("%s",CMD_BACK_DEFAULT);
printf("\n");
}

void set_color(char *data) //terminal func
{
	printf("%s", data);
}



void set_data_to_color(block_data data)
{
	if(data == NONE) set_color(CMD_BACK_BLACK);
	else if(data == I_BLOCK) set_color(CMD_BACK_LIGHT_BLUE);
	else if(data == J_BLOCK) set_color(CMD_BACK_BLUE);
	else if(data == L_BLOCK) set_color(CMD_BACK_LIGHT_GRAY);
	else if(data == O_BLOCK) set_color(CMD_BACK_LIGHT_YELLOW);
	else if(data == S_BLOCK) set_color(CMD_BACK_GREEN);
	else if(data == T_BLOCK) set_color(CMD_BACK_MAGENTA);
	else if(data == Z_BLOCK) set_color(CMD_BACK_LIGHT_RED);
	else if(data == WALL) set_color(CMD_BACK_CYAN);
}

/*
static inline void print_block(int len)
{
	for(int i=0;i<len;i++) printf("%s", ONE_BLOCK);
}
*/

static inline void print_one_block(void)
{
	printf("%s", ONE_BLOCK);
}



//1.현재 블럭 가져오기(rand)
//2,1.블럭을 좌표기준으로 출력 O
//3.내려가는 시간사이에 움직임 받기 X
//3_1.움직임을 받으면 현재 블럭을 지우기 O
//3_2.좌표를 이동 전 검산 후 이동 X(좌표 기반출력이라 벽에 비벼진다)
//3_3.이동된 좌표를 기반으로 블록 출력 X
//4.시간이 되면 블럭 지우기 O
//4_1.좌표를 내리기 및 검사 O
//4_2.아래에 블럭이 있다면 블록 고정 및 좌표 초기화 O

//만들 함수목록--
/*
아랫블럭 체크 o
게임오버 체크 o
옆으로 튀어나가는것 체크
현재블록 돌리기 o
(돌리기전에 튀어나감 체크)
*/


void delete_block(void)
{
	double_for(y,x,4)
	{
		if(current_block[y][x] != NONE) background[cur_y+y][cur_x+x]=NONE;
	}
}

void write_block(void)
{
	double_for(y,x,4)
        {
                if(current_block[y][x] != NONE) background[cur_y+y][cur_x+x]=current_block_type;
        }
}

bool check_over_block(void)
{
	double_for(y,x,4)
	{
		if(background[cur_y+y][cur_x+x] != NONE)
		{
			if(current_block[y][x] == current_block_type)
				return true;
		}
	}

	return false;
}

bool check_under_block(void)
{
	double_for(y,x,4)
	{
		if(background[cur_y+y+1][cur_x+x] != NONE) // 아래 블록이 비어있지않고,
		{
			if(current_block[y][x] == current_block_type &&
				current_block[y+1][x] == NONE) // 지금 블록이 블록모양에 존재하고 그 아래에는 없는경우
				return true;
		}
	}

	return false;
}

int check_line(void)
{
	for(int y=0;y<HEIGHT_TETRIS;y++)
	{
		int line=0;
		for(int x=0;x<WIDTH_TETRIS;x++)
		{
			if(background[y][x] != NONE) line++;
		}
		if(line==10)	return y;
		else line=0;
	}

	return -1;
}

void delete_line(int line)
{
	for(int i=0;i<WIDTH_TETRIS;i++) background[line][i]=NONE;

	for(int y=line;y>0;y--)
	{
		for(int x=0;x<WIDTH_TETRIS;x++)
		{
			background[y][x]=background[y-1][x];
		}
	}

	for(int i=0;i<WIDTH_TETRIS;i++) background[0][i]=NONE;
}

void refresh_line(void)
{
	int line=0;
	while(1)
	{
		line=check_line();
		if(line == -1) break;

		delete_line(line);
	}
}

void turn_right_block(char data[4][4])
{
	char temp[4][4];

	double_for(y,x,4)	temp[y][x]=data[3-x][y];
	double_for(y,x,4)	data[y][x]=temp[y][x];
}

void turn_left_block(char data[4][4])
{
	char temp[4][4];

	double_for(y,x,4)	temp[y][x]=data[x][3-y];
	double_for(y,x,4)	data[y][x]=temp[y][x];
}

void show_tetris_debug(void)
{
	printf("\n");
	for(int y=0; y<HEIGHT_TETRIS; y++)
        {
                for(int x=0; x<WIDTH_TETRIS; x++)
                {
			printf("%d ",background[y][x]);
                }
                change_line();
        }
}

void show_tetris_screan(void)
{
	system("clear");

	for(int i=0;i<12;i++)
	{
		set_data_to_color(WALL);
                print_one_block();
	}
	change_line();

	for(int y=0; y<HEIGHT_TETRIS; y++)
	{
		set_data_to_color(WALL);
		print_one_block();

		for(int x=0; x<WIDTH_TETRIS; x++)
		{
			set_data_to_color(background[y][x]);
			print_one_block();
		}
		set_data_to_color(WALL);
		print_one_block();

		change_line();
	}

	for(int i=0;i<12;i++)
        {
                set_data_to_color(WALL);
                print_one_block();
        }
	change_line();
}

void init_tetris(void)
{
	cur_x=3;
	current_block_type=T_BLOCK;

	double_for(y, x, 4)
	{
		current_block[y][x]=block_shapes[current_block_type-1][y][x];
	}

//background[4][5]=1;

/*
background[0][0]=1;
background[0][1]=2;
background[0][2]=3;
background[0][3]=4;
background[0][4]=5;
background[0][5]=6;
background[0][6]=7;
background[0][7]=1;
background[0][8]=2;
background[0][9]=3;
*/

background[19][0]=1;
background[19][1]=2;
background[19][2]=3;
background[19][3]=4;
background[19][4]=5;
background[19][5]=6;
background[19][6]=7;
background[19][7]=1;
background[19][8]=2;
background[19][9]=3;
}

void loop_tetris(void)
{
	time_t start_time=time(NULL);
	time_t end_time=time(NULL);

	while(1)
	{
		if(check_under_block() == true)
		{
			refresh_line();
			cur_x=3;
			cur_y=0;
			if(check_over_block() == true)
			{
				printf("\n\ngame over!\n\n");
				break;
			}
			write_block();
		}

		start_time=time(NULL);
		if(end_time-start_time != 0)
		{
			end_time=start_time;

			delete_block();
			cur_y+=1;
			write_block();

			show_tetris_screan();
			show_tetris_debug();
		}
	char key=getkey();
	if(key==0xffffffff)	continue;
	else if(key==0x1b) break;
	else if(key==0x64) // right
	{
		if(cur_x != 5)
		{
			delete_block();
			cur_x++;

			if(check_over_block() == true)
                        {
                                cur_x--;
                                write_block();
                                continue;
                        }

			write_block();

			show_tetris_screan();
                        show_tetris_debug();
		}
	}
	else if(key==0x61) // left
	{
		if(cur_x != 0)
		{
			delete_block();
			cur_x--;

			if(check_over_block() == true)
			{
				cur_x++;
				write_block();
				continue;
			}

			write_block();

			show_tetris_screan();
			show_tetris_debug();
		}
	}
	else if(key==0x2C)
	{
		delete_block();
		turn_left_block(current_block);

		if(check_over_block() == true)
		{
			turn_right_block(current_block);
			write_block();
			continue;
		}

		write_block();

		show_tetris_screan();
		show_tetris_debug();
	}

	printf("\n\ninpit:%x\n",key);

	}
}


int main(void)
{
init_tetris();

write_block();

//printf("%d\n", check_under_block());
//printf("%d\n", check_over_block());
//printf("%d\n", check_line());

loop_tetris();

/*
write_block();

show_tetris_screan();
show_tetris_debug();
sleep(1);

delete_block(); // one rotate
turn_right_block(current_block);
write_block();

show_tetris_screan();
show_tetris_debug();
sleep(1);


delete_block();
show_tetris_screan();
show_tetris_debug();
sleep(1);
*/

return 0;
}

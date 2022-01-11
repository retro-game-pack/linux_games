#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tetris.h"

block_data background[HEIGHT_TETRIS][WIDTH_TETRIS]; 	// 0,0 is main(left top)
							// [y][x]
int cur_x=0;
int cur_y=0;


void change_line(void)
{
printf("%s",CMD_FORE_DEFAULT);
printf("%s",CMD_BACK_DEFAULT);
printf("\n");
}

void set_color(char *data)
{
	printf("%s", data);
}

void set_data_to_color(block_data data)
{
	if(data == NONE) set_color(CMD_BACK_BLACK);
	else if(data == I_BLOCK) printf("%s", CMD_BACK_LIGHT_BLUE);
	else if(data == J_BLOCK) printf("%s", CMD_BACK_BLUE);
	else if(data == L_BLOCK) printf("%s", CMD_BACK_LIGHT_GRAY);
	else if(data == O_BLOCK) printf("%s", CMD_BACK_LIGHT_YELLOW);
	else if(data == S_BLOCK) printf("%s", CMD_BACK_GREEN);
	else if(data == T_BLOCK) printf("%s", CMD_BACK_MAGENTA);
	else if(data == Z_BLOCK) printf("%s", CMD_BACK_LIGHT_RED);

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

//1.현재 블럭 가져오기
//2,1.블럭을 좌표기준으로 출력
//3.내려가는 시간사이에 움직임 받기
//3_1.움직임을 받으면 현재 블럭을 지우기
//3_2.좌표를 이동 전 검산 후 이동
//3_3.이동된 좌표를 기반으로 블록 출력
//4.시간이 되면 블럭 지우기
//4_1.좌표를 내리기 및 검사
//4_2.아래에 블럭이 있다면 블록 고정 및 좌표 초기화

//만들 함수목록--
/*
print_block(int x, int y) 저장된 블록모양 출력
아랫블럭 체크
옆으로 튀어나가는것 체크
현재블록 돌리기(돌리기전에 튀어나감 체크)
*/


void show_tetris_debug(void)
{
	for(int y=0; y<HEIGHT_TETRIS; y++)
        {
                for(int x=0; x<WIDTH_TETRIS; x++)
                {
			printf("%d ",background[y][x]);
                        //set_data_to_color(background[y][x]);
                        //print_one_block();
                }
                change_line();
        }
}

void show_tetris_screan(void)
{
	for(int y=0; y<HEIGHT_TETRIS; y++)
	{
		for(int x=0; x<WIDTH_TETRIS; x++)
		{
			set_data_to_color(background[y][x]);
			print_one_block();
		}
		change_line();
	}
}

void init_tetris(void)
{
	cur_x=3;
	for(int y=0;y<4;y++)
	{
		for(int x=0;x<4;x++)
			background[3+y][3+x]=block_shapes[0][y][x];
	}
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

	while(1)
	{
	}
}


int main(void)
{
init_tetris();

show_tetris_screan();

printf("\n");
show_tetris_debug();

return 0;
}

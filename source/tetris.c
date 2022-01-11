#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tetris.h"

block_data background[HEIGHT_TETRIS][WIDTH_TETRIS]; 	// 0,0 is main(left top)
							// [y][x]

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
}

static inline void print_block(int len)
{
	for(int i=0;i<len;i++) printf("%s", ONE_BLOCK);
}

static inline void print_one_block(void)
{
	printf("%s", ONE_BLOCK);
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
background[0][0]=2;
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

set_color(CMD_BACK_BLACK);
print_block(10);
change_line();

set_color(CMD_BACK_LIGHT_BLUE);
print_one_block();
set_color(CMD_BACK_LIGHT_RED);
print_one_block();
change_line();

return 0;
}

#ifndef __TETRIS_H__
#define __TETRIS_H__


#include "ansi_color.h"


#define WIDTH_TETRIS	10
#define HEIGHT_TETRIS	20
#define ONE_BLOCK	"  "


enum block_data
{
NONE=0,
I_BLOCK,
J_BLOCK,
L_BLOCK,
O_BLOCK,
S_BLOCK,
T_BLOCK,
Z_BLOCK
};

typedef char block_data;


#endif

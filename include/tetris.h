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
char block_shapes[7][4][4]=
{

{
	{NONE,NONE,NONE,NONE},
	{NONE,NONE,NONE,NONE},
	{I_BLOCK,I_BLOCK,I_BLOCK,I_BLOCK},
	{NONE,NONE,NONE,NONE}
},
{
        {NONE,NONE,NONE,NONE},
        {NONE,NONE,NONE,J_BLOCK},
        {NONE,J_BLOCK,J_BLOCK,J_BLOCK},
        {NONE,NONE,NONE,NONE}
},
{
        {NONE,NONE,NONE,NONE},
        {NONE,L_BLOCK,NONE,NONE},
        {NONE,L_BLOCK,L_BLOCK,L_BLOCK},
        {NONE,NONE,NONE,NONE}
},
{
        {NONE,NONE,NONE,NONE},
        {NONE,O_BLOCK,O_BLOCK,NONE},
        {NONE,O_BLOCK,O_BLOCK,NONE},
        {NONE,NONE,NONE,NONE}
},
{
        {NONE,NONE,NONE,NONE},
        {NONE,NONE,S_BLOCK,S_BLOCK},
        {NONE,S_BLOCK,S_BLOCK,NONE},
        {NONE,NONE,NONE,NONE}
},
{
        {NONE,NONE,NONE,NONE},
        {NONE,NONE,T_BLOCK,NONE},
        {NONE,T_BLOCK,T_BLOCK,T_BLOCK},
        {NONE,NONE,NONE,NONE}
},
{
        {NONE,NONE,NONE,NONE},
        {NONE,Z_BLOCK,Z_BLOCK,NONE},
        {NONE,NONE,Z_BLOCK,Z_BLOCK},
        {NONE,NONE,NONE,NONE}
}

};


#endif

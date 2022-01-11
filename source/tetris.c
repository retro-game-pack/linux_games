#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <pthread.h>

#define CMD_FORE_DEFAULT	"\033[39m"
#define CMD_FORE_RED		"\033[31m"
#define CMD_FORE_GREEN		"\033[32m"
#define CMD_FORE_ORANGE		"\033[0;33m"
#define CMD_FORE_YELLOW		"\033[1;33m"
#define CMD_FORE_BLUE		"\033[0;34m"
#define CMD_FORE_LIGHT_BLUE	"\033[1:34m"
#define CMD_FORE_PURPLE		"\033[35m"
#define CMD_FORE_CYAN		"\033[36m"
#define CMD_FORE_WHITE		"\033[37m"



#define CMD_BACK_DEFAULT	"\033[49m"
#define CMD_BACK_RED		"\033[41m"
#define CMD_BACK_LIGHT_RED	"\033[101m"
#define CMD_BACK_GREEN		"\033[42m"
#define CMD_BACK_ORANGE		"\033[43m"
#define CMD_BACK_BLUE		"\033[44m"
#define CMD_BACK_PURPLE		"\033[45m"
#define CMD_BACK_CYAN		"\033[46m"
#define CMD_BACK_WHITE		"\033[47m"


enum block_color
{
asdf
};

typedef struct
{

char color;
}block_data;


void line_change(void)
{
printf("%s",CMD_FORE_DEFAULT);
printf("%s",CMD_BACK_DEFAULT);
printf("\n");
}


int main(void)
{
printf("%s",CMD_FORE_ORANGE);
printf("asdf\n");
printf("%s", CMD_FORE_RED);
printf("%s", CMD_BACK_RED);
printf("        ");

printf("%s",CMD_BACK_DEFAULT);
printf("\n");

printf("\033[42m");
printf("  ");
printf("%s",CMD_BACK_LIGHT_RED);
printf("  ");

printf("%s",CMD_BACK_DEFAULT);
printf("\n");

return 0;
}

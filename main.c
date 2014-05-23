#include <stdio.h>
#include <termios.h>
#include <unistd.h>
//#include "keyboard.h"
#include "Moving_Cursor.h"

/*This Editor make by nmj12. All right reserve nmj12.*/

enum MODES{
	COMMAND_MODE, INSERT_MODE};

int main(int argc, char *argv[]){
	char buff[255];
	enum MODES mode = COMMAND_MODE;
	int cur_line = 1;
	int cur_col = 1;
	int key1;

//	if(kbhit())
//		{
	key1=getchar();
		switch(/*readch()*/key1)
			{
				case 'i':
				case 'I':
					mode = INSERT_MODE;
				break;

				default:
				break;
			}
		

	if(mode == INSERT_MODE){
			sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 70, cur_line, cur_col);
			fputs(buff, stdout);
			sprintf(buff, "<INSERT MODE> \033[%02d;%02dH", cur_line, cur_col);
			fputs(buff, stdout);
		}

	else if(mode == COMMAND_MODE){
			Moving_Cursor();
			sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 70, cur_line, cur_col);
			fputs(buff, stdout);
			sprintf(buff, "<COMMAND MODE> \033[%02d;%02dH", cur_line, cur_col);
			fputs(buff, stdout);
		}
	else{
			printf("error");
		}
	return 0;
}

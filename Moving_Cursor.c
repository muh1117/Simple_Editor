#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "Moving_Cursor.h"

/*enum MODES{
	COMMAND_MODE};

int main(){
	moving_cursor();
	return 0;
}
*/
int Moving_Cursor(){
/*	char buff[255];
	enum MODES mode = COMMAND_MODE;

	int cur_line = 1;
	int cur_col = 1;*/
	const int min_line = 1;
	const int min_col = 1;
	const int max_line = 20;
	const int max_col = 80;
	int key;

	fputs("\033[2J", stdout);
	fputs("\033[0;0H", stdout);
	struct termios oldt, newt;
	tcgetattr (STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newt);

	while(1){
		key = getchar();
		if(mode == COMMAND_MODE){
				switch(key){
					case 'a':
					case 'A':
						cur_col--;
						if(cur_col < min_col) cur_col = min_col;
					break;

					case 's':
					case 'S':
						cur_line++;
						if(cur_line > max_line) cur_line = max_line;
					break;

					case 'w':
					case 'W':
						cur_line--;
						if(cur_line < min_line) cur_line = min_line;
					break;

					case 'd':
					case 'D':
						cur_col++;
						if(cur_col > max_col) cur_col = max_col;
					break;
				}//end switch
				
/*				sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 65, cur_line, cur_col);
				fputs(buff, stdout);
				sprintf(buff, "\033[%02d;%02dH", cur_line, cur_col);
				fputs(buff, stdout);*/
			}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}

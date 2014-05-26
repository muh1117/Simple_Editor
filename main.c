#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
//#include "Moving_Cursor.h"

/*This Editor make by nmj12. All right reserve nmj12.*/

char buff[255];
int cur_line = 1;
int cur_col = 1;
//const int min_line = 1;
//const int min_col = 1;
//const int max_line = 20;
//const int max_col = 80;
int key;
int key1;
int loop = 1;
int loop1 = 1;

enum MODES{
	COMMAND_MODE, INSERT_MODE};

int main(int argc, char *argv[]){
	char buff[255];
//	system("clear");
	enum MODES mode = COMMAND_MODE;
//	int cur_line = 1;
//	int cur_col = 1;
//	int key1;
//	int loop = 1;

//	if(kbhit())
//		{
	while(loop)
		{
		key1=getchar();
		switch(/*readch()*/key1)
			{
				case 'i':
				case 'I':
					mode = INSERT_MODE;
				break;

				case 'c':
				case 'C':
					mode = COMMAND_MODE;
				break;
	
				case 'q':
				case 'Q':
					loop = 0;
					exit(0);
				break;

//				default:
//				break;
			}
		
		if(mode == INSERT_MODE){
			system("clear");

			sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
			fputs(buff, stdout);
			sprintf(buff, "<INSERT MODE>\033[%02d;%02dH", cur_line, cur_col);
			fputs(buff, stdout);
			
			
			char text[80];
			FILE *pFILE;
			pFILE = fopen("editor.txt", "w");

			gets(text);

			fputs(text, pFILE);

			fclose(pFILE);
		}

		else if(mode == COMMAND_MODE){
				system ("clear");
				MovingCursor();
//				sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 70, cur_line, cur_col);
//				fputs(buff, stdout);
//				sprintf(buff, "<COMMAND MODE> \033[%02d;%02dH", cur_line, cur_col);
//				fputs(buff, stdout);
		}
		else{
				printf("error");
				exit(-1);
		}
	}
	return 0;
}

int MovingCursor(){
	char buff[255];
	enum MODES mode = COMMAND_MODE;

	int cur_line = 1;
	int cur_col = 1;
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

	while(loop1){
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

					case 'i':
					case 'I':
						loop1 = 0;
						mode == INSERT_MODE;
					break;

					case 'q':
					case 'Q':
						exit(0);
					break;
				}//end switch
				
				sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 65, cur_line, cur_col);
				fputs(buff, stdout);
				sprintf(buff, "<COMMAND MODE>\033[%02d;%02dH", cur_line, cur_col);
				fputs(buff, stdout);
			}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/* nmj12

	Copy right is with muh1117@naver.com

	Do not modify this comment.
	I allow re-distribution of this source code only under the education purpose.
*/

char buff[255];
int cur_line = 1;
int cur_col = 1;
const int min_line = 1;
const int min_col = 1;
const int max_line = 20;
const int max_col = 80;
char key;
char key1;
char key2;
int num;
int count = 0;
int loop = 1;
int loop1 = 1;
int loop2 = 1;
char text[80][20];
char in[sizeof(text)] = "";
int iOpen;
struct termios oldt, newt;


enum MODES{
	COMMAND_MODE, INSERT_MODE};

int main(int argc, char *argv[]){
	char buff[255];
	enum MODES mode = COMMAND_MODE;

	printf("Please press any key.\n");

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= (~ICANON);
	newt.c_lflag &= (~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	while(loop)
		{
		key1=getchar();
		switch(key1)
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
			}

		fflush(stdin);
		
		if(mode == INSERT_MODE){
			system("clear");

			tcgetattr(STDIN_FILENO, &oldt);
			newt = oldt;
			newt.c_lflag = ECHO; 
			newt.c_lflag &= ~ICANON;
			tcsetattr(STDIN_FILENO, TCSANOW, &newt);

			sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
			fputs(buff, stdout);
			sprintf(buff, "<INSERT MODE>\033[%02d;%02dH", cur_line, cur_col);
			fputs(buff, stdout);
			
			iOpen = fopen("editor.txt", "w+");

			if(iOpen){
				cur_line++;
				text[cur_col - 1][cur_line - 1];
				if(cur_col>max_col){
						cur_col=1;
						cur_line++;
						if(cur_line>max_line) cur_line = max_line;
					}

				fread(text, 80, 20, iOpen);
				printf("%s\n", text);
				fwrite(text, strlen(text), 1, iOpen);
				fwrite("\n", strlen("\n"), 1, iOpen);
			}

				scanf("%s", &text);
				fwrite(text, strlen(text), 20, iOpen);
				fclose(iOpen);
				printf("\nsave.\n\n");

				tcgetattr(STDIN_FILENO, &oldt);
				newt = oldt;
				newt.c_lflag &= ~ECHO;
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//}				
/*				else{
					printf("\nERROR!\n");
				}*/

				key2 = getchar();
				switch(key2){
					case 'c':
					case 'C':
						mode = COMMAND_MODE;
					break;

					case 'q':
					case 'Q':
						tcgetattr(STDIN_FILENO, &oldt);
						newt = oldt;
						newt.c_lflag = ECHO;
						tcsetattr(STDIN_FILENO, TCSANOW, &newt);
						exit(1);
					break;
				}
			fflush(stdin);
			}
		
		else if(mode == COMMAND_MODE){
				system ("clear");

				iOpen = fopen("editor.txt", "r");

				if(iOpen){
						tcgetattr(STDIN_FILENO, &oldt);
						newt = oldt;
						newt.c_lflag = ECHO;
						newt.c_lflag = ICANON;
						tcsetattr(STDIN_FILENO, TCSANOW, &newt);

						loop1 = 1;					
						MovingCursor();
				}
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

	if(iOpen){
		fread(text, 80, 1, iOpen);
		printf("%s", text);
	}
	fclose(iOpen);

	tcgetattr (STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ICANON;
	newt.c_lflag &= ~ECHO;
	tcsetattr (STDIN_FILENO, TCSANOW, &newt);

		sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
		fputs(buff, stdout);
		sprintf(buff, "<COMMAND MODE>\033[%02d;%02dH", cur_line, cur_col);
		fputs(buff, stdout);

		fflush(stdin);

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
						mode = INSERT_MODE;
					break;

					case 'q':
					case 'Q':
						tcgetattr(STDIN_FILENO, &oldt);
						newt = oldt;
						newt.c_lflag = ECHO;
						tcsetattr(STDIN_FILENO, TCSANOW, &newt);
						exit(1);
					break;
				}
				}//end switch

				sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
				fputs(buff, stdout);
				sprintf(buff, "\033[%02d;%02dH", cur_line, cur_col);
				fputs(buff, stdout);
			}
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag = (ICANON|ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	}

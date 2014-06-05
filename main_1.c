#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/*This Editor make by nmj12. All right reserve nmj12.*/

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
int loop = 1;
int loop1 = 1;
int loop2 = 1;
char text[80];
char in[sizeof(text)] = "";
int iOpen;
char data[80][20];
struct termios oldt, newt;


enum MODES{
	COMMAND_MODE, INSERT_MODE};

int main(int argc, char *argv[]){
	char buff[255];
	enum MODES mode = COMMAND_MODE;

	printf("Please press any key.\n");

//	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= (~ICANON);
	newt.c_lflag &= (~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	while(loop)
		{
		key1=getchar();
		//key1=getch();
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
printf("1");
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
			
			iOpen = open("editor.txt", O_RDWR|O_CREAT, 0644);

			if(iOpen > 0){
				cur_line++;
				data[cur_col - 1][cur_line - 1] = text;
				if(cur_col>max_col){
						cur_col=1;
						cur_line++;
						if(cur_line>max_line) cur_line = max_line;
					}
					gets(text);
					//puts(text);
					write(iOpen, text, strlen(text));
					close(iOpen);
					printf("\nsave.\n\n");
					}
				else{
					printf("\nERROR!\n");
				}
printf("2");
				key2 = getchar();
				//key2=getch();
				switch(key2){
					case 'c':
					case 'C':
						mode = COMMAND_MODE;
					break;

					case 'q':
					case 'Q':
						//loop1=0;
						exit(1);
					break;
				}
			fflush(stdin);
		}

		else if(mode == COMMAND_MODE){
				system ("clear");

/*				tcgetattr(STDIN_FILENO, &oldt);
				newt = oldt;
				newt.c_lflag = ICANON;
				tcsetattr(STDIN_FILENO, TCSANOW, &newt);*/

				iOpen = open("editor.txt", O_RDONLY);

				if(iOpen > 0){
					if(text != EOF){
						tcgetattr(STDIN_FILENO, &oldt);
						newt = oldt;
						newt.c_lflag = ECHO;
						tcsetattr(STDIN_FILENO, TCSANOW, &newt);

						read(iOpen, in, sizeof(text));
						puts(in);
						close(iOpen);
//						puts(in);
						loop1 = 1;					
						MovingCursor();
					}
				}
				else{
					printf("\nERROR!\n\n");
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

	tcgetattr (STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ICANON;
	newt.c_lflag &= ~ECHO;
	tcsetattr (STDIN_FILENO, TCSANOW, &newt);

		sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
		fputs(buff, stdout);
		sprintf(buff, "<COMMAND MODE>\033[%02d;%02dH", cur_line, cur_col);
		fputs(buff, stdout);

	//while(loop1){
		fflush(stdin);
		//loop1=1;
		while(loop1){
		key = getchar();

		if(mode == COMMAND_MODE){
printf("3");
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
						exit(1);
					break;
				}
				}//end switch
printf("4");
				sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
				fputs(buff, stdout);
				sprintf(buff, "\033[%02d;%02dH", cur_line, cur_col);
				fputs(buff, stdout);
			}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
printf("5");
	}
//	return 0;
//}

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

struct termios oldt, curt, newt;
char data[80][20];

int key;
int key1;
int key2;
int loop = 1;
int loop1 = 1;
int loop2 = 1;
//int count = 0;

char text[80];
char in[sizeof(text)] = "";

int iOpen;



enum MODES{
	COMMAND_MODE, INSERT_MODE};

int main(int argc, char *argv[]){
	char buff[255];
	enum MODES mode = COMMAND_MODE;

//	if(count == 0){
		printf("Please press any key.\n");
//	}
//	else{
//		printf("Please press key 'i' or 'c'. If you want quit, please press key 'q'.\n");
//	}
	while(loop)
		{
		key1=getchar();
		switch(key1)
			{
				case 'i':
				case 'I':
					mode = INSERT_MODE;
//					count++;
				break;

				case 'c':
				case 'C':
					mode = COMMAND_MODE;
//					count++;
				break;
	
				case 'q':
				case 'Q':
					loop = 0;
					exit(0);
				break;
			}
		
		if(mode == INSERT_MODE){
			system("clear");

			sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
			fputs(buff, stdout);
			sprintf(buff, "<INSERT MODE>\033[%02d;%02dH", cur_line, cur_col);
			fputs(buff, stdout);

			switch (key) {
				case 'c': // escape key code
						mode = COMMAND_MODE;
						tcgetattr ( STDIN_FILENO, &curt );
						newt = curt;
						newt.c_lflag &= ~( ECHO );
						tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
				break;

				default:
						mode = INSERT_MODE;
						//calibrate cursor
						cur_col++;
						//save contents
						data[cur_col-1][cur_line-1] = key;
						if (cur_col > max_col) {
							cur_col = 1;
							cur_line++;
							if (cur_line > max_line) cur_line = max_line;
						}
				break;
		
			iOpen = open("editor.txt", O_RDWR|O_CREAT, 0644);

			if(iOpen > 0){
				gets(text);
				write(iOpen, in, strlen(in));
				close(iOpen);
				printf("\nsave.\n\n");
			}
			else{
				printf("\nERROR!\n");
			}
		}

		if(mode == COMMAND_MODE){
			system ("clear");

			iOpen = open("editor.txt", O_RDONLY);
			
			if(iOpen > 0){
				if(text != EOF){
					read(iOpen, in, sizeof(text));
					close(iOpen);
					puts(in);
				}
			}
			else{
				printf("\nERROR!\n\n");
			}
				
			MovingCursor();
		}

		else{
				printf("error");
				exit(-1);
		}
	}
	return 0;
}
}

int MovingCursor(){
//	char buff[255];
	enum MODES mode = COMMAND_MODE;

//	int cur_line = 1;
//	int cur_col = 1;
	//const int min_line = 1;
	//const int min_col = 1;
	//const int max_line = 20;
	//const int max_col = 80;
//	int key;

	fputs("\033[2J", stdout);
	fputs("\033[0;0H", stdout);
	//struct termios oldt, curt, newt;
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
						
						tcgetattr ( STDIN_FILENO, &curt );
						newt = curt;
						newt.c_lflag |= ( ECHO );
						tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
					break;

					case 'q':
					case 'Q':
						exit(0);
					break;
				}//end switch
				
				sprintf(buff, "\033[%02d;%02dH%02d:%02d", 0, 60, cur_line, cur_col);
				fputs(buff, stdout);
				sprintf(buff, "<COMMAND MODE>\033[%02d;%02dH", cur_line, cur_col);
				fputs(buff, stdout);
			}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}

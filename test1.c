#include <stdio.h>

int main(int argc, char *argv[]){

	fputs("\033[6;10H", stdout);
	fputs("\033[6;10HHello\n", stdout);//cursor moving

	return 0;
}

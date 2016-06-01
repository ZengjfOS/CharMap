#include "includes.h"
void checkTerminalSize(row, col){
	struct winsize size;
	if(isatty(STDOUT_FILENO) == 0) exit(1);
	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) < 0){
		perror("ioctl TIOCGWINSZ error"); 
		exit(1);
	}
	if(size.ws_row < 24 || size.ws_col < 80){
		printf("\033[%dm-->please checking terminal: rows >=24 && cols <= 80\033[%dm\n", GREENF, WHITEF);
		exit(0);
	}
	ppts->rows = size.ws_row;
	ppts->cols = size.ws_col;
}

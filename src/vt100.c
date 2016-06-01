#include "includes.h"

/**
 * move the cursor to the point (x, y)
 */
void moveCursorToPoint(int row, int col){
    printf("\033[%d;%dH", row, col);
}

/**
 * move the cursor to the point (x, y)
 * and put the char (ch) at this point
 */
void putCharAtPoint(char ch, int row, int col){
    printf("\033[%d;%dH%c", row, col, ch);
}

/**
 * clear the terminal window, and put the cursor
 * to the point (1,1)
 */
void initScreen(void){
    printf("\033[2J");
    printf("\033[1;1H");
}

void clearAllSet(void){
    printf("\033[0m");
}

void showCursor(void){
    printf("\033[?25h");
}

void hiddenCursor(void){
    printf("\033[?25l");
}

void clearWindow(void){
    printf("\033[2J");
}

/**
 * set the color include front and background color once a time 
 */
void setColor(int color){
    printf("\033[%dm", color);
}
void setAttribute(int attribute){
    printf("\033[%dm", attribute);
}
void flashCursorAtPoint(int row, int col){
    moveCursorToPoint(row, col);
    printf("\033[6m");
}

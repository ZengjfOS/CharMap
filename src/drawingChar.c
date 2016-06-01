#include "includes.h"

void drawCornerChar(int row, int col, char ch){
    drawPoint(row, col, ch);
}
void drawDateAndTime(int row, int col){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    moveCursorToPoint(row,col);
    printf("%4d-%02d-%02d %02d:%02d:%02d", 1900+timeinfo->tm_year, 1+timeinfo->tm_mon, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
void drawDate(int row, int col){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    moveCursorToPoint(row,col);
    printf("%4d-%02d-%02d", 1900+timeinfo->tm_year, 1+timeinfo->tm_mon, timeinfo->tm_mday);
}
void drawTime(int row, int col){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    moveCursorToPoint(row,col);
    printf("%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
void drawText(int row, int col, char* ch){
	moveCursorToPoint(row, col);
    printf("%s", ch);
}
void fillBox(int firstRow, int firstCol, int secondRow, int secondCol, char ch){
    int row = 0;
    int col = 0;
    for (row = firstRow+1; row < secondRow; row++){
        for (col = firstCol+1; col < secondCol; col++){
            drawPoint(row, col , ch);
        }
    }
}
void drawBox(int firstRow, int firstCol, int secondRow, int secondCol, char horizonChar, char verticalChar, char cornerChar){
	horizonLine(firstRow, firstCol, (secondCol-firstCol), horizonChar);
	horizonLine(secondRow, firstCol, (secondCol-firstCol), horizonChar);
	verticalLine(firstCol, firstRow, (secondRow-firstRow), verticalChar);
	verticalLine(secondCol, firstRow, (secondRow-firstRow), verticalChar);
    drawCornerChar(firstRow, firstCol, cornerChar);
    drawCornerChar(firstRow, secondCol, cornerChar);
    drawCornerChar(secondRow, secondCol, cornerChar);
    drawCornerChar(secondRow, firstCol, cornerChar);
}
void drawPoint(int row, int col, char ch){
	putCharAtPoint(ch, row, col);
}
void horizonLine(int row, int firstCol, int cols, char ch){
	int col = firstCol;
	int maxOfCols = firstCol + cols;
	for(; col < maxOfCols+1; col++){
		drawPoint(row, col, ch);
	}
}
void verticalLine(int col, int firstRow, int rows, char ch){
	int row = firstRow;
	int maxOfRows = firstRow + rows;
	for(; row < maxOfRows+1; row++){
		drawPoint(row, col, ch);
	}
}

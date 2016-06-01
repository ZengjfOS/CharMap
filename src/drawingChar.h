#ifndef __DRAWINGGRAPH__H
	#define __DRAWINGGRAPH__H

	#include <stdio.h>
	#include <math.h>
	#include "vt100.h"

	void fillBox(int firstRow, int firstCol, int secondRow, int secondCol, char ch);
	void drawBox(int firstRow, int firstCol, int secondRow, int secondCol, char horizonChar, char verticalChar, char cornerChar);
	void drawPoint(int row, int col, char ch);
	void horizonLine(int row, int firstCol, int cols, char ch);
	void verticalLine(int col, int firstRow, int rows, char ch);
    void drawText(int row, int col, char* ch);
    void drawDateAndTime(int row, int col);
    void drawTime(int row, int col);
    void drawDate(int row, int col);
    void drawCornerChar(int row, int col, char ch);
#endif

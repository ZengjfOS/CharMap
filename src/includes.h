#ifndef __INCLUDES__H__
	#define __INCLUDES__H__
	
	#include "common.h"
	#include "properties.h"
	#include "kbhit.h"
	#include "vt100.h"
	#include "drawingChar.h"
	#include "component.h"
	#include "terminal.h"
	#include "properties.h"
	#include "task.h"
	
	#define true 1
	#define false 0

	properties* ppts;
	//command* commands;
	unsigned int count;
	int  playFlag;
	char guideChar[5];
	char titleChar[titleSize];
    int titleLength;
	char inputChar[20];
	char* charMap;
	char cmd[20];
	int inputCharIndex;
    char pressedChar;
	

#endif

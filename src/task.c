#include "includes.h"

//extern char* charMap;

void init(void){
	ppts = parseProperties("./properties.ppts");
	ppts->keyValue = getKeyvalue(); /* 这里内容和上面其实有冲突，解析同一个文件两次，这在效率上是不能容忍的，但不前不打算修复　*/
    titleLength = strlen(ppts->title);
	checkTerminalSize(ppts->rows, ppts->cols);
	
    //char charMap[ppts->rows - 4][ppts->cols - 2+1] = {};
    signal(SIGINT, exitByCtrl_c);
	initScreen();
    init_keyboard();
    initTitleCharArray();
    initCharMap();
    initCommands();
	////hiddenCursor();
	drawFrame(2, 1, ppts->rows-1, ppts->cols, '-', '|', '+');
	printf("\n");
	
}
void initTitleCharArray(void){
    int i = 0;
    for(i = 0; i < titleLength - 1; i++){ //主要是因为计算字符串长度的时候会多计算一个'\0'
        titleChar[i] = ' ';
    }
}
void exitByCtrl_c(int singal){
    moveCursorToPoint(ppts->rows, 1);
    close_keyboard();
    printf("\n\n\033[32m----> Thank you for used charMaps   :)\n\n");
    clearAllSet();
    showCursor();
    exit(0);
}
void FrequencyDivisionForTask(void){
	count++;
    hiddenCursor();
    keyBoardHandler();
    showKeyCode(pressedChar);

    if((count % 2) == 0){
        divisionByTwo();
    }
    if((count % 5) == 0){
        divisionByFive();
    }
    if((count % 10) == 0){
        divisionByTen();
    }
    if((count % 20) == 0){
        divisionByTwenty();
    }
    if((count % 25) == 0){
        divisionByTwentyFive();
    }
    if((count % 50) == 0){
        divisionByFifty();
    }
    if(playFlag != -1){
        clearAllSet();
        showCursor();
        flashCursorAtPoint(ppts->rows, inputCharIndex + 5);
    }
    fflush(0);  //一定要记得添加这个，不然显示不了光标
	usleep(ppts->interval);
}
void divisionByTwo(void){
}
void divisionByFive(void){
}
void divisionByTen(void){
    drawGuideChar();
	commandHandler();
}
void divisionByTwenty(void){
	drawTitle();
}
void divisionByTwentyFive(void){
    showFunctionName();
}
void divisionByFifty(void){
    drawDateAndTime(ppts->rows, ppts->cols - 18);
}
void keyBoardHandler(void){
	if(kbhit()){
		pressedChar = readch();
        if(playFlag == -1){
            playFlag = -2;
        }
        /**
         * enter、backspace 键另外处理  
         */
        if(pressedChar != 10 && pressedChar != 127){
			putInputCharToArrayWithShow(pressedChar);
        }else if(pressedChar == 127){
			dealWithBackSpace(pressedChar);
		}else if(pressedChar == 10){
            /**
             *  let the inputChar var to the command var
             */
            if(getCommand() == 0){
				/**
				 *  deal with the command 
				 */
				commandForward();
			}
        }
    }
}

#include "includes.h"

unsigned int count = 0;
int titleMoveFlag = 0;
char guideChar[5] = ">> :";
char titleChar[titleSize] = {};
char inputChar[20] = "";
int inputCharIndex = 0;
char cmd[20] = "";
int playFlag = 0;
command commands[] = {
    {"rdw", playRandomWave, "RandomWare", 1,  NULL},
    {"stop", virtualStop, "virtualStop", 2,  NULL},
    {"quit", exitCharMaps, "quit", 3, NULL},
    {"snw", playSnowing, "Snowing", 4, NULL},
    {"", NULL, "", -111, NULL}
};



void exitCharMaps(void){
	moveCursorToPoint(ppts->rows, 0);
	close_keyboard();
	printf("\n\n----> Thank you for used charMaps   :)\n\n");
    clearAllSet();
    showCursor();
	exit(0);
}
void virtualStop(void){
    playFlag = 0;
}
void initCharMap(void){
    int charMapLength = (ppts->rows-4)*(ppts->cols-2+1)*sizeof(char);
    charMap = malloc(charMapLength);
    int i = 0;
    for(i = 0; i < charMapLength; i++){
        charMap[i] = '\0';
    }
}
char * getCharMapRowPoint(int row){
    int charMapRowLength = (ppts->cols-2+1)*sizeof(char);
    return charMap + charMapRowLength * row;
}
void setCharMapPointWithChar(int row, int col, char ch){
    int charMapRowLength = (ppts->cols-2+1)*sizeof(char);
    *((charMap + charMapRowLength * row) + col) = ch;
}
void setCharMapWithChar(char ch){
    int col = 0;
    int row = 0;
    char* charMapTemp = 0;
	for(col = 0; col < ppts->cols - 2; col++){
		for(row = 0; row < ppts->rows - 4; row++){
            charMapTemp = (char *)getCharMapRowPoint(row);
            *(charMapTemp + col) = ch;
		}
	}
}
void playRandomWave(void){
    int row = 0;
	int col = 0;
	int cutRow = 0;
    int charMapRowLength = (ppts->cols-2+1)*sizeof(char);
	for(col = 0; col < ppts->cols - 2; col++){
		for(row = 0; row < ppts->rows - 4; row++){
            setCharMapPointWithChar(row, col, '*');
		}
	}
	for(col = 0; col < ppts->cols - 2; col++){
		cutRow = (int)((rand()/(RAND_MAX + 1.0)) * (ppts->rows -4));
		for(row = 0; row <= cutRow; row++){
			setCharMapPointWithChar(row, col, ' ');
		}
	}
	for(row = 0; row < ppts->rows - 4; row++){
		//注意是cols-2，不是cols-1
		setCharMapPointWithChar(row, ppts->cols - 2, '\0');
	}
	fillBox(2, 1, ppts->rows - 1, ppts->cols, ' ');
	for(row = 0; row < ppts->rows - 4; row++){
		drawText(row+3, 2, getCharMapRowPoint(row));
	}
    fflush(0);
}
void initCommands(void){
    ppts->cmds = commands;
    //确保程序正确任务对应cmdNo是唯一的
    int i = 0;
    for(i = 0; strlen(ppts->cmds[i].cmdAlias) != 0; i++){
        ppts->cmds[i].cmdNo = (i + 1);
    }
}
void commandHandler(void){
    int i = 0;
    for(i = 0; strlen(ppts->cmds[i].cmdAlias) != 0; i++){
        if(playFlag == ppts->cmds[i].cmdNo){
            ppts->cmds[i].handler();
            return;
        }
    }
}
void commandForward(void){
    int i = 0;
    for(i = 0; strlen(ppts->cmds[i].cmdAlias) != 0; i++){
        if(strcmp(ppts->cmds[i].cmdAlias, cmd) == 0){
            playFlag = ppts->cmds[i].cmdNo;
			if(strcmp(ppts->cmds[i].functionName, "Snowing") == 0){
				initSnowing();
			}
			int i = strlen(cmd) - 1;
			for(; i >= 0; i--){
				cmd[i] = '\0';
			}
            return;
        }
    }
    playFlag = -1;
    drawText(ppts->rows, 5, "                          |");
    drawText(ppts->rows, 5, "unknow command            |");
    setCharMapWithChar(' ');
    showCharMap();
    fflush(0);
}
void showCharMap(void){
    int row = 0;
    int col = 0;
    char* charMapTemp = 0;
	for(row = 0; row < ppts->rows - 4; row++){
        charMapTemp = (char *)getCharMapRowPoint(row);
		drawText(row+3, 2, (char *)charMapTemp);
		fflush(0);
	}
}
void initSnowing(void){
    int i = 0;
    int row = 0;
    int col = 0;
	for(col = 0; col < ppts->cols - 2; col++){
		for(row = 0; row < ppts->rows - 4; row++){
			setCharMapPointWithChar(row, col, ' ');
		}
	}
    for(i = 0; i < ppts->cols - 2; i++){
        row = (int)((rand()/(RAND_MAX + 1.0)) * (ppts->rows - 4));
        col = (int)((rand()/(RAND_MAX + 1.0)) * (ppts->cols - 2));
		setCharMapPointWithChar(row, col, '*');
    }
}
void playSnowing(void){
	/*注意声明定义的时候的长度，和使用下标的时候是不一样的的*/
	int size = ppts->cols - 2 + 1;
	char temp[size];
	int row = 0;
	fillBox(2, 1, ppts->rows - 1, ppts->cols, ' ');
	//strcpy(temp, charMap[19]);
	strcpy(temp, getCharMapRowPoint(ppts->rows - 4 - 1));
	for(row = (ppts->rows - 4 - 1); row > 0; row--){
		//strcpy(charMap[row], charMap[row - 1]);
		strcpy(getCharMapRowPoint(row), getCharMapRowPoint(row - 1));
	}
	strcpy(getCharMapRowPoint(row), temp);
	for(row = 0; row < ppts->rows - 4; row++){
		//drawText(row+3, 2, charMap[row]);
		drawText(row+3, 2, getCharMapRowPoint(row));
	}
	showCharMap();
    fflush(0);
}
int getCommand(void){
	if(strlen(inputChar) == 0){
		drawText(ppts->rows, 5, "                          |");
		drawText(ppts->rows, 5, "please input command :)   |");
		drawText(1, 1, "command: NULL             ");
        playFlag = -1;
		return -1;
	}
    strcpy(cmd, inputChar);
    int i = 0;
    for(i = 19; i > -1; i--){
        inputChar[i] = '\0';
    }
    inputCharIndex = 0;
    drawText(ppts->rows, 5, "                          ");
    drawText(1, 1, "                          ");
    moveCursorToPoint(1, 1);
    printf("command:%s", cmd);
    fflush(0);
	return 0;
}
void showKeyCode(char ch){
	moveCursorToPoint(ppts->rows, ppts->cols - 34);
    printf("| keycode:%03d | ", ch);
    fflush(0);
}
void dealWithBackSpace(char ch){
    if(inputCharIndex == 0){
        return;
    }
    inputCharIndex--;
    inputChar[inputCharIndex] = '\0';
    drawText(ppts->rows, 5, "                          ");
    drawText(ppts->rows, 5, inputChar);
    fflush(0);
}
void putInputCharToArrayWithShow(char ch){
    if(inputCharIndex > maxInputCharForCommand){
        drawText(ppts->rows, 5, "please input chars less 20");
        fflush(0);
        usleep(1000000);
        while(kbhit()){
            readch();
        }
        inputCharIndex = 0;
        int i = 0;
        for(i = 19; i > -1; i--){
            inputChar[i] = '\0';
        }
        playFlag = -1;
        return;
    }else if(inputCharIndex == 0){
        drawText(ppts->rows, 5, "                          ");
        int col = 0;
        for (col = 0; col < maxInputCharForCommand; col++){
            inputChar[col] = '\0';
        }
    }
    inputChar[inputCharIndex] = ch;
    drawText(ppts->rows, 5, inputChar);
    inputCharIndex++;
    fflush(0);
}
void drawGuideChar(void){
	moveCursorToPoint(ppts->rows, 1);
    setAttribute(32);
    char temp = ' ';
    temp = guideChar[2];
    guideChar[2] = guideChar[1];
    guideChar[1] = guideChar[0];
    guideChar[0] = temp;
    printf("%s", guideChar);
    clearAllSet();
    drawText(ppts->rows, 5 + 26, "|");
    fflush(0);
}
void drawTitle(void){
    int i = 0;
    setAttribute(7);
    titleMoveFlag++;
    if(titleMoveFlag < titleLength){ 
        for(i = 0; i < titleMoveFlag; i++){
            titleChar[titleLength - 2 - i] = ppts->title[titleMoveFlag -1 - i];
        }
    }else if(titleMoveFlag == titleLength * 2){
		for(i = 0; i < titleLength - 1; i++){ //主要是因为计算字符串长度的时候会多计算一个'\0'
			titleChar[i] = ' ';
		}
    }else if(titleMoveFlag < titleLength * 3){ 
        for(i = 0; i < titleMoveFlag % titleLength; i++){
            titleChar[i] = ppts->title[i];
        }
    }else if(titleMoveFlag == titleLength * 4){
		for(i = 0; i < titleLength - 1; i++){ //主要是因为计算字符串长度的时候会多计算一个'\0'
			titleChar[i] = ' ';
		}
    }else if(titleMoveFlag < titleLength * 5){ 
        for(i = 0; i < titleMoveFlag % titleLength; i++){
            titleChar[titleLength - 2 - i] = ppts->title[titleLength - 2 - i];
        }
    }else if(titleMoveFlag == titleLength * 6){
		for(i = 0; i < titleLength - 1; i++){
			titleChar[i] = ' ';
		}
    }else if(titleMoveFlag < titleLength * 7){ 
        for(i = 0; i < titleMoveFlag % titleLength; i++){
            titleChar[i] = ppts->title[i];
            // titleLength - 2 - i 表达式中-2的原因在于字符串多了'\0'，加之数组下标要-1
            titleChar[titleLength - 2 - i] = ppts->title[titleLength - 2 - i];
        }
    }else if(titleMoveFlag == titleLength * 8){
        titleMoveFlag = 0;
		for(i = 0; i < titleLength - 1; i++){
			titleChar[i] = ' ';
		}
    }
    drawText(1, ppts->cols/2-titleLength/2, titleChar);
    clearAllSet();
    fflush(0);
}

void drawFrame(int firstRow, int firstCol, int secondRow, int secondCol, char horizonChar, char verticalChar, char cornerChar){
    drawBox(firstRow, firstCol, secondRow, secondCol, horizonChar, verticalChar, cornerChar);
    fflush(0);
}

void showRandomNo(void){
	printf("\033[1;1H%d",  (int)((rand()/(RAND_MAX + 1.0)) * (ppts->rows -4)));
	fflush(0);
}
void showFunctionName(void){
    int i = 0;
	printf("\033[1;%dHFN:%s", ppts->cols - 16, "              " );
    for(i = 0; strlen(ppts->cmds[i].cmdAlias) != 0; i++){
        if(playFlag == ppts->cmds[i].cmdNo){
	        printf("\033[1;%dHFN:%s", ppts->cols - 16, ppts->cmds[i].functionName );
            break;
        }
    }
	fflush(0);
}

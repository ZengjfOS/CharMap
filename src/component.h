#ifndef __COMPONENT_H__
    #define __COMPONENT_H__

    void drawGuideChar(void);

    void drawTitle(void);

	void putInputCharToArrayWithShow(char ch);

	void dealWithBackSpace(char ch);
    //void getBackSpace(char ch);
    void showKeyCode(char ch);

    void initCharMap(void);
    char* getCharMapRowPoint(int row);
    void setCharMapWithChar(char ch);
    void setCharMapPointWithChar(int row, int col, char ch);
    void showCharMap(void);

    void initCommands(void);
	void commandForward(void);
    int getCommand(void);
    void commandHandler(void);

    void drawInputChar(void);
    double  getRandomNumber(void);
    void playRandomWave(void);
    void initSnowing(void);
    void playSnowing(void);
    void virtualStop(void);
    void exitCharMaps(void);
    void showFunctionName(void);
	void drawFrame(int firstRow, int firstCol, int secondRow, int secondCol, char horizonChar, char verticalChar, char cornerChar);
	void showRandomNo(void);
#endif

#ifndef __PRINTFCONTROL__
    #define __PRINTFCONTROL__
    #define BLACKF  30
    #define REDF    31
    #define GREENF  32
    #define YELLOWF 33
    #define BLUEF   34
    #define PURPLEF 35
    #define WHITEF  37

    #define BLACKG  40
    #define REDG    41
    #define GREENG  42
    #define YELLOWG 43
    #define BLUEG   44
    #define PURPLEG 45
    #define WHITEG  47
    /**
     * move the cursor to the point (x, y)
     */
    void moveCursorToPoint(int row, int col);
    /**
     * move the cursor to the point (x, y)
     * and put the char (ch) at this point
     */
    void putCharAtPoint(char ch, int row, int col);
    /**
     * clear the terminal window, and put the cursor
     * to the point (0,1)
     */
    void initScreen(void);
    /**
     * clear the terminal window
     */
    void clearWindow(void);
    void hiddenCursor(void);
    void showCursor(void);
    void clearAllSet(void);
    void setColor(int color);
    void setAttribute(int attribute);
	void flashCursorAtPoint(int row, int col);
#endif

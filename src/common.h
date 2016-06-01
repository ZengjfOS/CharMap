#ifndef __COMMON_H__
	#define __COMMON_H__
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
	#include <errno.h>
	#include <termios.h>
	#include <time.h>
	#include <signal.h>
	#include <unistd.h>
	#include <sys/ioctl.h>

	#define keyValueSize 20
	#define versionSize 10
	#define titleSize 16
	#define defaultRows 24
	#define defaultCols 80
	#define bufferSize 1024
    #define maxInputCharForCommand 20
	
	
	typedef struct KeyValue{
		struct KeyValue* next;
		char key[ keyValueSize ];
		char value[ keyValueSize ];
	}keyvalue;
	
	typedef struct Command{
        char cmdAlias[ keyValueSize ];
		void (*handler)(void);
		char functionName[ keyValueSize ];
        int cmdNo;
		struct command* next;
	}command;

	typedef struct Properties{
		int rows;
		int cols;
		int interval;
		command* cmds;
		keyvalue* keyValue;
		char version[ versionSize ];
		char title[ titleSize ];
	}properties;
	
#endif

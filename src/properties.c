#include "common.h"
#include "properties.h"

/**
  * 用于存放从文件读取出来的键值对
  */
char lineBuffer[ bufferSize ] = {};
int getProperties(char* path){
	FILE *propertiesFd = NULL;
	propertiesFd = fopen(path, "r");
	if(propertiesFd == NULL){
		printf("can't found the giving file.\ngoing to open the default file:./properties.ppts.\n");
		propertiesFd = fopen("./properties.ppts", "r");
		if(propertiesFd == NULL){
			perror("can't opent the default file.\n");
			return -1;
		}
	}
	FILE *temp = fopen("./properties.temp", "w+");
	if(temp == NULL){
		perror("can't found the file: properties.temp\n");
		return -1;
	}
	char dealWithBuffer[ bufferSize ] = {};
	int index = 0;
	int i = 0;
	while(fgets(lineBuffer, bufferSize, propertiesFd)){
		index = 0;
		for(i = 0; i < 100; i++){
			/**
			  * if the char was '\0' or '#' ,go to next line
			  * '\0' was the end of line 
			  * '#' was the annotate of line
			  * and with the '#' to the code at a line, we need the '\n' to replace
			  */
			if(lineBuffer[i] == '\0' || lineBuffer[i] == '#'){
				if(index != 0 && lineBuffer[i] == '#')
					dealWithBuffer[index] = '\n';
				break;
			/**
			  * delete the char ' ' and '\t'
			  */
			}else if(lineBuffer[i] == ' ' || lineBuffer[i] == '\t' ){
				continue;
			}
			dealWithBuffer[index++] = lineBuffer[i];
		}
		fputs(dealWithBuffer, temp);
		fflush(temp);
		for(i = 0; i < index; i++){
			dealWithBuffer[i] = '\0';
		}
	}
	fclose(temp);
	fclose(propertiesFd);
	return 0;
}

keyvalue* getKeyvalue(void){
	FILE *temp = fopen("./properties.temp", "r");
	if(temp == NULL){
		perror("can't open the file: properties.temp\n");
		return NULL;
	}
	/**
	  * key/value 在处理时候的下标
	  */
	int index = 0;
	/**
	  * 循环使用的变量
	  */
	int i = 0;
	/**
	  * key保存的位置
	  */
	char key[1024] = {};
	/**
	  * value保存的位置
	  */
	char value[1024] = {};
	/**
	  * 保存key最后一个字符的边界，在'\n'之后
	  */
	int keyBounds = 0;
	/**
	  * 保存value最后一个字符的边界，在'\n'之后
	  */
	int valueBounds = 0;
	/**
	  * 从lineBuffer中获取key到value的标志
	  */
	int keyToValueFlag = 0;
	/**
	  * key value 键值对首指针
	  */
	keyvalue* keyvalueHead = NULL;
	keyvalue* currentKeyvalue = NULL;
	keyvalue* previewKeyvalue = NULL;
	while(fgets(lineBuffer, 1024, temp)){
		index = 0;
		keyBounds = 0;
		valueBounds = 0;
		keyToValueFlag = 0;
		currentKeyvalue = malloc(sizeof(keyvalue));
		for(i = 0; i < 1024; i++){
			/**
			  * 键值对以=号分开
			  */
			if(lineBuffer[i] == '='){
				key[index] = '\n';
				keyBounds = index + 1;
				index = 0;
				keyToValueFlag = 1;
				continue;
			}
			/**
			  * 处理行尾
			  */
			if(lineBuffer[i] == '\0'){
				valueBounds = index + 1;
				break;
			}
			if(keyToValueFlag ==0){
				key[index++] = lineBuffer[i];
			}else if(keyToValueFlag == 1){
				value[index++] = lineBuffer[i];
			}
		}
		strcpy(currentKeyvalue->key, key);
		strcpy(currentKeyvalue->value, value);
		currentKeyvalue->next = NULL;
		//printf("key : %svalue: %s", currentKeyvalue->key, currentKeyvalue->value);
		if(keyvalueHead == NULL){
			keyvalueHead = currentKeyvalue;
			previewKeyvalue = currentKeyvalue;
		}else {
			previewKeyvalue->next =  currentKeyvalue;
			previewKeyvalue =  currentKeyvalue;
			currentKeyvalue = NULL;
		}
		//testKeyvalue(keyvalueHead);
		for(i = 0; i < keyBounds; i++){
			key[i] = '\0';	
		}
		for(i = 0; i < valueBounds; i++){
			value[i] = '\0';	
		}
	}
	fclose(temp);
	return keyvalueHead;
}

properties* parseKeyvalue(keyvalue* head){
	if(head == NULL){
		printf("the parameter was NULL");
		return NULL;
	}
	properties* ppts = malloc(sizeof(properties));
	keyvalue* currentKeyvalue = head;
	while(currentKeyvalue){
		//printf("%d ----->keyvalue: %s=%s", index, currentKeyvalue->key, currentKeyvalue->value);
		/**
		  * 本来打算直接用strcmp,但是貌似strcmp会自动比较字符串所占数组的大小
		  * 所以改成使用strncmp
		  */
		if(!strncmp(currentKeyvalue->key, "title", strlen("title"))){
			strcpy(ppts->title, currentKeyvalue->value);
		}else if(!strncmp(currentKeyvalue->key, "rows", strlen("rows"))){ 
			ppts->rows = atoi(currentKeyvalue->value);
		}else if(!strncmp(currentKeyvalue->key, "cols", strlen("cols"))){ 
			ppts->cols = atoi(currentKeyvalue->value);
		}else if(!strncmp(currentKeyvalue->key, "interval", strlen("interval"))){ 
			ppts->interval = atoi(currentKeyvalue->value);
		}else if(!strncmp(currentKeyvalue->key, "version", strlen("version"))){ 
			strcpy(ppts->version, currentKeyvalue->value);
		}
		currentKeyvalue = currentKeyvalue->next;
	}
	//printf("properties: %d %d %d %s %s", ppts->rows, ppts->cols, ppts->interval, ppts->version, ppts->title);
	return ppts;
}

properties* parseProperties(char* path){
	if(getProperties(path) == 0){
		return parseKeyvalue(getKeyvalue());
	}else{
		printf("prepared file error");
	}
}
char* getValue(char* key){
	if(key == NULL){
		printf("the parameter: key was NULL");
		return NULL;
	}
	keyvalue* currentKeyvalue = getKeyvalue();
	while(currentKeyvalue){
		/**
		  * 本来打算直接用strcmp,但是貌似strcmp会自动比较字符串所占数组的大小
		  * 所以改成使用strncmp
		  */
		if(strncmp(currentKeyvalue->key, key, strlen(key)) == 0){
			//printf("value: %s\n", currentKeyvalue->value);
			return currentKeyvalue->value;
		}
		currentKeyvalue = currentKeyvalue->next;
	}
}

/**
  * 这个是测试函数
  */
void testKeyvalue(keyvalue* head){
	if(head == NULL){
		printf("the parameter was NULL");
		return;
	}
	keyvalue* currentKeyvalue = head;
	int index = 1;
	while(currentKeyvalue){
		printf("%d ----->keyvalue: %s=%s", index, currentKeyvalue->key, currentKeyvalue->value);
		currentKeyvalue = currentKeyvalue->next;
		index++;
	}
}

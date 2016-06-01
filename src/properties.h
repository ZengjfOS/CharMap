#ifndef __PROPERTIES__H
	#define __PROPERTIES__H
	
	int getProperties(char* path);
	keyvalue* getKeyvalue(void);
	void testKeyvalue(keyvalue* head);
	properties* parseKeyvalue(keyvalue* head);
	properties* parseProperties(char* path);
	char* getValue(char*);

#endif

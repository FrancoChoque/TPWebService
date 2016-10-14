#ifndef ADT_Client__H__
#define ADT_Client__H__


#include <stdio.h>
#include "errors.h"

#define STR_LEN 21;


typedef (modifier_t*)(client_t*,void* data);



typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;	


typedef struct{
	client_t* client;
	void* data;
	modifier_t data_type;
}ADT_Client_t;


int ADT_Client_create(ADT_Client*);
int ADT_Client_destroy(ADT_Client*);	
int ADT_Client_modify
#endif
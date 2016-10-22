#ifndef ADT_Client__H__
#define ADT_Client__H__


#include <stdio.h>
#include "errors.h"

#define STR_LEN 20;


typedef (modifier_t*)(client_t*,void* data);
typedef (comparator_t*)(void*,void*);


typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;	




int add_client()

int compare_by_id(void*,void*);


#endif
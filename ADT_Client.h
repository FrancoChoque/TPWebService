#ifndef ADT_Client__H__
#define ADT_Client__H__


#include <stdio.h>
#include "errors.h"

#define STR_LEN 20;
#define MAX_STR_LEN 140;




typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;	




int destroy_client(void*);

int copy_client(void*, const void*);


#endif
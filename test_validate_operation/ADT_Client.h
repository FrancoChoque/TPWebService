#ifndef ADT_Client__H__
#define ADT_Client__H__


#include <stdio.h>
#include "errors.h"
#include "string.h"

#define STR_LEN 20
#define MAX_STR_LEN 140
#define FIELD_CLIENT_ID 0
#define FIELD_CLIENT_NAME 1
#define FIELD_CLIENT_SURNAME 2
#define FIELD_CLIENT_PHONE 3
#define FIELD_CLIENT_MAIL 4
#define FIELD_CLIENT_DATE 5
#define DELIM ';'



typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;	




void destroy_client(void*);

int copy_client(void*, const void*);

int compare_client(const void*, const void*);


#endif
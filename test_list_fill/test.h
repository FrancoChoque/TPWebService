#ifndef MAIN__H__
#define MAIN__H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "ADT_List.h"

#define FIELD_CLIENT_ID 0
#define FIELD_CLIENT_NAME 1
#define FIELD_CLIENT_SURNAME 2
#define FIELD_CLIENT_PHONE 3
#define FIELD_CLIENT_MAIL 4
#define FIELD_CLIENT_DATE 5
#define STR_LEN 140
#define DELIM ';'


char* strdup (const char*);
int split(char*, char***, int*);


typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;

void print_client(client_t*);

#endif
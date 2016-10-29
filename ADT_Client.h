#ifndef ADT_Client__H__
#define ADT_Client__H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"

#define STR_LEN 20
#define MAX_STR_LEN 140
#define CLIENT_ID "id"
#define CLIENT_NAME "Name"
#define CLIENT_SURNAME "Surname"
#define CLIENT_TELEPHONE "Telephone"
#define CLIENT_MAIL "Mail"
#define CLIENT_DATE "Time"


#define CLIENT_FIELD_ID 0
#define CLIENT_FIELD_NAME 1
#define CLIENT_FIELD_SURNAME 2
#define CLIENT_FIELD_PHONE 3
#define CLIENT_FIELD_MAIL 4
#define CLIENT_FIELD_DATE 5


typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;	




void destroy_client(void*);
int compare_client(const void*, const void*);
int copy_client(void*, const void*);

int modify_client_name(void*,void*);
int modify_client_surname(void*,void*);
int modify_client_telephone(void*,void*);
int modify_client_mail(void*,void*);
int modify_client_date(void*,void*);



char* print_client_as_jason(const void*);
char* print_client_as_xml(const void*);



#endif
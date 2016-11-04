#ifndef ADTWS_OP__H__
#define ADTWS_OP__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"


#define METHOD_POST "POST"
#define METHOD_GET "GET"
#define METHOD_DEFAULT METHOD_GET
#define TYPE_XML "xml"
#define TYPE_JASON "jason"


#define URL_DELIM_SLASH '/'
#define URL_DELIM_COLON ':'

#define URL_FIELD_ENCRYPTION 1
#define URL_FIELD_HOST 2
#define URL_FIELD_PORT 3
#define URL_FIELD_OPERATION 4
#define URL_FIELD_GET_DATA 5


#define REQUEST_DELIM ' '
#define REQUEST_FLAG_METHOD "-X"
#define REQUEST_FLAG_CONTENT_TYPE "-H"
#define REQUEST_FLAG_DATA "-d"
#define XML_OPERATION "<Operation>"
#define XML_CLIENT "<Client>"


typedef struct{
	char* request;
	char* response;
	char* operation;
	char* operation_time;
	char* format;
}ADTWS_Op;






int ADTWS_Op_create(ADTWS_Op*, int, const char**);
int ADTWS_Op_destroy(ADTWS_Op*);
int ADTWS_Op_set_operation(ADTWS_Op*);
int ADTWS_Op_set_request(ADTWS_Op*, int, const char**);
int ADTWS_Op_set_format(ADTWS_Op*);
int ADTWS_Op_set_operation_time(ADTWS_Op*);
int ADTWS_Op_set_response(ADTWS_Op*, char*);

char* ADTWS_Op_get_operation(ADTWS_Op);
char* ADTWS_Op_get_operation_time(ADTWS_Op);
char* ADTWS_Op_get_request(ADTWS_Op);
char* ADTWS_Op_get_format(ADTWS_Op);
char* ADTWS_Op_get_response(ADTWS_Op);




int ADTWS_Op_get_data(char**, const char*, ADTWS_Op);
int ADTWS_Op_get_method(char**, ADTWS_Op);
int ADTWS_Op_get_host(char**, ADTWS_Op);


int ADTWS_Op_copy(ADTWS_Op*, ADTWS_Op);


void strtoxml(char*, const char*, const char*);
void strtojason(char*, const char*, const char*);

int get_local_time(char**);
#endif
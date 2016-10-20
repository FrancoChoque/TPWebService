#ifndef ADTWS_Ops__H__
#define ADTWS_Ops__H__ 

#include <stdio.h>
#include "errors.h"
#define DEFAULT_FORMAT "GET"

typedef struct{
	char* request;
	char* response;
	char* operation;
	char* operation_time;
	char* format;
}ADTWS_Ops;


typedef int (data_parser*)(void*);



int ADTWS_Ops_create(ADTWS_Ops*);
int ADTWS_Ops_destroy(ADTWS_Ops*);
int parse_xml();
int parse_jason();



int ADTWS_Ops_get_operation(ADTWS_Ops*);
int ADTWS_Ops_set_operation(ADTWS_Ops*);
int ADTWS_Ops_log_operation(ADTWS_Ops*);
int ADTWS_Ops_validate_operation(ADTWS_Ops*);


#endif
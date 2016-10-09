#ifndef ADTWS_Ops__H__
#define ADTWS_Ops__H__ 

#include <stdio.h>

typedef struct{
	char* request;
	char* response;
	char* operation;
	char* operation_time;
	char* format;
}ADTWS_Ops;


ADTWS_Ops_create();
ADTWS_Ops_destroy();

ADTWS_Ops_get_operation();
ADTWS_Ops_set_operation();
ADTWS_Ops_log_operation();

#endif
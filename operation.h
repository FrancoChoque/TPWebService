#ifndef OPERATION__H__
#define OPERATION__H__ 

#include <string.h>
#include "errors.h"


typedef int (*ws_operation) (ADTWS*);

typedef enum{
	GET,
	POST
}method_t;

int compare_operation(const void*, const void*);

typedef struct {
	char* csv_file;
	char* op_file;
	char* log_file;
	method_t method;
	
}config;



#endif
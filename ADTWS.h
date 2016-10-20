#ifndef ADTWS__H__
#define ADTWS__H__ 

#include <stdio.h>
#include "errors.h"
#include "ADTWS_Ops.h"
#include "ADT_List.h"


typedef struct{
	ADTWS_Ops current_op;
	list_t all_operations;
	list_t clients;
	queue_t execution_queue;
}ADTWS;


int ADTWS_create(ATDWS*, char*);
int ADTWS_valid_operation(ADTWS*);
int ADTWS_consume(ADTWS*);
int ADTWS_destroy (ADTWS*);
int ADTWS_get_client_list();
int ADTWS_get_operation_list();


#endif
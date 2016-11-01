#ifndef ADTWS__H__
#define ADTWS__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"
#include "errors.h"
#include "utils.h"
#include "straight_list.h"
#include "ADT_Client.h"
#include "ADT_Queue.h"
#include "ADTWS_Op.h"

#define OPERATION_PATH_POSITION 0
#define CLIENT_PATH_POSITION 1
#define LOG_PATH_POSITION 2
#define MAX_OPERATIONS 8

#define FORMAT_CHOP 40

typedef struct{
	ADTWS_Op operation_t;
	list_t operation_list;
	list_t client_list;
	queue_t execution_queue;
	char* config_file;
}ADTWS;


typedef int(*operate_t)(ADTWS*);



/*operate_t operations[MAX_OPERATIONS] = {
	get_time,
	get_max_id_client,
	set_max_id_client,
	get_client_by_id,
	set_client_by_id,
	get_all_clients,
	get_all_operations,
	validate_operation
};*/


int ADTWS_create(ADTWS*, ADTWS_Op);
int ADTWS_destroy (ADTWS*);
int ADTWS_valid_operation(ADTWS*);
int ADTWS_consume(ADTWS*);
int ADTWS_set_operation(ADTWS*, ADTWS_Op);
int ADTWS_set_config_file(ADTWS*);


typedef void (*modify_string_t)(char*, const char*, const char*);
typedef char* (*client_to_string_t)(client_t);

int get_file_path(char**, const char*, int);


int log_operation(ADTWS);
#endif
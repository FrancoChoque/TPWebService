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
#include "queue.h"
#include "ADTWS_Op.h"

#define OPERATION_PATH_POSITION 0
#define CLIENT_PATH_POSITION 1
#define LOG_PATH_POSITION 2
#define MAX_OPERATIONS 5

#define FORMAT_CHOP 40

typedef struct{
	ADTWS_Op operation_t;
	list_t operation_list;
	list_t client_list;
	queue_t execution_queue;
	char* config_file;
}ADTWS;


typedef int(*operate_t)(ADTWS*, const char*, const char*, char**);


int ADTWS_create(ADTWS*, ADTWS_Op);
int ADTWS_destroy (ADTWS*);
int ADTWS_valid_operation(ADTWS*);
int ADTWS_consume(ADTWS*);
int ADTWS_set_operation(ADTWS*, ADTWS_Op);
int ADTWS_set_config_file(ADTWS*);

int log_operation(ADTWS);


int get_all_operations(ADTWS*, const char*, const char*, char**);
int get_all_clients(ADTWS*, const char*, const char*, char**);
int get_time(ADTWS*, const char*, const char*, char**);
int set_max_id_client(ADTWS*, const char*, const char*, char**);
int get_max_id_client(ADTWS*, const char*, const char*, char**);
int get_client_by_id(ADTWS*, const char*, const char*, char**);
int set_client_by_id(ADTWS*, const char*, const char*, char**);
int validate_operation(ADTWS*, const char*, const char*, char**);
#endif
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "ADTWS.h"
#include "ADT_List.h"
#include "ADT_Client.h"


int ADTWS_create(ADTWS* ws, ADTWS_Ops* op){

	int st;
	list_t client_list, operation_list;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = create_list(&client_list,sizeof(client_t), destroy_client, copy_client))!= OK){
		return st;
	}

	if((st = fill_client_list(&client_list))!= OK){
		return st;
	}
	

	if((st = create_list(&operation_list,sizeof(operation_t), destroy_operation, copy_operation))!= OK){
		return st;
	}

	if((st = fill_operation_list(&opearation_list))!= OK){
		return st;
	}

	ADTWS->all_clients = client_list;
	ADTWS->all_operations = operation_list;
	ADTWS->current_op = *op;


	return OK;			
}


int ADTWS_valid_operation(ADTWS* ws){


}



int fill_client_list(list_t* client_list){

	
	client_t client;

	if(client_list == NULL){
		return ERROR_NULL_POINTER;
	}

	if((csv_file = fopen(client_file_path,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(fgets(str,STR_LEN,fp)!= NULL){

		
	}

	

}


int create_client(client_t* client){


	FILE* csv_file;


}



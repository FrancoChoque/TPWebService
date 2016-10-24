#include "ADTWS.h"

int ADTWS_create(ADTWS* ws, ADTWS_Op op){

	int st;
	list_t client_list, operation_list;
	queue_t operation_queue;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = ADT_List_create(&client_list,sizeof(client_t),(list_destroy_t)destroy_client,(list_copy_t)copy_client))!= OK){
		return st;
	}

	if((st = fill_client_list(&client_list))!= OK){
		ADT_List_destroy(&client_list);
		return st;
	}
	

	if((st = ADT_List_create(&operation_list,sizeof(operation_t), destroy_operation, copy_operation))!= OK){
		ADT_List_destroy(&client_list);
		return st;
	}

	if((st = fill_operation_list(&opearation_list))!= OK){
		ADT_List_destroy(&client_list);
		ADT_List_destroy(&operation_list);
		return st;
	}

	ADTWS->client_list = client_list;
	ADTWS->operation_list = operation_list;
	ADTWS->operation_t = op;
	ADTWS->execution_t = operation_queue;

	return OK;			
}



int ADTWS_valid_operation(ADTWS* ws){

	
	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if(search_list((void*) ADTWS_Op_get_operation(ws->operation_t), ws->operation_list,(list_compare_t)compare_operation)){
		return INVALID_OPERATION;
	}

	return OK;
}


int ADTWS_consume(ADTWS* ws){

	char* op;

	op = ADTWS_Op_get_operation(ws->operation_list);

	op(ws);

	return OK;

}

int ADTWS_destroy(ADTWS* ws){


}




int fill_operation_list(list_t* operation_list){

	FILE* fp;

	char str[STR_LEN];
	

	if(operation_list == NULL){
		return ERROR_NULL_POINTER;
	}

	if((fp = fopen(operation_file_path,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(!feof(fp)){
		if((fgets(str,sizeof(str),fp)) == NULL) break;
		if((st = ADT_List_insert_node(operation_list,mov_next,(void*)str))!= OK){
			fclose(fp);
			return st;
		}
	}
	
	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}

	return OK;
}



int fill_client_list(list_t* client_list){

	client_t client;
	FILE* fp;
	char str[MAX_STR_LEN]; 
	char *temp, **fieldv;
	int fieldc;

	if(client_list == NULL){
		return ERROR_NULL_POINTER;
	}

	if((fp = fopen(client_file_path,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(!feof(fp)){

		if((fgets(str,sizeof(str),fp)) == NULL) break;
		if((st = split_csv_string(str,&fieldv,&fieldc))!= OK){ /*split_csv_string() está en utils.c*/
			return st;
			fclose(fp);
		}
		client.client_id = (int) strtoul(fieldv[FIELD_CLIENT_ID],&temp,10);
		strncpy(client.name,fieldv[FIELD_CLIENT_NAME],STR_LEN-1);
		strncpy(client.surname,fieldv[FIELD_CLIENT_SURNAME],STR_LEN-1);
		strncpy(client.telephone,fieldv[FIELD_CLIENT_PHONE],STR_LEN-1);
		strncpy(client.mail,fieldv[FIELD_CLIENT_MAIL],STR_LEN-1);
		strncpy(client.date,fieldv[FIELD_CLIENT_DATE],STR_LEN-1);
		if((st = ADT_List_insert_node(client_list,mov_next,(void*)&client))!= OK){
			destroy_string_array(fieldv,fieldc);
			free(fieldv);
			fieldv = NULL;
			fclose(csv_file);
			return st;
		}
	}

	destroy_string_array(fieldv,fieldc); /*también está en utils.c*/
	free(fieldv);
	fieldv = NULL;
	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}
	
	return OK
}





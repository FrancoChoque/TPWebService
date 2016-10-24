#include "operation.h"

int compare_operation(const void* a, const void* b){

	char *str_a, *str_b;

	str_a = (char*) a;
	str_b = (char*) b;

	return strcmp(a,b);
}

int get_client_by_id(ADTWS* ws, int id){

	client_t client;
	char* response;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	client.client_id = id;

	if(ADT_List_search(&client,ws->client_list,compare_client) == TRUE){
		ADT_List_get_node(&client,ws->client_list->current->data);
		
	}

	return OK;
}



int get_time(ADTWS* ws){

	time_t time_stamp;
	struct tm* display;
	char time_string[STR_LEN];
	

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if(time(&time_stamp) == -1){
		return ERROR_SYS_TIME;
	}
	
	if((display = localtime(&time_stamp)) == NULL){
		return ERROR_SYS_TIME;
	}
	
	strftime(time_string,STR_LEN,"%d/%m/%Y %H:%M:%S",display);
	
	ADTWS_Op_set_response(ADTWS->operation,time_string);

	
}


int print_client(char* dest, client_t source, char* format){

	if(!strcmp(format,FORMAT_JASON)){
		
	}
}




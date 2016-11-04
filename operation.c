#include "operation.h"


int destroy_operation(void* op){

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	return OK;
}


int copy_operation(void* dest, const void* src){

	char *d,*s;

	d = (char*) dest;
	s = (char*) src;

	if(src == NULL){
		return ERROR_NULL_POINTER;
	}

	strcpy(d,s);

	return OK;
}



int compare_operation(const void* a, const void* b){

	char *str_a, *str_b;

	str_a = (char*) a;
	str_b = (char*) b;

	return strcmp(str_a,str_b);
}




/*





int get_client_by_id(ADTWS* ws){

	client_t client;
	char* str;
	int st;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	

	client.client_id = id; 

	if(ADT_List_search(&ws->client_list,(void*)&client,(list_compare_t)compare_client) == TRUE){
		if((st = ADT_List_get_node(&ws->client_list,(void*)&client))!= OK){
			return st;
		}
	}

	str = print_client(&client);

	if((st = ADTWS_Op_set_response(ADTWS->operation_t,str))!= OK){
		free(str);
		return st;
	}
	
	return OK;
}




int set_client_by_id(ADTWS* ws){

	client_t client;
	char* str;
	int st;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}




	if(ADT_List_search(&ws->client_list,(void*)&client,compare_client) == TRUE){
		
		if((st = ADT_List_update(&ws->client_list,(void*)&client))!= OK){
			return st;
		}
	}
	else{
		if((st = ADT_List_insert(&ws->client_list,mov_next,(void*)&client))!= OK){
			return st;
		}
	}

	str = print_client(&client);

	if((st = ADTWS_Op_set_response(ADTWS->operation_t,str))!= OK){
		free(str);
		return st;
	}

	return OK;
}






int get_max_id_client(ADTWS* ws){

	client_t client;
	int st;


	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	

	while(move_current(mov_next) == TRUE);

	if((st = ADT_List_get_node(ws,(void*)&client))!= OK){
		return st;
	}
	
	str = modify(&client);

	if((st = ADTWS_Op_set_response(ws->operation_t,str))!= OK){
		return st;
	}

	return OK
}


*/










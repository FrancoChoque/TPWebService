#include "operation.h"


int destroy_operation(void* op){

	char* str;

	str = (char*) op;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	free(str);
	str = NULL;

	return OK;
}


int copy_operation(void* dest, const void* src){

	char *d,*s;

	d = (char*) dest;
	s = (char*) src;

	if(src == NULL){
		return ERROR_NULL_POINTER;
	}

	if((d = strdup(s)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}



int compare_operation(const void* a, const void* b){

	char *str_a, *str_b;

	str_a = (char*) a;
	str_b = (char*) b;

	return strcmp(a,b);
}



int get_time(ADTWS* ws){

	time_t time_stamp;
	struct tm* display;
	char time_string[STR_LEN];
	char* response;
	int st;
	

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
	
	response = print_as(time_string); /*xml/jason*/

	ADTWS_Op_set_response(ADTWS->operation,response);

	return OK;
	
}




int get_client_by_id(ADTWS* ws){

	client_t client;
	char* str;
	int st;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	/*FALTA PEDIR MEMORIA PARA str*/

	client.client_id = id; /*todavía no tengo ni idea de como sacar el id desde el request*/

	if(ADT_List_search(&ws->client_list,(void*)&client,(list_compare_t)compare_client) == TRUE){
		if((st = ADT_List_get_node(&ws->client_list,(void*)&client))!= OK){
			return st;
		}
	}

	str = print_client(&client); /*todavía no tengo ni idea de cuanto o cómo tengo que alocarle al string que contiene un cliente*/

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

	/*FALTA PEDIR MEMORIA PARA str*/

	

	/*acá iría función que parsea el jason/xml y llena los campos del client*/


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

	str = print_client(&client); /*xml/jason*/

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

	/*FALTA PEDIR MEMORIA PARA str*/

	while(move_current(mov_next) == TRUE); /*Me voy al final de la lista*/

	if((st = ADT_List_get_node(ws,(void*)&client))!= OK){
		return st;
	}
	
	str = print_as(&client); /*xml/jason*/

	if((st = ADTWS_Op_set_response(ws->operation_t,str))!= OK){
		return st;
	}

	return OK
}


int set_max_id_client(ADTWS* ws){

	client_t client;
	char* str;
	int st;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	client.client_id = id; /*todavía no tengo ni idea de como sacar el id desde el request*/

	/*FALTA PEDIR MEMORIA PARA str*/

	while(move_current(mov_next) == TRUE);
	
	if((st = ADT_List_insert_node(ws,mov_next,(void*)&client))!= OK){
		return st;
	}
	
	str = print_as(&client); /*xml/jason*/
	
	if((st = ADTWS_Op_set_response(ws->operation_t,str))!= OK){
		return st;
	}

	return OK;

}


int get_all_clients(ADTWS* ws){

	client_t client;

	char* aux, str;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	/*FALTA PEDIR MEMORIA PARA aux*/

	move_current(ws,mov_first);

	do{
		if((st = ADT_List_get_node(ws,(void*)&client))!= OK){
			free(aux);
			aux = NULL;
			return st;
		}
		aux = print_as(&client); /*xml/jason*/
		if((str = (char*) realloc(str,strlen(aux))) == NULL){
			free(aux);
			return ERROR_MEMORY_SHORTAGE;
		} 
		strcat(str,aux); /*no estoy seguro si es legal hacer esto, porque en primer ciclo str tiene memoria alocada pero está vacío*/
			
	}while(move_current(list,mov_next) == OK);

	if((st = ADTWS_Op_set_response(ws->operation_t,str))!= OK){
		free(aux);
		free(str);
		return st;
	}

	return OK;
}





int get_all_operations(ADTWS* ws){

	
	char *str, *aux;

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if((aux = (char*) malloc(ws->operation_t->data_size)) == NULL){ /*abstraction rape*/
		return ERROR_MEMORY_SHORTAGE;
	}

	move_current(ws,mov_first);
	
	do{
		if((st = ADT_List_get_node(ws,(void*)aux)) == NULL){
			free(aux);
			if(str != NULL){
				free(str); /*este if está por si el programa muere en el primer ciclo, me parece que no se puede hacer free() de algo que puede ser NULL*/
			}
			return st;
		}
		aux = print_as(aux); /*xml/jason*/
		if((str = (char*) realloc(str,strlen(aux))) == NULL){
			free(aux);
			return ERROR_MEMORY_SHORTAGE; 
		}
		strcat(str,aux);	
	}while(move_current(list,mov_next) == OK);

	if((st = ADTWS_Op_set_response(ws->operation_t,str))!= OK){
		free(aux);
		free(str);
		return st;
	}

	return OK;
}







int log_operation(ADTWS_Op* op){

	FILE* fp;
	

	if(response == NULL){
		return ERROR_NULL_POINTER;
	}

	if((fp = fopen(log_file_path,"a") == NULL){
		return ERROR_OPENING_FILE;


	fprintf(fp,"%s;%s;\n%s;\n%s",ADTWS_Op->operation_time,ADTWS_Op->operation,ADTWS_Op->request,ADTWS_op->response);

	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}

	return OK;
}






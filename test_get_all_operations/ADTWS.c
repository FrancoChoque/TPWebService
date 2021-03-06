#include "ADTWS.h"


int fill_operation_list(list_t*, const char*);
int fill_client_list(list_t*, const char*);
int get_all_operations(ADTWS*);

int ADTWS_create(ADTWS* ws, ADTWS_Op op){

	int st;
	list_t client_list, operation_list;
	queue_t operation_queue;

	
	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = ADTWS_set_operation(ws,op))!= OK){
		return st;
	}

	if((st = ADTWS_set_config_file(ws))!= OK){
		ADTWS_destroy(ws);
		return st;
	}

	if((st = straight_list_create(&client_list,sizeof(client_t),(straight_list_copy_t)copy_client,(straight_list_destroy_t)destroy_client))!= RES_OK){
		ADTWS_destroy(ws);
		return st;
	}
	
	if((st = fill_client_list(&client_list,ws->config_file))!= OK){
		ADTWS_destroy(ws);
		return st;
	}
	
	if((st = straight_list_create(&operation_list,(size_t)STR_LEN,(straight_list_copy_t)copy_operation,(straight_list_destroy_t)destroy_operation))!= RES_OK){
		ADTWS_destroy(ws);
		return st;
	}

	if((st = fill_operation_list(&operation_list,ws->config_file))!= OK){
		ADTWS_destroy(ws);
		return st;
	}

	if((st = ADT_Queue_create(&operation_queue,STR_LEN,(queue_copy_t)copy_operation,(queue_destroy_t)destroy_operation))!= OK){
		ADTWS_destroy(ws);
		return st;
	}
	
	ws->client_list = client_list;
	ws->operation_list = operation_list;
	ws->execution_queue = operation_queue;

	return OK;			
}



int ADTWS_valid_operation(ADTWS* ws){


	char *str, *response;
	char temp[29];
	
	if((str = strdup(ADTWS_Op_get_operation(ws->operation_t))) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	straight_list_move(&ws->operation_list,straight_list_first);



	do{
		straight_list_get(&ws->client_list,(void*)temp);
		if(!strcmp(temp,str)) break;
	}while(straight_list_move(&ws->operation_list,straight_list_next) == TRUE);

	if(strcmp(temp,str)){
		return ERROR_INVALID_OPERATION;
	}

	response = (char*) malloc(20);

	

	ADTWS_Op_set_response(&ws->operation_t,response);

	return OK;
}


int ADTWS_consume(ADTWS* ws){

	
	int st;
		
	if((st = get_all_operations(ws))!= OK){
		ADTWS_Op_set_response(&ws->operation_t,"error_msg[st]");
		return st;
	}

	return OK;

}

int ADTWS_destroy(ADTWS* ws){

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}
	
	
	ADTWS_Op_destroy(&ws->operation_t);
	
	
	if(!straight_list_is_empty(&ws->client_list)){
		straight_list_destroy(&ws->client_list);
	}
	
	if(!straight_list_is_empty(&ws->operation_list)){
		straight_list_destroy(&ws->operation_list);
	}
	
	if(!queue_is_empty(ws->execution_queue)){	
		ADT_Queue_destroy(&ws->execution_queue);
	}
	
	if(ws->config_file != NULL){
		free(ws->config_file);
	}

	return OK;
}


int ADTWS_set_operation(ADTWS* ws, ADTWS_Op op){

	
	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if((ws->operation_t.request = strdup(op.request)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	if((ws->operation_t.operation = strdup(op.operation)) == NULL){
		free(ws->operation_t.request);
		return ERROR_MEMORY_SHORTAGE;
	}

	if((ws->operation_t.operation_time = strdup(op.operation_time)) == NULL){
		free(ws->operation_t.request);
		free(ws->operation_t.operation);
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if((ws->operation_t.format = strdup(op.format)) == NULL){
		free(ws->operation_t.request);
		free(ws->operation_t.operation);
		free(ws->operation_t.operation_time);
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}



int ADTWS_set_config_file(ADTWS* ws){

	char* str;

	ADTWS_Op_get_domain(&str,ws->operation_t);

	strcat(str,".conf");

	ws->config_file = str;	

	return OK;

}





int fill_operation_list(list_t* operation_list, const char* config_file){

	FILE* fp;

	char str[STR_LEN], *operation_file,*operation;
	int st;
	

	if(operation_list == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = get_file_path(&operation_file,config_file,OPERATION_PATH_POSITION))!= OK){
		return st;
	}

	if((fp = fopen(operation_file,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(!feof(fp)){
		if((fgets(str,sizeof(str),fp)) == NULL) break;
		if((operation = strdup(str)) == NULL){
			return ERROR_MEMORY_SHORTAGE;
		}
		operation[strcspn(operation,"\n")] = 0;
		if((st = straight_list_insert(operation_list,straight_list_next,(void*)operation))!= TRUE){
			free(operation);
			free(operation_file);
			fclose(fp);
			return st;
		}
	}
	
	free(operation_file);
	free(operation);

	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}

	return OK;
}



int fill_client_list(list_t* client_list, const char* config_file){

	client_t client;
	FILE* fp;
	char str[MAX_STR_LEN]; 
	char *client_file_path, *temp, **fieldv;
	int fieldc,st;


	if(client_list == NULL){
		return ERROR_NULL_POINTER;
	}
	
	if((st = get_file_path(&client_file_path,config_file,CLIENT_PATH_POSITION))!= OK){
		return st;
	}
	
	if((fp = fopen(client_file_path,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(!feof(fp)){

		if((fgets(str,sizeof(str),fp)) == NULL) break;
		if((st = split_csv_string(str,&fieldv,&fieldc))!= OK){ 
			return st;
			fclose(fp);
		}
		client.client_id = (int) strtoul(fieldv[CLIENT_FIELD_ID],&temp,10);
		strncpy(client.name,fieldv[CLIENT_FIELD_NAME],STR_LEN-1);
		strncpy(client.surname,fieldv[CLIENT_FIELD_SURNAME],STR_LEN-1);
		strncpy(client.telephone,fieldv[CLIENT_FIELD_PHONE],STR_LEN-1);
		strncpy(client.mail,fieldv[CLIENT_FIELD_MAIL],STR_LEN-1);
		strncpy(client.date,fieldv[CLIENT_FIELD_DATE],STR_LEN-1);
		if((st = straight_list_insert(client_list,straight_list_next,(void*)&client))!= TRUE){
			destroy_string_array(fieldv,fieldc);
			free(fieldv);
			fieldv = NULL;
			fclose(fp);
			return st;
		}
	}

	destroy_string_array(fieldv,fieldc); 
	free(fieldv);
	fieldv = NULL;
	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}
	
	return OK;
}


int get_file_path(char** path, const char* config, int file_pos){

	FILE* fp;
	char str[STR_LEN];
	int i = 0;

	if (config == NULL){
		return ERROR_NULL_POINTER;
	}

	if((fp = fopen(config,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(fgets(str,sizeof(str),fp)!= NULL){
		if(i == file_pos){
			if((*path = strdup(str)) == NULL){
				fclose(fp);
				return ERROR_MEMORY_SHORTAGE;
			}
			(*path)[strcspn(*path,"\n")] = 0; /*le saco el \n al string para poder usar fopen()*/
			fclose(fp);
			return OK;
		} 
		i++;
	}
	fclose(fp);
	return ERROR_MISSING_FILE;
}



int get_all_operations(ADTWS* ws){

	
	char *response,*raw_str,*format_str,*aux;
	modify_string_t modify;
	int st;
	size_t alloc_size;
	

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	if(!strcmp(ADTWS_Op_get_format(ws->operation_t),TYPE_XML)){
		modify = (modify_string_t)strtoxml;
	}else{
		modify = (modify_string_t)strtojason;
	} 
	

	if((raw_str = (char*) malloc(ws->operation_list.size +1)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	if((format_str = (char*) malloc(ws->operation_list.size + FORMAT_CHOP + 1)) == NULL){
		raw_str = NULL;
		free(raw_str);
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if((response = (char*) malloc(INIT_CHOP)) == NULL){
		raw_str = NULL;
		free(raw_str);
		free(format_str);
		return ERROR_MEMORY_SHORTAGE;
	}

	*response = '\0';
		
	alloc_size = INIT_CHOP;
	
	straight_list_move(&ws->operation_list,straight_list_first);

	do{
		straight_list_get(&ws->operation_list,(void*)raw_str);
		
		modify(format_str,raw_str,OPERATION);

		alloc_size += strlen(format_str);
		
		if((response = (char*) realloc(response,alloc_size)) == NULL){
			raw_str = NULL;
			free(raw_str);
			free(format_str);
			return ERROR_MEMORY_SHORTAGE;
		}
		
		strcat(response,format_str);

	}while(straight_list_move(&ws->operation_list,straight_list_next) == TRUE);

	free(raw_str);
	if((st = ADTWS_Op_set_response(&(ws->operation_t),response))!= OK){	
		raw_str = NULL;
		
		free(format_str);
		free(response);
		return st;
	}

	free(response);
	
	free(format_str);
	

	
	return OK;
}



int log_operation(ADTWS ws){

	FILE* fp;
	char* path;
	int st;

	if((st = get_file_path(&path,ws.config_file,LOG_PATH_POSITION))!=OK){
		return st;
	}

	if((fp = fopen(path,"a")) == NULL){
		return ERROR_OPENING_FILE;
	}

	fprintf(fp,"%s;%s;\n%s;\n%s\n",ADTWS_Op_get_operation_time(ws.operation_t),ADTWS_Op_get_operation(ws.operation_t),ADTWS_Op_get_request(ws.operation_t),ADTWS_Op_get_response(ws.operation_t));

	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}

	return OK;
}


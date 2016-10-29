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

	ws->operation_t = op;

	ADTWS_set_config_file(ws);

	if((st = ADT_List_create(&client_list,sizeof(client_t),(list_copy_t)copy_client,(list_destroy_t)destroy_client))!= OK){
		return st;
	}
	
	if((st = fill_client_list(&client_list,ws->config_file))!= OK){
		ADT_List_destroy(&client_list);
		return st;
	}
	
	if((st = ADT_List_create(&operation_list,STR_LEN,(list_copy_t)copy_operation,(list_destroy_t)destroy_operation))!= OK){
		ADT_List_destroy(&client_list);
		return st;
	}


	if((st = fill_operation_list(&operation_list,ws->config_file))!= OK){
		ADT_List_destroy(&client_list);
		ADT_List_destroy(&operation_list);
		return st;
	}

	ADT_Queue_create(&operation_queue,STR_LEN,(queue_copy_t)copy_operation,(queue_destroy_t)destroy_operation);
	

	ws->client_list = client_list;
	ws->operation_list = operation_list;
	ws->execution_queue = operation_queue;

	return OK;			
}



int ADTWS_valid_operation(ADTWS* ws){


	char *str, *response;

	str = strdup(ADTWS_Op_get_operation(ws->operation_t));

	if(ADT_List_search(&ws->operation_list,(void*)str,(list_compare_t)compare_operation)){
		return ERROR_INVALID_OPERATION;
	}

	response = (char*) malloc(20);

	strtoxml(response,MSG_TRUE,VALID);

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
		if((st = ADT_List_insert_node(operation_list,mov_next,(void*)operation))!= OK){
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
		if((st = ADT_List_insert_node(client_list,mov_next,(void*)&client))!= OK){
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

	
	char *response,*str,*xml_str,*format;
	modify_string_t modify;
	int st;
	size_t alloc_size;
	char *str1;

	

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}

	format = strdup(ADTWS_Op_get_format(ws->operation_t));
	
	if(!strcmp(format,TYPE_XML)){
		modify = (modify_string_t)strtoxml;
	}else{
		modify = (modify_string_t)strtojason;
	} 

	/*if((str = (char*) malloc(30)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	
	if((xml_str = (char*) malloc(strlen(str)+FORMAT_CHOP)) == NULL){
		free(str);
		return ERROR_MEMORY_SHORTAGE;
	}

	if((response = (char*) malloc(INIT_CHOP)) == NULL){
		free(str);
		free(xml_str);
		return ERROR_MEMORY_SHORTAGE;
	}

	move_current(&ws->operation_list,mov_first);
	
	alloc_size = INIT_CHOP;

	do{
		if((st = ADT_List_get_node(&ws->operation_list,(void*)str))!= OK){
			free(str);
			free(xml_str);
			free(response);
			return st;
		}
		modify(xml_str,str,OPERATION);
		alloc_size += strlen(xml_str);
		
		if((response = (char*) realloc(response,alloc_size)) == NULL){
			free(str);
			free(xml_str);
			free(response);
			return ERROR_MEMORY_SHORTAGE; 
		}
		strcat(response,xml_str);	
	}while(move_current(&ws->operation_list,mov_next) == OK);

	if((st = ADTWS_Op_set_response(&ws->operation_t,response))!= OK){
		free(str);
		free(xml_str);
		free(response);
		return st;
	}

	free(str);
	free(xml_str);
	printf("ok?\n");
	return OK;
}*/
	str = (char*) malloc(30);

    xml_str = (char*) malloc(strlen(str)+FORMAT_CHOP+strlen(OPERATION));

    response = (char*) malloc(INIT_CHOP);

    move_current(&ws->operation_list,mov_first);
   
    alloc_size = INIT_CHOP;

    do{
        ADT_List_get_node(&ws->operation_list,(void*)str);
        modify(xml_str,str,OPERATION);
        alloc_size += strlen(xml_str);
        printf("ok\n");
        response = (char*) realloc(response,alloc_size);
        strcat(response,xml_str);   
    }while(move_current(&ws->operation_list,mov_next) == OK);

    ADTWS_Op_set_response(&ws->operation_t,response);

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


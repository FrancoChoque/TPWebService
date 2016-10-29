#include "ADTWS_Op.h"

int parse_url(const char*, char**);
int parse_format_header(const char*, char**);




int ADTWS_Op_create(ADTWS_Op* op, int argc, const char** argv){

	int i, st;

	if(argv == NULL || op == NULL){
		return ERROR_NULL_POINTER;
	}


	if((st = ADTWS_Op_set_request(op,argc,argv))!= OK){
		return st;
	}	
	
	if((st = ADTWS_Op_set_operation(op))!= OK){
		return st;
	}

	if((st = ADTWS_Op_set_format(op,argc,argv))!= OK){
		return st;
	}	

	if((st = ADTWS_Op_set_operation_time(op))!= OK){
		return st;
	}


	return OK; 

}





int ADTWS_Op_destroy(ADTWS_Op* op){

	
	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	if(op->request != NULL){
		free(request);
		op->request = NULL;
	}

	if(op->reponse != NULL){
		free(response);
		op->response = NULL;
	}

	if(op->operation != NULL){
		free(operation);
		op->operation = NULL;
	}

	if(op->operation_time != NULL){
		free(operation_time);
		op->operation_time = NULL;
	}

	if(op->format != NULL){
		free(format);
		op->format = NULL;
	}

	return OK;
}


/*esta función copia en el campo request del ADT Web Service Operation todos los argv.
concat_args() está en la biblioteca utils*/

int ADTWS_Op_set_request(ADTWS_Op* op, int arr_len, const char** arr){

	int st;
	char* request;

	
	if(op == NULL || arr == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = concat_args(arr_len,arr,op->request))!= OK){
		return st;
	}
	
	return OK;

}


int ADTWS_Op_set_operation(ADTWS_Op* op){

	int st, i;
	char* url;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}
	/*Acá falta el algoritmo que agarra el campo request del ADTWS_Op
	y copia el url (https://...etc) en el char* url */

	if((st = parse_url(url,&op->operation,REQUEST_FIELD_OPERATION))!= OK){
		return st;
	}

	return OK;



}



int ADTWS_Op_set_format(ADTWS_Op* op){

	int i, st;
	char* str;

	if(op == NULL || request == NULL){
		return ERROR_NULL_POINTER;
	}

	parse_request(str,FORMAT_FLAG);
	
	if((st = parse_url(str,&op->format,FIELD_METHOD_FORMAT))!= OK){
		return st;
	}

	return OK;
}




int ADTWS_Op_set_operation_time(ADTWS_Op* op){

	int st;
	char* current_time;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}	
	
	if((st = get_time(current_time))!=OK){ /*get_time todavía no existe*/
		return st;
	}

	if ((op->operation_time = strdup(current_time)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}	



int ADTWS_Op_set_response(ADTWS_Op* op, char* str){

	if(op == NULL || str == NULL){
		return ERROR_NULL_POINTER;
	}

	op->response = str;

	return OK;
}


char* ADTWS_Op_get_operation(ADTWS_Op op){

	return op.operation;
}

char* ADTWS_Op_get_format(ADTWS_Op op){

	return op.format;
}

char* ADTWS_Op_get_response(ADTWS_Op op){

	return op.response;
}




int ADTWS_Op_get_data(ADTWS_Op op,){

   	char* str = strdup(strstr(op.response, REQUEST_FLAG_DATA));

   	return str;
}

char* ADTWS_Op_get_url(ADTWS_Op op){


}

/*esta función copia en str lo que haya en el campo de la url especificado por field
por ej: le paso "https://algodetp.com/getTime" y field = 3 y copia "getTime" en str
le paso "https://algodetp.com/getClientbyID/1" y field = 4 y copia "1" en str
*/

int parse_url(const char* url, char** str, int field){

	
	char *aux,*aux2,*temp;
	int i;
	char delims[] = {URL_DELIM,'\0'}; 


	if(url == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((temp = strdup(url)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	for(aux = url, i = 0; i < field && (aux2 = strtok(aux,delims))!= NULL; aux = NULL, i++);

	if((*str = strdup(aux2)) == NULL){
		free(temp);
		temp = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}

	free(temp);
	temp = NULL;	
	
	return OK;
}



int parse_request(const char* request, char** str, char* flag){

	
	char *aux,*aux2,*temp;
	int i;
	char delims[] = {' ','\0'}; 


	if(url == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((temp = strdup(url)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	for(aux = url, i = 0; (aux2 = strtok(aux,delims))!= NULL; aux = NULL, i++){
		;

	if((*str = strdup(aux2)) == NULL){
		free(temp);
		temp = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}

	free(temp);
	temp = NULL;	
	
	return OK;
}




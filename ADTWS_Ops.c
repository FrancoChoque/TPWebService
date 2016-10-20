#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ADTWS_Ops.h"



int ADTWS_Ops_create(int argc, const char** argv, ADTWS_Ops* op){

	unsigned int i;
	int st;

	if(argv == NULL || op == NULL){
		return ERROR_NULL_POINTER;
	}


	if((st = ADTWS_Ops_get_request(op,argc,argv))!= OK){
		return st;
	}	
	
	if((st = ADTWS_Ops_get_operation(op))!= OK){
		return st;
	}

	if((st = ADTWS_Ops_get_format(op,argc,argv))!= OK){
		return st;
	}	

	if((st = ADTWS_Ops_get_operation_time(op))!= OK){
		return st;
	}


	return OK; 

}



/*esta función copia en el campo request del ADT Web Service Operation todos los argv
concat_args() está en la biblioteca utils*/

int ADTWS_Ops_get_request(ADTWS_Ops* op, int arr_len, const char** arr){

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


int ADTWS_Ops_get_operation(ADTWS_Ops* op){

	int st;
	unsigned int i;
	char* url;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}
	/*Acá falta el algoritmo que agarra el campo request del ADTWS_Ops
	y copia el url (https://...etc) en el char* url*/

	if((st = parse_url(url,op->operation))!= OK){
		return st;
	}

	return OK;



}

/*esta función copia en op_name el nombre de la operación que está en argv
por ej: le paso "https://algodetp.com/getTime" y copia "getTime" en op_name
le paso "https://algodetp.com/getClientbyID/1" y copia "getClientbyID" en op_name
Pueden probar esta función con test_url_parser.c */
int parse_url(const char* url, char* op_name){

	
	char* aux;
	char* aux2;
	unsigned int i;
	char delims[] = {URL_DELIM,'\0'}; /*URL_DELIM vendria a ser el slash (/),*/


	if(url == NULL || op_name == NULL){
		return ERROR_NULL_POINTER;
	}	

	for(aux = url, i = 0; i < 3 && (aux2 = strtok(q,delims))!= NULL; aux = NULL, i++);

	if((op_name = strdup(aux2)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}	
	
	return OK;

}



int ADTWS_Ops_get_format(ADTWS_Ops* op, int len, const char** request){

	unsigned int i;

	if(op == NULL || request == NULL){
		return ERROR_NULL_POINTER;
	}

	for(i = 0; i < len; i++){
		if(!strcmp(request[i],FORMAT_FLAG)){ /*FORMAT FLAG es el -X*/
			if((op->format = strdup(request[i+1])) == NULL){
				return ERROR_MEMORY_SHORTAGE;
			}
			return OK; 
		}	
	}

	if((op->format = strdup(DEFAULT_FORMAT)) == NULL){ /*DEFAULT_FORMAT es GET*/
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}



/*get_time() está en la biblioteca sys_time*/

int ADTWS_Ops_get_operation_time(ADTWS_Ops* op){

	int st;
	char* current_time;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}	
	
	if((st = get_time(current_time))!=OK){
		return st;
	}

	if ((op->operation_time = strdup(current_time)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}	



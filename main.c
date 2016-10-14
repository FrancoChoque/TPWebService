#include <stdio.h>
#include <stdlib.h>
#include "ADTWS_Ops_h"
#include "ADTWS_h"
#include "errors.h"





int main(int argc, char* argv[]){

	int st;

	ADTWS_Ops* operation;
	ADTWS* web_service;

	
	if((st = validate_arguments(argc,argv))!= OK){
		log_error(st);
		show_usage();
		return EXIT_FAILURE;
	}

	if((st = ADTWS_create(web_service))!= OK){
		log_error(st);
		return EXIT_FAILURE;
	}

	if((st = ADTWS_Ops_create(argc,argv,operation))!= OK){
		ADTWS_destroy(web_service);
		log_error(st);
		return EXIT_FAILURE;
	}

	if((st = execute_operation(operation,web_service))!= OK){
		log_error(st);
		ADTWS_destroy(web_service);
		ADTWS_Ops_destroy(operation);
		return EXIT_FAILURE;
	}

	ADTWS_destroy(web_service);
	ADTWS_Ops_destroy(operation);

	return OK;
}




int validate_arguments(int argc, char** argv){

	if(argv == NULL){
		return ERROR_NULL_POINTER;
	}

	if(argc < MIN_ARGS){
		return INVALID_ARGUMENTS;
	}

	return OK;
}



int execute_operation(ADTWS* web_service, ADTWS_Ops* operation){

	if(web_service == NULL || operation == NULL){
		return ERROR_NULL_POINTER;
	}


	return OK;
}



/*Estas funciones que son genéricas las pondría en una biblioteca aparte tipo utils.h (utilities) o algo así*/


char* strdup(char* s){ /*Copia string*/

	char* d;

	if((d = (char*) malloc (strlen(s)+1)) == NULL){
		return NULL;
	}

	strcpy(d,s);

	return d;
}





int concat_str_array(int len, char** arr, char* dest){ /*devuelve por dest el request del ADTWS_Ops*/

	
	char* aux;
	unsigned int i;


	if(arr == NULL){
		return ERROR_NULL_POINTER;
	}

	if((dest = (char*) malloc (INIT_CHOP)) == NULL){ 
		return ERROR_MEMORY_SHORTAGE;
	}

	for (i = 0; i < len; i++){
		if((aux = (char*) malloc (strlen(arr[i])+1)) == NULL){
			return ERROR_MEMORY_SHORTAGE;
		}	
		strcpy(aux,arr[i]);
		if((dest = (char*) realloc (dest,strlen(dest)+strlen(aux)+1)) == NULL){
			return ERROR_MEMORY_SHORTAGE;
		}
		strcat(dest,aux);	
		strcat(dest," ");
	}

	
	return OK;
}
#include "main.h"

void log_error(int);
void show_usage(void);
extern const char* error_msg[];

int main(int argc, char* argv[]){

	int st;

	ADTWS_Op operation;
	ADTWS web_service;

	

	if((st = validate_arguments(argc,argv))!= OK){
		log_error(st);
		show_usage();
		return EXIT_FAILURE;
	}

	if((st = ADTWS_Op_create(&operation,argc,(const char**)argv))!= OK){		
		log_error(st);
		return EXIT_FAILURE;
	}
	
	if((st = ADTWS_create(&web_service,operation))!= OK){
		log_error(st);
		ADTWS_Op_destroy(&operation);
		return EXIT_FAILURE;
	}
	
	ADTWS_Op_destroy(&operation);
	
	if((st = execute_operation(&web_service))!= OK){
		log_error(st);
		ADTWS_destroy(&web_service);
		return EXIT_FAILURE;
	}

	ADTWS_destroy(&web_service);
	
	return OK;
}




int validate_arguments(int argc, char** argv){

	if(argv == NULL){
		return ERROR_NULL_POINTER;
	}

	if(argc < MIN_ARGS){
		return ERROR_INVALID_ARGUMENTS;
	}

	return OK;
}



int execute_operation(ADTWS* ws){

	int st;	

	if(ws == NULL){
		return ERROR_NULL_POINTER;
	}
	
	if((st = ADTWS_valid_operation(ws))!= OK){
		return st;
	}

	if((st = ADTWS_consume(ws))!= OK){
		return st;
	}
	
	log_operation(*ws);
	
	return OK;
}



void log_error(int st){

	fprintf(stderr,"%s\n",error_msg[st]);
	
	return;
}

void show_usage(void){

	fprintf(stderr, "Usage: ./tp -X <METHOD> -H <TYPE> <URL> -d <DATA>\n");

	return;
}
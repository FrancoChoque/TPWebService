#include "main.h"




int main(int argc, char* argv[]){

	int st;

	ADTWS_Op operation;
	ADTWS web_service;

	
	if((st = validate_arguments(argc,argv))!= OK){
		log_error(st);
		show_usage();
		return EXIT_FAILURE;
	}

	if((st = ADTWS_Op_create(operation,argc,argv))!= OK){		
		log_error(st);
		return EXIT_FAILURE;
	}

	if((st = ADTWS_create(web_service))!= OK){
		log_error(st);
		ADTWS_Op_destroy(operation);
		return EXIT_FAILURE;
	}

	if((st = execute_operation(operation))!= OK){
		log_error(st);
		ADTWS_Op_destroy(operation);
		ADTWS_destroy(web_service);
		return EXIT_FAILURE;
	}

	ADTWS_destroy(web_service);
	ADTWS_Op_destroy(operation);

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



int execute_operation(ADTWS* ws){

	FILE* config_file;
	

	if(web_service == NULL || operation == NULL){
		return ERROR_NULL_POINTER;
	}


	if((st = ADTWS_consume(operation))!= OK){
		log_operation(ws->operation_t);
		return INVALID_OPERATION
	}

	log_operation(ws->operation_t);

	return OK;
}


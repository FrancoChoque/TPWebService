#include "main.h"


int main(int argc, char* argv[]){

	int st;

	ADTWS_Op* operation;
	ADTWS* web_service;

	
	if((st = validate_arguments(argc,argv))!= OK){
		log_error(st);
		show_usage();
		return EXIT_FAILURE;
	}

	
	if((st = ADTWS_Op_create(argc,argv,operation))!= OK){		
		log_error(st);
		return EXIT_FAILURE;
	}

	if((st = ADTWS_create(web_service))!= OK){
		log_error(st);
		ADTWS_Op_destroy(operation);
		return EXIT_FAILURE;
	}

	if((st = execute_operation(operation,web_service))!= OK){
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



int execute_operation(ADTWS* web_service, ADTWS_Op* operation){

	if(web_service == NULL || operation == NULL){
		return ERROR_NULL_POINTER;
	}

	ADTWS_consume(operation,web_service);
	


	return OK;
}

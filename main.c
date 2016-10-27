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

	if((st = set_file_paths(ADTWS_Ops_get_url(operation)))!= OK){
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
		log_operation(msg_error[st]);
		return FAILED_OPERATION;
	}

	log_operation(ws->operation_t);

	return OK;
}


int set_file_paths(char* url){

	FILE* fp;
	char *temp;
	int i;

	if (url == NULL){
		return ERROR_NULL_POINTER;
	}

	parse_request(url,&temp,REQUEST_FIELD_DOMAIN);

	config_file = strtok(temp,':');

	strcat(config_file,".conf");

	fp = fopen(config_file,"rt");

	for(i = 0; !feof(fp); i++){
		if(fgets(str,sizeof(str),fp) == NULL) break;
		file_paths[i] = strdup(str);
	}

	return OK;


}

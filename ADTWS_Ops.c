#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTWS_Ops.h"



int ADTWS_Ops_create(int argc, char** argv, ADTWS_Ops* op){

	unsigned int i;
	int st;

	if(argv == NULL || op == NULL){
		return ERROR_NULL_POINTER;
	}


	if((st = ADTWS_Ops_set_request(op,argv,argc))!= OK){
		return st;
	}	
	



	return OK; 

}


int ADTWS_Ops_set_request(AOTWS_Ops* op,char** arr,int arr_size){

	int st;
	char* request;

	
	if(op == NULL || arr == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = concat_args(argc,argv,request))!= OK){
		return st;
	}
	
	if((op->request = (char*) malloc(strlen(request)+1)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	strcpy(op->request,request);


	return OK;

}


int ADTWS_Ops_get_operation(AOTWS_Ops* Op){

	unsigned int i;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	for(i = 0; i < strlen(op->request); i++){

		if(op->request[i])
	}



}

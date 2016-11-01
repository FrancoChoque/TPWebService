#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"


#define OPERATION "OPERATION"


void strtoxml(char*, const char*, const char*);

char* arr[] = {
	"get_time",
	"get_max_id_client",
	"set_max_id_client",
	"get_client_by_id",
	"set_client_by_id",
	"get_all_clients",
	"get_all_operations",
	"validate_operation"
};






int main(void){

	
	char *response,*str,*aux;
	
	int st,i;
	size_t alloc_size;
	i = 0;
	

	str = (char*) malloc(40);

	
	aux = (char*) malloc(80);



	response = (char*) malloc(1);

	
	
	alloc_size = INIT_CHOP;


	do{
		strcpy(str,arr[i]);
		strtoxml(aux,str,OPERATION);
		alloc_size += strlen(aux);
		response = (char*) realloc(response,alloc_size);
		strcat(response,aux);
		i++;	
	}while(i<8);

	
	
	free(str);
	
	printf("%s\n",response);
	
	return OK;
}


void strtoxml(char* dest, const char* str, const char* xml_camp){
		
	
	sprintf(dest,"<%s>%s</%s>",xml_camp,str,xml_camp);
	
	return;
}
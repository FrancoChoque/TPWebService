#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"


char* strdup(char* s){ /*Copia string*/

	char* d;

	if((d = (char*) malloc (strlen(s)+1)) == NULL){
		return NULL;
	}

	strcpy(d,s);

	return d;
}





int concat_str_array(int len, char** arr, char* dest){ /*Copia en un string dest, el arreglo de strings arr.
				 										En este caso, el request del ADTWS_Ops*/

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
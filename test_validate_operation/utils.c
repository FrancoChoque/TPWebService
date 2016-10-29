#include "utils.h"


char* strdup(const char* s){ /*Copia string*/

	char* d;

	if((d = (char*) malloc (strlen(s)+1)) == NULL){
		return NULL;
	}

	strcpy(d,s);

	return d;
}




/*copia un arreglo de strings en un solo string*/
int concat_str_array(int len, const char** arr, char** dest){ 

	unsigned int i;


	if(arr == NULL){
		return ERROR_NULL_POINTER;
	}

	if((*dest = (char*) malloc (INIT_CHOP)) == NULL){ 
		return ERROR_MEMORY_SHORTAGE;
	}

	for (i = 0; i < len; i++){
			
		if((*dest = (char*) realloc (*dest,strlen(*dest)+strlen(arr[i])+1)) == NULL){
			return ERROR_MEMORY_SHORTAGE;
		}
		strcat(*dest,arr[i]);	
		strcat(*dest," ");
	}
	
	return OK;
}


/*agarra un string de un csv y reparte los campos en un arreglo de strings
ej: recibe 2;JUANA;GOMEZ;5555-5555;juana@gomez.com.ar;16/09/2016 10:24:53
devuelve fieldv[0] = 2 fieldv[1] = JUANA fieldv[2] = GOMEZ ...etc */

int split_csv_string(char* str, char*** fieldv, int* fieldc){ 

	char *p, *q;
	int i;
	char dels[] = {CSV_DELIM, '\0'};

	
	if(str == NULL || fieldv == NULL || fieldc == NULL){
		return ERROR_NULL_POINTER;
	}

	(*fieldc) = 0;
	
	for(i = 0; str[i]!= '\0'; i++){
		if(str[i] == CSV_DELIM){
			(*fieldc)++;
		}
	}
	
	(*fieldc)++;

	if(((*fieldv) = (char**) malloc ((*fieldc) * sizeof(char*))) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	for(q = str, i = 0; (p = strtok(q,dels))!= NULL; q = NULL, i++){
		if(((*fieldv)[i] = strdup(p)) == NULL){
			destroy_string_array(*fieldv,i);
			free(*fieldv);
			(*fieldv) = NULL;
			return ERROR_MEMORY_SHORTAGE;
		}
	}

	return OK;
}



void destroy_string_array(char** arr, int len){ /*destruye un arreglo de strings*/

	int i;

	if(arr == NULL){
		return;
	}

	for(i = 0; i < len; i++){
		free(arr[i]);
		arr[i] = NULL;
	}

	return;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strdup(const char*);


int main(void){

	char request[400] = "tpws -X POST -H Content-Type:application/xml http:/SERVERTP1GRUPAL:8888/setClientById/ -d <?xmlversion=1.0encoding=UTF-8?>​<Cliente><id>​1</id><Nombre>​JUAN​</Nombre><Apellido>​PEREZ​</Apellido><Telefono>4444-4444</Telefono><Mail>juan@perez.com.ar</Mail><Time>19/09/2016 19:04:33</Time></Cliente>";

	char *aux,*aux2,*temp;
	int i;
	char delims[] = {' ','\0'}; 



	for(aux = request, i = 0; (strcmp(aux2,"-H")) && (aux2 = strtok(aux,delims))!= NULL; aux = NULL, i++);

	aux2 = strtok(aux,delims);
	aux = NULL;

	aux2 = strtok(aux,delims);
	aux = NULL;
	
	
	printf("%s\n",aux2);	
	
	return 0;
}



char* strdup(const char* s){

	char* d;

	if((d = (char*) malloc (strlen(s)+1)) == NULL){
		return NULL;
	}

	strcpy(d,s);

	return d;
}


/*int parse_url(const char* url, char** str, int field){

	
	char *aux,*aux2,*temp;
	int i;
	char delims[] = {URL_DELIM,'\0'}; 


	if(url == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((temp = strdup(url)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	for(aux = url, i = 0; i < field && (aux2 = strtok(aux,delims))!= NULL; aux = NULL, i++);

	if((*str = strdup(aux2)) == NULL){
		free(temp);
		temp = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}

	free(temp);
	temp = NULL;	
	
	return OK;
}
*/
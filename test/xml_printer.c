#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OPERATION "operation"
#define STR_LEN 40
#define XML_STR_CHOP 20

void operation_to_xml(char*, const char*);
char* strdup(const char*);


char* op[] ={
	"get_client",
	"set_client",
	"kill_client",
	"birth_client",
	"get_time",
	"stop_time"
};


int main (void){
	
	char *aux,*aux2,*str;
	int i;

	aux = (char*) malloc(STR_LEN);
	aux2 = (char*) malloc(STR_LEN+XML_STR_CHOP);
	str = (char*) malloc(1);
	
	do{
		aux = strdup(op[i]);
		operation_to_xml(aux2,aux);
		str = (char*) realloc(str,strlen(str)+strlen(aux2));
		strcat(str,aux2);
		i++;	
	}while(i<6);

	free(aux2);

	printf("%s\n",str);
}




void operation_to_xml(char* dest, const char* str){
	

	sprintf(dest,"<%s>%s</%s>",OPERATION,str,OPERATION);
	

	return;
}


char* strdup(const char*s){

	char* d;

	d = (char*) malloc(strlen(s)+1);

	strcpy(d,s);

	return d;
}
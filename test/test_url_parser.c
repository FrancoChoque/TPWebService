#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_url(const char*, char**);

char* strdup(const char*);

int main (void){

	char str[] = "https://algodetp.com/getClientbyID/1";
	char* s;

	parse_url(str,&s);

	
	printf("%s\n", s);

	return 0;
}



char* strdup (const char* s){

	char*d;

	d = (char*) malloc(strlen(s)+1);

	strcpy(d,s);

	return d;

}





int parse_url(const char* url, char** op_name){

	
	char* aux;
	char* aux2;
	unsigned int i;
	char delims[] = {'/','\0'}; 
	char* temp;

	temp = strdup(url);


	for(aux = temp, i = 0; i < 3 && (aux2 = strtok(aux,delims))!= NULL; aux = NULL, i++);

	*op_name = strdup(aux2);
	
	return 0;

}
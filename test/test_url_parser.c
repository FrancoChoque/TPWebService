#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* strdup(const char*);

int main (void){


	char* q;
	char* p;
	char* s;
	char** values;
	int i;

	

	char str[] = "https://kapa.com/kapita/s";

	s = (char*) malloc (sizeof(strlen(str))+1);
	strcpy(s,str);

	char delims[] = {'/','\0'};

	for(q = s, i = 0; i < 3 && (p = strtok(q,delims))!= NULL; q = NULL, i++);

	strcpy(s,p);
	
	printf("%s\n", s);

	return 0;
}



char* strdup (const char* s){

	char*d;

	d = (char*) malloc(strlen(s)+1);

	strcpy(d,s);

	return d;

}
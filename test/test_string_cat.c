#include <stdio.h>
#include <string.h>
#include <stdlib.h>

	

int main(int argc, char* argv[]){


	char* d;
	char* aux;

	int i;

	d = (char*) malloc (INIT_CHOP);

	for (i = 0; i < argc; i++){
		aux = (char*) malloc (1+strlen(argv[i]));
		strcpy(aux,argv[i]);
		d = (char*) realloc (d,strlen(d)+strlen(aux)+1);
		strcat(d,aux);	
		strcat(d," ");

	}

	printf("%s\n",d);

	return 0;

}
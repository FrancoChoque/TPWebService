#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FIELD_PATH_CLIENT 0
#define FIELD_PATH_OPERATION 1
#define FIELD_PATH_LOG 2


typedef struct{
	char* csv_file;
	char* op_file;
	char* log_file;
}file_paths;

char* strdup(const char*);


int main (void){


	FILE* fp;
	char str[20];
	int i = 0;
	file_paths path;

	fp = fopen("file","rt");

	while(!feof(fp)){

		fgets(str,20,fp);
		if(i == FIELD_PATH_CLIENT) path.csv_file = strdup(str);
		if(i == FIELD_PATH_OPERATION) path.op_file = strdup(str);
		if(i == FIELD_PATH_LOG) path.log_file = strdup(str);
		i++;
	}

	printf("%s\n%s\n%s\n",path.csv_file,path.op_file,path.log_file);

	return 0;
}


char* strdup(const char* s){

	char* d;

	d = (char*) malloc (strlen(s)+1);
	strcpy(d,s);

	return d;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIELD_CLIENT_ID 0
#define FIELD_CLIENT_NAME 1
#define FIELD_CLIENT_SURNAME 2
#define FIELD_CLIENT_PHONE 3
#define FIELD_CLIENT_MAIL 4
#define FIELD_CLIENT_DATE 5
#define STR_LEN 20
#define DELIM ';'


char* strdup (const char*);
int split(char*, char***, int*);


typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;

void print_client(client_t*);

int main(void){

		FILE* fp;
		client_t client;
		char str[STR_LEN * 7];
		char *temp, **fieldv;
		int fieldc;


		fp = fopen("csv","rt");

		printf("%d\n",(int)strlen(str));

		while(!feof(fp)){

			if((fgets(str,STR_LEN*7	,fp)) == NULL) break;
			split(str,&fieldv,&fieldc);
			client.client_id = (int) strtoul(fieldv[FIELD_CLIENT_ID],&temp,10);
			strcpy(client.name,fieldv[FIELD_CLIENT_NAME]);
			strcpy(client.surname,fieldv[FIELD_CLIENT_SURNAME]);
			strcpy(client.telephone,fieldv[FIELD_CLIENT_PHONE]);
			strcpy(client.mail,fieldv[FIELD_CLIENT_MAIL]);
			strcpy(client.date,fieldv[FIELD_CLIENT_DATE]);
			print_client(&client);
		}
	
	return 0;
}


int split(char* str, char*** fieldv, int* fieldc){

	char *p, *q;
	int i;
	char dels[] = {DELIM, '\0'};

	
	(*fieldc) = 0;
	
	for(i = 0; str[i]!= '\0'; i++){
		if(str[i] == DELIM){
			(*fieldc)++;
		}
	}
	
	(*fieldc)++;

	(*fieldv) = (char**) malloc ((*fieldc) * sizeof(char*));

	for(q = str, i = 0; (p = strtok(q,dels))!= NULL; q = NULL, i++){
		(*fieldv)[i] = strdup(p);
		
	}

	return 0;

}


char* strdup (const char* src){

	char* dest;

	dest = (char*) malloc (strlen(src)+1);

	strcpy(dest,src);

	return dest;
}


void print_client (client_t* client){

	printf("%d\n%s\n%s\n%s\n%s\n%s\n", client->client_id,client->name,client->surname,client->telephone,client->mail,client->date);
	return;
}
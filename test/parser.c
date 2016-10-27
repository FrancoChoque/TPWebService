#include <stdio.h>
#include <stdlib.h>


#define STR_LEN 20

typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}client_t;

int parse_jason(client_t*, const char*);

int main(void){


	client_t client;

	char jason[] = '{"id":"1","Nombre":"JUAN" ,"Apellido": "PEREZ","Telefono":
    "4444-4444","Mail": "juan@perez.com.ar", "Time": "19/09/2016 19:04:33"}'

	parse_jason(&client_t,jason);

	printf("%d\n",client.client_id);
	printf("%s\n",client.name);
	printf("%s\n",client.surname);
	printf("%s\n",client.mail|);
	printf("%s\n",client.date);

	return 0;;

}
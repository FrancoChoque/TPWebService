#include "ADT_Client.h"



int copy_client(void* dest, const void* source){


	client_t *d, *s;

	if(dest == NULL || source == NULL){
		return ERROR_NULL_POINTER;
	}

	d = (client_t*) dest;
	s = (client_t*) source;
	d->client_id = s->client_id;
	
	strncpy(d->name, s->name, STR_LEN-1);
	strncpy(d->surname, s->surname, STR_LEN-1);
	strncpy(d->telephone, s->telephone, STR_LEN-1);
	strncpy(d->mail, s->mail, STR_LEN-1);
	strncpy(d->date, s->date, STR_LEN-1);

	return OK;
}


void destroy_client(void* data){

	return ;
}

int compare_client(const void* a, const void* b){

	client_t *client_a, *client_b;

	client_a = (client_t*) a;
	client_b = (client_t*) b;

	return (client_a->client_id - client_b->client_id);
}


char* print_client_as_xml(client_t client){

	char* str;

	if((str = (char*) malloc (MAX_STR_LEN)) == NULL){
		return NULL;
	}

	sprintf(str,"<%s><Client><%s>%d</%s><%s>%s</%s><%s>%s</%s><%s>%s</%s><%s>%s</%s><%s>%s</%s></Client>",
		XML_VERSION,CLIENT_ID,client.client_id,CLIENT_ID,CLIENT_NAME,client.name,
		CLIENT_NAME,CLIENT_SURNAME,client.surname,CLIENT_SURNAME,
		CLIENT_TELEPHONE,client.telephone,CLIENT_TELEPHONE,
		CLIENT_MAIL,client.mail,CLIENT_MAIL,CLIENT_DATE,client.date,CLIENT_DATE);
	
	return str;
}


char* print_client_as_jason(client_t client){

	
	char* str;

	if((str = (char*) malloc (MAX_STR_LEN)) == NULL){
		return NULL;
	}

	sprintf(str,"{\"%s\":\"%d\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\",\"%s\":\"%s\"}",
		CLIENT_ID,client.client_id,CLIENT_NAME,client.name,
		CLIENT_SURNAME,client.surname,CLIENT_TELEPHONE,client.telephone,
		CLIENT_MAIL,client.mail,CLIENT_DATE,client.date);

	
	return str;
}


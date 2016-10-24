#include "ADT_Client.h"

int copy_client(void* dest, const void* source){


	if(dest == NULL || source == NULL){
		return ERROR_NULL_POINTER;
	}

	client_t *d, *s;
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


void print_client_as_xml(const void* c, FILE* fp){

	client_t* client;
	char str[MAX_STR_LEN];

	client = (client_t*) c;

	if(client == NULL) return;

	sprintf(str,"<Client><%s>%s</%s><%s>%s</%s><%s>%s</%s><%s>%s</%s><%s>%s</%s><%s>%s</%s></Client>\n"
		CLIENT_ID,client->id,CLIENT_ID,CLIENT_NAME,client->name,
		CLIENT_NAME,CLIENT_SURNAME,client->surname,CLIENT_SURNAME,
		CLIENT_TELEPHONE,client->telephone,CLIENT_TELEPHONE,
		CLIENT_MAIL,client->mail,CLIENT_MAIL,CLIENT_DATE,client->date,CLIENT_DATE);
	
	fprintf(fp,"%s\n",str);

	return;
}


void print_client_as_jason(const void* c, FILE* fp){

	client_t* client;
	char str[MAX_STR_LEN];

	client = (client_t*) c;

	if(client == NULL) return;

	sprintf(str,"%s:%d,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s",CLIENT_ID,client->id,CLIENT_NAME,client->name,
		CLIENT_SURNAME,client->surname,CLIENT_TELEPHONE,client->telephone,
		CLIENT_MAIL,client->mail,CLIENT_DATE,client->date)

	fprintf(fp,"%s\n",str);

	return str;
}

#include "ADT_Client.h"

int copy_client(void* dest, const void* source){

	

	if(dest == NULL || source == NULL){
		return 1;
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
	printf("%d\n",client_a->client_id - client_b->client_id);
	return (client_a->client_id - client_b->client_id);
}
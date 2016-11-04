#include "ADT_Client.h"



int copy_client(void* dest, const void* source){


	client_t *d, *s;

	if(dest == NULL || source == NULL){
		return ERROR_NULL_POINTER;
	}

	d = (client_t*) dest;
	s = (client_t*) source;
	
	d->client_id = s->client_id;
	
	if(s->name != NULL){
		strncpy(d->name, s->name, STR_LEN-1);
	}
	if(s->surname != NULL){
		strncpy(d->surname, s->surname, STR_LEN-1);
	}
	if(s->telephone != NULL){
		strncpy(d->telephone, s->telephone, STR_LEN-1);
	}
	if(s->mail != NULL){
		strncpy(d->mail, s->mail, STR_LEN-1);
	}
	if(s->date != NULL){
		strncpy(d->date, s->date, STR_LEN-1);
	}

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



int xmltoclient(const char* xml , void* data){

	client_t* client;
	char *str, *aux, *aux2, *temp;
	char delims[] = {'<','>','/','\0'};
	char delims_date[] = {'<','>','\0'};
	
	client = (client_t*) data;


	if((str = strdup(xml)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	/*saco el <?xml="1.0"encoding...>*/
	aux = str; 	
	aux2 = strtok(aux,delims);
	aux = NULL;
	/*..............................>*/

	while((aux2 = strtok(aux,delims))!= NULL){
		
		if(!strcmp(aux2,CLIENT_ID)){
			aux2 = strtok(aux,delims);
			client->client_id = (int) strtoul(aux2,&temp,10);
			if(strcmp((aux2 = strtok(aux,delims)),CLIENT_ID)){
				free(str);
				return ERROR_INVALID_XML;
			}
			continue;
		}
		if(!strcmp(aux2,CLIENT_NAME)){
			aux2 = strtok(aux,delims);
			strncpy(client->name,aux2,STR_LEN-1);
			if(strcmp((aux2 = strtok(aux,delims)),CLIENT_NAME)){
				free(str);
				return ERROR_INVALID_XML;
			}
			continue;
		}
		
		if(!strcmp(aux2,CLIENT_SURNAME)){
			aux2 = strtok(aux,delims);
			strncpy(client->surname,aux2,STR_LEN-1);
			if(strcmp((aux2 = strtok(aux,delims)),CLIENT_SURNAME)){
				free(str);
				return ERROR_INVALID_XML;
			}
			continue;
		}
		
		if(!strcmp(aux2,CLIENT_TELEPHONE)){
			aux2 = strtok(aux,delims);
			strncpy(client->telephone,aux2,STR_LEN-1);
			if(strcmp((aux2 = strtok(aux,delims)),CLIENT_TELEPHONE)){
				free(str);
				return ERROR_INVALID_XML;
			}
			continue;
		}
		if(!strcmp(aux2,CLIENT_MAIL)){
			aux2 = strtok(aux,delims);
			strncpy(client->mail,aux2,STR_LEN-1);
			if(strcmp((aux2 = strtok(aux,delims)),CLIENT_MAIL)){
				free(str);
				return ERROR_INVALID_XML;
			}
			continue;
		}
		if(!strcmp(aux2,CLIENT_DATE)){
			aux2 = strtok(aux,delims_date);
			strncpy(client->date,aux2,STR_LEN-1);
			if(strcmp((aux2 = strtok(aux,delims)),CLIENT_DATE)){
				free(str);
				return ERROR_INVALID_XML;
			}
			continue;
		}
	}
	
	free(str);

	return OK;
}


int jsontoclient (const char* str, void* data){

    char *json, *aux, *aux2,*temp;
    char delims[] = {'{','}','"',':','\0'};
    client_t* client;

    client = (client_t*) data;

    if((json = strdup(str)) == NULL){
    	return ERROR_MEMORY_SHORTAGE;
    }

    for(aux = json; (aux2 = strtok(aux,delims))!= NULL;){
    	
    	aux = NULL;

        if(!strcmp(aux2,CLIENT_ID)){
            aux2 = strtok(aux,delims);
            client->client_id = (int) strtoul(aux2,&temp,10);
            continue;
        }
        if(!strcmp(aux2,CLIENT_NAME)){
            aux2 = strtok(aux,delims);
            strncpy(client->name,aux2,STR_LEN-1);
            continue;
        }
        if(!strcmp(aux2,CLIENT_SURNAME)){
            aux2 = strtok(aux,delims);
            strncpy(client->surname,aux2,STR_LEN-1);
            continue;
        }
        if(!strcmp(aux2,CLIENT_TELEPHONE)){
            aux2 = strtok(aux,delims);
            strncpy(client->telephone,aux2,STR_LEN-1);
            continue;
        }
        if(!strcmp(aux2,CLIENT_MAIL)){
            aux2 = strtok(aux,delims);
            strncpy(client->mail,aux2,STR_LEN-1);
            continue;
        }
        if(!strcmp(aux2,CLIENT_DATE)){
            aux2 = strtok(aux,delims);
            strncpy(client->date,aux2,STR_LEN-1);
            continue;
        }
    }

    free(json);

    return OK;
}
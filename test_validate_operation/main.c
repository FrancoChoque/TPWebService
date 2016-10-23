#include "main.h"




int main(void){

		
	list_t list;
	int id,st;
	

	id = 4;

	if((st = ADT_List_create(&list,sizeof(client_t),(copy_t)copy_client,(destroy_t)destroy_client))!= OK){
		printf("%d\n",st);
		return 1;
	}


	if((st = fill_list(&list))!= OK){
		return st;
	}
	
	valid_client(&list,id);
		
	



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




int fill_list(list_t* list){


	FILE* fp;
	client_t client;
	char str[MAX_STR_LEN];
	char *temp, **fieldv;
	int fieldc;
	int st;
	
	fp = fopen("csv","rt");

		

	while(!feof(fp)){

		if((fgets(str,sizeof(str),fp)) == NULL) break;
		split(str,&fieldv,&fieldc);
		client.client_id = (int) strtoul(fieldv[FIELD_CLIENT_ID],&temp,10);
		strncpy(client.name,fieldv[FIELD_CLIENT_NAME],STR_LEN-1);
		strncpy(client.surname,fieldv[FIELD_CLIENT_SURNAME],STR_LEN-1);	
		strncpy(client.telephone,fieldv[FIELD_CLIENT_PHONE],STR_LEN-1);
		strncpy(client.mail,fieldv[FIELD_CLIENT_MAIL],STR_LEN-1);
		strncpy(client.date,fieldv[FIELD_CLIENT_DATE],STR_LEN-1);
		
		if((st = ADT_List_insert_node(list,mov_next,(void*)&client))!= OK){
			printf("%d\n", st);
			return st;
		}

	}
	
	
	return 0;


}

int valid_client(list_t* list,int id){

	client_t client;

	client.client_id = id;


	if(search_list((void*)&client,list,(comparator_t)compare_client)){
		return 1;
	}

	return 0;
}


int search_list(void* node, list_t* list,comparator_t compare){


	move_current(list,mov_first);

	do{
		if(!compare(node,list->current->data)){
			printf("yes\n");
			return 0;
		}	 
	}while(move_current(list,mov_next) == OK);

	printf("oh\n");
	return 1;

}
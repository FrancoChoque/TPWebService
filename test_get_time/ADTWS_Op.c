#include "ADTWS_Op.h"
#include <time.h>

int parse_url(char**, const char*, int);
int parse_request(char**, const char*, char*);
void operation_to_xml(char*, const char*);
void operation_to_jason(char*,const char*);
int get_local_time(char**);



int ADTWS_Op_create(ADTWS_Op* op, int argc, const char** argv){

	int st;

	if(argv == NULL || op == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = ADTWS_Op_set_request(op,argc,argv))!= OK){
		return st;
	}	
	
	if((st = ADTWS_Op_set_operation(op))!= OK){
		ADTWS_Op_destroy(op);
		return st;
	}
	
	if((st = ADTWS_Op_set_format(op))!= OK){
		ADTWS_Op_destroy(op);
		return st;
	}	

	if((st = ADTWS_Op_set_operation_time(op))!= OK){
		ADTWS_Op_destroy(op);
		return st;
	}

	op->response = NULL;

	return OK; 

}





int ADTWS_Op_destroy(ADTWS_Op* op){

		
	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	if(op->request != NULL){
		free(op->request);
		op->request = NULL;
	}
	
	if(op->response != NULL){
		free(op->response);
		op->response = NULL;
	}
	
	if(op->operation != NULL){
		free(op->operation);
		op->operation = NULL;
	}
	
	if(op->operation_time != NULL){
		free(op->operation_time);
		op->operation_time = NULL;
	}
	
	if(op->format != NULL){
		free(op->format);
		op->format = NULL;
	}
	
	return OK;
}


/*esta función copia en el campo request del ADT Web Service Operation todos los argv.
concat_args() está en la biblioteca utils*/

int ADTWS_Op_set_request(ADTWS_Op* op, int arr_len, const char** arr){

	int st;
	

	if(op == NULL || arr == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((st = concat_str_array(arr_len,arr,&op->request))!= OK){
		return st;
	}

	return OK;
}



int ADTWS_Op_set_operation(ADTWS_Op* op){

	int st;
	char *url, *str;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = ADTWS_Op_get_url(&url,*op))!= OK){
		return st;
	}
	
	if((st = parse_url(&str,url,URL_FIELD_OPERATION))!= OK){
		free(url);
		return st;
	}

	if((op->operation = strdup(str)) == NULL){
		free(url);
		free(str);
		return ERROR_MEMORY_SHORTAGE;
	}

	free(url);
	free(str);

	return OK;
}



int ADTWS_Op_set_format(ADTWS_Op* op){

	int st;
	char *str,*aux;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = parse_request(&str,op->request,REQUEST_FLAG_CONTENT_TYPE))!= OK){
		return st;
	}
	
	if((aux = strstr(str,TYPE_JASON)) == NULL){
		if((aux = strstr(str,TYPE_XML)) == NULL){
			free(str);
			return ERROR_UNSUPPORTED_CONTENT_TYPE;
		}
		if((op->format = strdup(TYPE_XML)) == NULL){
			free(str);
			return ERROR_MEMORY_SHORTAGE;
		}
		free(str);
		return OK;
	}

	free(str);

	if((op->format = strdup(TYPE_JASON)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}




int ADTWS_Op_set_operation_time(ADTWS_Op* op){

	int st;
	char* current_time;

	if(op == NULL){
		return ERROR_NULL_POINTER;
	}	
	
	if((st = get_local_time(&current_time))!= OK){ 
		return st;
	}

	if ((op->operation_time = strdup(current_time)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	free(current_time);

	return OK;
}	



int ADTWS_Op_set_response(ADTWS_Op* op, char* str){

	if(op == NULL || str == NULL){
		return ERROR_NULL_POINTER;
	}

	if((op->response = strdup(str)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
}


char* ADTWS_Op_get_operation(ADTWS_Op op){

	return op.operation;
}

char* ADTWS_Op_get_operation_time(ADTWS_Op op){

	return op.operation_time;
}


char* ADTWS_Op_get_format(ADTWS_Op op){

	return op.format;
}


char* ADTWS_Op_get_request(ADTWS_Op op){

	return op.request;
}

char* ADTWS_Op_get_response(ADTWS_Op op){

	return op.response;
}



int ADTWS_Op_get_method(char** method, ADTWS_Op op){

	int st;

	if((st = parse_request(method, op.request, REQUEST_FLAG_METHOD))!= OK){
		return st;
	}

	return OK;
}


int ADTWS_Op_get_data(char** data, ADTWS_Op op){

   	char* str;

   	if((str = strstr(op.response, REQUEST_FLAG_DATA)) == NULL){
   		return ERROR_INVALID_DATA;
   	}

   	if((*data = strdup(str)) == NULL){
   		return ERROR_MEMORY_SHORTAGE;
   	}

   	return OK;
}


int ADTWS_Op_get_url(char** url, ADTWS_Op op){



	*url = strdup("http://SERVERTP1GRUPAL:8888/validate_operation/");

	return OK;
}


int ADTWS_Op_get_domain(char** domain, ADTWS_Op op){

	char* aux;
	int st;

	if((st = ADTWS_Op_get_url(&aux,op))!= OK){
		return st;
	}

	if((st = parse_url(domain,aux,URL_FIELD_DOMAIN))!= OK){
		free(aux);
		return st;
	}

	return OK;
}



/*esta función copia en str lo que haya en el campo de la url especificado por field
ej: recibe: "https://algodetp.com:8080/getTime/1" y field = 4
	devuelve: "getTime" en str

	recibe: "https://algodetp.com:8080/getClientbyID/1" y field = 5  
	devuelve: "1" en str
*/

int parse_url(char** str, const char* url, int field){

	
	char *aux,*aux2,*temp;
	int i;
	char delims[] = {URL_DELIM_SLASH,URL_DELIM_COLON,'\0'}; 


	if(url == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((temp = strdup(url)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	for(aux = temp, i = 0; i < field && (aux2 = strtok(aux,delims))!= NULL; aux = NULL, i++);

	if((*str = strdup(aux2)) == NULL){
		free(temp);
		temp = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}

	free(temp);
	temp = NULL;	
	
	return OK;
}




/*Bastante parecida a parse_url pero en vez de un valor fijo, usa flags
ej: recibe: "-X POST -H "Content-Type:application/json/"" y "-H"
	devuelve: "Content-Type:application/jason/" */

int parse_request(char** str, const char* request, char* flag){

	
	char *aux,*aux2,*temp;
	char delims[] = {REQUEST_DELIM,'\0'}; 


	if(request == NULL || flag == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((temp = strdup(request)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	for(aux = temp; ((aux2 = strtok(aux,delims))!= NULL) && (strcmp(aux2,flag)); aux = NULL);
	
	if(strcmp(aux2,flag)){
		return ERROR_NOT_FOUND;
	}

	aux2 = strtok(aux,delims);
	
	aux = NULL;
	
	if((*str = strdup(aux2)) == NULL){
		free(temp);
		aux2 = temp = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}

	free(temp);
	aux2 = temp = NULL;	
	
	return OK;
}



void strtoxml(char* dest, const char* str, const char* xml_camp){
		
	
	sprintf(dest,"<%s>%s</%s>",xml_camp,str,xml_camp);
	
	return;
}


void strtojason(char* dest, const char* str, const char* jason_camp){

	
	sprintf(dest,"{\"%s\": \"%s\"}",jason_camp,str);
	
	return;
}


int get_local_time(char** str_time){

	time_t time_stamp;
	struct tm* display;
	char time_string[STR_LEN], *response;
	


	if(str_time == NULL){
		return ERROR_NULL_POINTER;
	}

	if(time(&time_stamp) == -1){
		return ERROR_SYS_TIME;
	}
	
	if((display = localtime(&time_stamp)) == NULL){
		return ERROR_SYS_TIME;
	}
	
	strftime(time_string,STR_LEN,"%d/%m/%Y %H:%M:%S",display);
	
	*str_time = strdup(time_string);

	return OK;
	
}
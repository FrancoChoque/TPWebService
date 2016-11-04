#include "ADTWS_Op.h"
#include <time.h>


int get_url(char**, const char*);
int parse_url(char**, const char*, int);
int parse_request(char**, const char*, char*);
void operation_to_xml(char*, const char*);
void operation_to_jason(char*,const char*);




int ADTWS_Op_create(ADTWS_Op* op, int argc, const char** argv){

	int st;

	if(argv == NULL || op == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = ADTWS_Op_set_request(op,argc,argv))!= OK){
		return st;
	}	
	
	if((st = ADTWS_Op_set_operation(op))!= OK){
		free(op->request);
		return st;
	}
	
	if((st = ADTWS_Op_set_format(op))!= OK){
		free(op->request);
		free(op->operation);
		return st;
	}	

	if((st = ADTWS_Op_set_operation_time(op))!= OK){
		free(op->request);
		free(op->operation);
		free(op->format);
		return st;
	}

	op->response = '\0';

	return OK; 

}





int ADTWS_Op_destroy(ADTWS_Op* op){

		
	if(op == NULL){
		return ERROR_NULL_POINTER;
	}

	
	if(op->request != '\0'){
		free(op->request);
		op->request = NULL;
	}
	
	if(op->operation_time != '\0'){
		free(op->operation_time);
		op->operation_time = NULL;
	}
	
	if(op->format != '\0'){
		free(op->format);
		op->format = NULL;
	}

	if(op->response != '\0'){
		free(op->response);
		op->response = NULL;
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
	
	if((st = get_url(&url,op->request))!= OK){
		return st;
	}
	
	if((st = parse_url(&str,url,URL_FIELD_OPERATION))!= OK){
		free(url);
		return st;
	}

	if(str == NULL){
		free(url);
		return ERROR_OPERATION_NOT_FOUND;
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

	if(str == NULL){
		return ERROR_CONTENT_TYPE_HEADER_NOT_FOUND;
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
	char* aux;

	if((st = parse_request(&aux,op.request,REQUEST_FLAG_METHOD))!= OK){
   		return st;
   	}
   	
   	if(aux == NULL){	/*Si no encuentra la bandera, el método por defecto es GET*/
   		if((*method = strdup(METHOD_GET)) == NULL){
   			free(aux);
   			return ERROR_MEMORY_SHORTAGE;
   		}
   		return OK;
   	}

   	if((*method = strdup(aux)) == NULL){
   		free(aux);
   		return ERROR_MEMORY_SHORTAGE;
   	}
   	
   	free(aux);

   	return OK;
}




int ADTWS_Op_get_data(char** data, const char* method, ADTWS_Op op){

   	
   	int st;
   	char *aux, *url;
   	


   	if(!strcmp(method,METHOD_GET)){ 
   		   	
   		if((st = get_url(&url,op.request))!= OK){
   			return st;
   		}
		if((st = parse_url(&aux,url,URL_FIELD_GET_DATA))!= OK){
   			free(url);
   			return st;
   		}
		if(aux == NULL){
   			free(url);
   			return ERROR_DATA_NOT_FOUND;
		}
		if((*data = strdup(aux)) == NULL){
   			free(url);
   			return ERROR_MEMORY_SHORTAGE;
   		}
   		free(url);
   		return OK;	
   	} 	

	if(!strcmp(method,METHOD_POST)){
		
		if((st = parse_request(&aux,op.request,"-d"))!= OK){
   			return st;
   		}
   		if(aux == NULL){
   			return ERROR_DATA_NOT_FOUND;
   		}
   		if((*data = strdup(aux)) == NULL){
   			return ERROR_MEMORY_SHORTAGE;
   		}
   		return OK;
   	}
   	
   	return ERROR_INVALID_METHOD;
}



int get_url(char** url, const char* request){

	char *aux2,*temp, *aux;

	
	if((aux2 = strstr(request,"http")) == NULL){
		return ERROR_URL_NOT_FOUND;
	}

	if((temp = strdup(aux2)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	aux2 = NULL;

	aux = strtok(temp," ");

	if((*url = strdup(aux)) == NULL){
		free(temp);
		return ERROR_MEMORY_SHORTAGE;
	}

	free(temp);

	return OK;
}



int ADTWS_Op_get_host(char** host, ADTWS_Op op){

	char* aux;
	int st;

	if((st = get_url(&aux,op.request))!= OK){
		return st;
	}

	if((st = parse_url(host,aux,URL_FIELD_HOST))!= OK){
		free(aux);
		return st;
	}

	if(host == NULL){
		free(aux);
		return ERROR_HOST_NOT_FOUND;
	}

	free(aux);

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

	if(aux2 == NULL){
		*str = NULL;
		free(temp);
		temp = NULL;
		return OK;
	}

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


	if(request == NULL || flag == NULL || str == NULL){
		return ERROR_NULL_POINTER;
	}	

	if((temp = strdup(request)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	for(aux = temp; ((aux2 = strtok(aux,delims))!= NULL) && (strcmp(aux2,flag)); aux = NULL);
	
	if(aux2 == NULL){
		free(temp);
		*str = NULL;
		return OK;
	}

	if((aux2 = strtok(aux,delims)) == NULL){
		free(temp);
		return ERROR_MISSING_DATA;
	}
	
	
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
	char time_string[STR_LEN];
	


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
	
	if((*str_time = strdup(time_string)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	return OK;
	
}





 


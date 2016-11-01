#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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

int main(int argc,char ** argv){

    int st;
    client_t  client;
    if(!(st=parse_jason(&client, argv[argc-1])))
        return 0;
    printf("%d\n",client.client_id);
    printf("%s\n",client.name);
    printf("%s\n",client.surname);
    printf("%s\n",client.mail);
    printf("%s\n",client.date);
    return 1;

}
/*'{"id":"1","Nombre":"JUAN" ,"Apellido": "PEREZ","Telefono": "4444-4444","Mail": "juan@perez.com.ar",
 "Time": "19/09/2016 19:04:33"}'*/
int parse_jason(client_t* cl,const char * json){
	char jason[400],*pointer=NULL,id[2];
	int positionid=0,counter=0;
	strcpy(jason,json);
	pointer=strstr(jason,"\"");
	while(strcmp(jason,"End")){
		switch(pointer[2]){
			case 'd' :
				positionid=strcspn(json,"123456789");
				if(json[positionid+1]!='"'){
				    id[0]=json[positionid];
				    id[1]=json[positionid+1];
				}else id[0]=json[positionid];
				cl->client_id=atoi(id);
				break;
			case 'o':
				pointer=strstr(jason,":");
				strcpy(jason,pointer);
				pointer=strstr(jason,"\"");
				strncpy(cl->name,pointer+1,strcspn(pointer+1,"\""));
				break;
			case 'p':
				pointer=strstr(jason,":");
				strcpy(jason,pointer);
				pointer=strstr(jason,"\"");
				strncpy(cl->surname,pointer+1,strcspn(pointer+1,"\""));
				break;
			case 'e':
				pointer=strstr(jason,":");
				strcpy(jason,pointer);
				pointer=strstr(jason,"\"");
				strncpy(cl->telephone,pointer+1,strcspn(pointer+1,"\""));
				break;
			case 'a':
				pointer=strstr(jason,":");
				strcpy(jason,pointer);
				pointer=strstr(jason,"\"");
				strncpy(cl->mail,pointer+1,strcspn(pointer+1,"\""));
				break;
			case 'i':
				pointer=strstr(jason,":");
				strcpy(jason,pointer);
				pointer=strstr(jason,"\"");
				strncpy(cl->date,pointer+1,strcspn(pointer+1,"\""));
				break;
			default :
				return 0;
		}
	counter++;
        if(counter==6){
            strcpy(jason,"End");
        } else if (!pointer) return 0;
        else {
        pointer=strstr(jason,",");
        strcpy(jason,pointer);
        pointer=strstr(jason,"\"");
        }
	}
	pointer=NULL;
	return 1;
}

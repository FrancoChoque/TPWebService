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

int parse_xml(client_t*, const char*);

int main(int argc,char ** argv){

    int st;
    client_t  client;
    if(!(st=parse_xml(&client, argv[argc-1])))
        return 0;
    printf("%d\n",client.client_id);
    printf("%s\n",client.name);
    printf("%s\n",client.surname);
    printf("%s\n",client.mail);
    printf("%s\n",client.date);
    return 1;

}
/*'​ <?​ xml version=​ "1.0"
encoding=​ "UTF-8"​ ?>​ < ​ Cliente​ ><​ id​ > ​ 1 ​ </​ id​ ><​ Nombre​ > ​ JUAN​ </​ Nombre​ ><​ Apellido​ > ​ PEREZ​ </​ Apellido
><​ Telefono​ >4444-4444</​ Telefono​ ><​ Mail​ >juan@perez.com.ar</​ Mail​ ><​ Time​ > ​ 19​ /09/2016
19:04:33</​ Time​ ></​ Cliente​ > ​ '*/
int parse_xml(client_t* cl,const char * xml){
	char *xm,pointer[100],delim[2]=">",id[2];
	int st,last=0,counter=0;
	xm=malloc(sizeof(char)*(strlen(xml)+1));
	strcpy(xm,xml);
	strcpy(pointer,strtok(xm,delim));
	strcpy(pointer,strtok(NULL,delim));
	strcpy(pointer,strtok(NULL,delim));
	while(pointer){
		switch(pointer[6]){
			case 'd' :
				strcpy(pointer,strtok(NULL,delim));
				last=strcspn(pointer,"123456789");
				id[0]=pointer[last];
				if(pointer[last+1]!=' ' || pointer[last+1]!='<')
                        id[1]=pointer[last+1];
				cl->client_id=atoi(id);
				break;
			case 'o':
                strcpy(pointer,strtok(NULL,delim));
                last=strcspn(pointer,"<");
				if(pointer[0]==' ')
                strncpy(cl->name,pointer+1,last-2);
                else
				strncpy(cl->name,pointer,last);
				break;
			case 'p':
                strcpy(pointer,strtok(NULL,delim));
                last=strcspn(pointer,"<");
				if(pointer[0]==' ')
					strncpy(cl->surname,pointer+1,last-2);
                else
				strncpy(cl->surname,pointer,last);
				break;
			case 'e':
                strcpy(pointer,strtok(NULL,delim));
                last=strcspn(pointer,"<");
				if(pointer[0]==' ')
					strncpy(cl->telephone,pointer+1,last-2);
                else
				strncpy(cl->telephone,pointer,last);
				break;
			case 'a':
                strcpy(pointer,strtok(NULL,delim));
                last=strcspn(pointer,"<");
				if(pointer[0]==' ')
					strncpy(cl->mail,pointer+1,last-2);
                else
				strncpy(cl->mail,pointer,last);
				break;
			case 'i':
                strcpy(pointer,strtok(NULL,delim));
                last=strcspn(pointer,"<");
				if(pointer[0]==' ')
					strncpy(cl->date,pointer+1,last-2);
                else
				strncpy(cl->date,pointer,last);
				break;
			default :
                free(xm);
				return 0;
		}
        strcpy(pointer,strtok(NULL,delim));
        counter++;
        if(counter==6) break;
    }
	free(xm);
	xm=NULL;
	return 1;
}

#ifndef ADT_Clientes__H__
#define ADT_Clientes__H__

#define STR_LEN 21;


typedef struct{
	int client_id;
	char name[STR_LEN];
	char surname[STR_LEN];
	char telephone[STR_LEN];
	char mail[STR_LEN];
	char date[STR_LEN];
}ADT_Cliente;	
	

#endif
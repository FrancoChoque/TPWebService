#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* strdup(const char* );

int main()
{
   const char haystack[400] =  "tpws\" -X POST -H ​Content-Type:application/xml http:// SERVERTP1GRUPAL:8888/ setClientById/ ​ -d​ ​<?xmlversion=1.0 encoding=UTF-8?>​ <Cliente><id>​ 1 </id><Nombre>​ JUAN​ </Nombre><Apellido>​ PEREZ​ </Apellido><Telefono>4444-4444</Telefono><Mail>juan@perez.com.ar</Mail><Time>19/09/2016 19:04:33</Time>\"</Cliente>";

   char* ret;
	
	ret = strdup(strstr(haystack, "-d"));

   printf("The substring is: %s\n", ret);
   printf("%s\n", haystack);
   
   return(0);
}


char* strdup(const char* s){ 

	char* d;

	if((d = (char*) malloc (strlen(s)+1)) == NULL){
		return NULL;
	}

	strcpy(d,s);

	return d;
}
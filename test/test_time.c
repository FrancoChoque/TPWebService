#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


int main(void){

	time_t time_stamp;
	struct tm* display;
	char time_string[21];
	char str;

	if(time(&time_stamp) == -1){
		return 1;
	}
	
	if((display = localtime(&time_stamp)) == NULL){
		return 1;
	}
	
	strftime(time_string,20,"%d/%m/%Y %H:%M:%S",display);
	

	printf("%s\n",time_string);

	return 0;
}	

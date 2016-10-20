#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "ADT_List.h"


int create_list (list_t* list, destroyer_t destroyer){

	if(list = NULL){
		return ERROR_NULL_POINTER;
	}

	list-> first = NULL;
	list-> current = NULL;
	list-> node_counter = 0;
	list-> destroyer = destroyer;

	return OK;
}



int add_node (list_t* list, void* data){ /*si se agrega un cliente, es siempre al final de la lista*/

	
	node_t* aux;

	if(list == NULL || data == NULL){
		return ERROR_NULL_POINTER;
	}

	aux

}



int empty_list (list_t*);
int destroy_list(list_t*);
int is_empty(list_t*);
int move_current(list_t*);
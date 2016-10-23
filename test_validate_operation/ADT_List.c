#include "ADT_List.h"


int ADT_List_create (list_t* list, size_t size, copy_t copy, destroy_t destroy){

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}

	list-> first = NULL;
	list-> current = NULL;
	list-> data_size = size;
	list-> copy = copy;
	list-> destroy = destroy;

	return OK;
}



int ADT_List_destroy (list_t* list){

	int st;
	
	
	if(list == NULL){
		return ERROR_NULL_POINTER;
	}
	
	if((st = empty_list(list))!= OK){
		return st;
	}

	return OK;
}



int empty_list(list_t *list){

	node_t *current, *next;

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}
	
	for(current = list->first; current; current = next){
		next = current->next;
		list->destroy(current->data);
		free(current->data);
		free(current);
	}
	
	list->first = list->current = NULL;

	return OK;
}




int is_empty (list_t list){

	return (list.first == NULL)? 1:0;
}



int ADT_List_get_node (const list_t* list, void* data){

	int st;

	

	if((st = list->copy(data,list->current->data))!= OK){
		return st;
	}


	return OK;
}


int move_current(list_t* list, movement_t M){

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}

	switch(M){

		case mov_first:
			list->current = list->first;
		break;

		case mov_next:
			if (list->current->next == NULL) return ERROR_INVALID_MOVEMENT;
			
			list->current = list->current->next;
		break;

		case mov_previous: return ERROR_INVALID_MOVEMENT; 
	}
	
	return OK;
}




int ADT_List_delete_node(list_t *list){

	node_t *aux, *aux2;

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}

	aux = list->current;
	
	if(list->current == list->first){ /*Si es el primero*/
		list->first = list->current->next;
		list->current = list->first;
	}

	else{
		
		if(list->current->next != NULL){ /*Si no es el último*/
			aux = list->current->next;
			memcpy(list->current->data, aux->data, list->data_size);
			list->current->next = aux->next;
		}

		else{							/*Si es el último queda en el Anterior al borrado */
			aux2 = list->first;
			while (aux2->next != list->current){ /*recorre la lista hasta llegar al anteúltimo*/
				aux2 = aux->next;
			}
			aux2->next = list->current->next; /*el anteúltimo apunta a NULL*/
			list->current = aux2; 	/*actualiza el current*/
		}
	}

	dispose_node(aux,list->destroy);

	return OK;
}




int ADT_List_insert_node(list_t* list, movement_t M, const void* adition){


	int st;
	node_t* new_node;
	void* swap_aux;


	if(list == NULL || adition == NULL){
		return ERROR_NULL_POINTER;
	}
	
	if((st = build_node(&new_node,list->data_size,adition,list->copy))!= OK){
		return st;
	}
	
	
	
	if((list->first == NULL) || (M == mov_first) || ((M == mov_previous) && (list->first == list->current))){
		new_node->next = list->first;
		list->first = list->current = new_node;
	}
	else{
		new_node->next = list->current->next;
		list->current->next = new_node;
		if(M == mov_previous){
			swap_aux = new_node->data;
			new_node->data = list->current->data;
			list->current->data = swap_aux;
		}
	}
	
	list->current = new_node;
	
	return OK;
}


int ADT_List_update(list_t* list, const void* data) {
	
	
	void* new_data;
	int st;


	if(list == NULL || data == NULL){
		return ERROR_NULL_POINTER;
	}


	if(list->first == NULL){
		return ERROR_EMPTY_LIST; /* Lista vacía: No puedo actualizar */
	}
	
	if((new_data = (void*) malloc(list->data_size)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if((st = list->copy(new_data, data))!= OK){
		free(new_data);
		return st;
	}

	

	list->destroy(list->current->data);
	free(list->current->data);
	list->current->data = new_data;
	
	return OK;
	
}





/* <private functions> */




void dispose_node(node_t *node, destroy_t destroy){
	
	if(node == NULL) return;
	destroy(node->data);
	free(node->data);
	free(node);
	node = NULL;
	return;
}


int build_node(node_t** node, size_t size, const void* data, copy_t copy){
	
	int st;


	if(data == NULL){
		return ERROR_NULL_POINTER;
	}
	
	if(((*node) = (node_t*) malloc(sizeof(node_t))) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if(((*node)->data = (void*) malloc (size)) == NULL){
		free(*node);
		(*node) = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if((st = copy((*node)->data, data))!= OK){
		free((*node)->data);
		free(*node);
		return st;
	}
	
	return OK;
}
/* </private functions> */





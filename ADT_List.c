#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "ADT_List.h"


int ADT_List_create (list_t* list, copy_t copy, destroyer_t destroyer){

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}

	list-> first = NULL;
	list-> current = NULL;
	list-> copy = copy;
	list-> destroyer = destroyer;

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



int ADT_List_empty(list_t *list){

	node_t *current, *next;
	int st;

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}
	
	for(current = list->first; current; current = next){
		next = current->next;
		st = lp->destroy(current->data);
		free(current->data);
		free(current);
	}
	
	list->first = list->current = NULL;

	return OK;
}




int ADT_List_is_empty (list_t list){

	return (list.first == NULL);
}



int ADT_List_get_node (list_t list, void* data){

	int st;

	if(data == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = list.copy(data, list.current->data))!= OK){
		return st;
	}

	return OK;
}


int move_current(list_t* list, movement_t M){

	if(list == NULL){
		return ERROR_NULL_POINTER;
	}

	switch(M){

		case first:
			list->current = list->first;
		break;

		case next:
			if (list->current->next == NULL)
				return FALSE;
			else
				list->current = list->current->next;
		break;

		case previous: return FALSE; /*preguntar/arreglar*/
	}
	return OK;
}




int delete_node(list_t *list){

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
			memcpy(pLs->Corriente->Elem, pNodo->Elem, pLs->TamanioDato);
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

	list->destroyer(aux->data);
	free(aux->data);
	free(aux);
	aux = NULL;

	return OK;
}




int add_node(list_t* list, movement_t M, void* adition){


	int st;
	node_t* aux;
	void* swap_aux;

	if(list == NULL || adition == NULL){
		return ERROR_NULL_POINTER;
	}

	if((aux = (node_t*) malloc(sizeof(node_t))) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	if((aux->data = (void*) malloc(list->data_size)) == NULL){
		free(aux);
		aux = NULL;
		return ERROR_MEMORY_SHORTAGE;
	}

	
	if((st = list->copy(aux->data, adition))!= OK){
		free(aux->data);
		free(aux);
		aux = NULL;
		return st;
	}	
	
	if((is_empty(list)) || (M == mov_first) || ((M == mov_previous) && (list->first == list->current))){
		aux->next = list->first;
		(list->first = list->current) = aux;
	}
	else{
		aux->next = list->current->next;
		list->current->next = aux;
		if(M == mov_previous){
			swap_aux = aux->data;
			aux->data = list->current->data;
			list->current->data = swap_aux;
		}
	}
	
	list->current = aux;
	
	return OK;
}





/* <private functions> */
void dispose_node(straight_list_node_t * node, straight_list_destroy_t destroy) {
	destroy(node->data);
	free(node->data);
	free(node);
}

straight_list_node_t * build_node(size_t size, const void* data, straight_list_copy_t copy) {
	
	straight_list_node_t *node = (straight_list_node_t*) malloc(sizeof(straight_list_node_t));
	if (!node) { /* No hay memoria disponible */
		return NULL;
	}
	
	node->data = malloc (size);
	if(!node->data) { /* No hay memoria disponible */
		free(node);
		return NULL;
	}

	if(copy(node->data, data) != RES_OK) {
		free(node->data);
		free(node);
		return NULL;
	}
	
	return node;
}
/* </private functions> */








void straight_list_delete(straight_list_t *lp)
{
	straight_list_node_t *current = lp->current;
	if (lp->current==lp->first)
	{
		lp->first = lp->current->next;
		lp->current = lp->first;
	}
	else
	{
		if(lp->current->next){
			/* En este caso en que el corriente no es el ultimo, puedo evitarme
			 * recorrer toda la lista buscando el anterior */
			current=lp->current->next;
			memcpy(lp->current->data, current->data, lp->size);
			lp->current->next = current->next;
		}else {
			straight_list_node_t *aux = lp->first;
			while (aux->next != lp->current) {
				aux = aux->next;
			}
			aux->next=lp->current->next;
			lp->current = aux; /*Si es el ultimo queda en el Anterior al borrado */
		}
	}

	dispose_node(current, lp->destroy);
}

int straight_list_insert(straight_list_t *lp, straight_list_movement_t m, const void* data)
{
	straight_list_node_t *new_node = build_node(lp->size, data, lp->copy);
	if(!new_node) return FALSE;
	
	if ((lp->first == NULL) || (m==straight_list_first) || ((m==straight_list_previous) && (lp->first==lp->current)))
	{
		/*Si esta vacia o hay que insertar en el Primero o
		hay que insertar en el Anterior y el actual es el Primero */
		new_node->next = lp->first;
		lp->first = lp->current = new_node;
	}
	else
	{
		/* Siempre inserto como siguiente, el nodo nuevo, porque es más fácil */
		new_node->next = lp->current->next;
		lp->current->next = new_node;
		if (m == straight_list_previous)
		{
			/* Pero cuando el movimiento es Anterior, entonces swapeo los elementos */
			void* tmp = new_node->data;
			new_node->data = lp->current->data;
			lp->current->data = tmp;
		}
	}
	lp->current=new_node;
	return TRUE;
}

int straight_list_update(straight_list_t* l, const void* data) {
	if(!l->first) {
		return FALSE; /* Lista vacía: No puedo actualizar */
	}
	
	void* new_data = malloc(l->size);
	if(!new_data) {
		return FALSE;
	}
	
	if(l->copy(new_data, data) == RES_OK) {
		l->destroy(l->current->data);
		free(l->current->data);
		l->current->data = new_data;
		return TRUE;
	} else {
		free(new_data);
		return FALSE;
	}
}


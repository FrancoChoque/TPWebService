#ifndef ADT_LIST__H__
#define ADT_LIST__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"




typedef int (*list_copy_t) (void*, const void*);
typedef int (*list_destroy_t) (void*);
typedef int (*list_compare_t) (const void*, const void*);

typedef enum{
	mov_first,
	mov_next,
	mov_previous
}movement_t;



typedef struct node_t{
	struct node_t* next;
	void* data;
}node_t;


typedef struct{
	node_t *first, *current;
	size_t data_size;
	list_destroy_t destroy;
	list_copy_t copy;
}list_t;



/*
PRE: 
POST: lista creada
*/
int ADT_List_create (list_t*, size_t size, list_copy_t, list_destroy_t);


/*
PRE: lista creada
POST: lista vacia
*/
int ADT_List_destroy (list_t*);


/*
PRE: lista no vacía
POST: lista vacía
*/
int ADT_List_empty (list_t*);



/*
PRE: estructura con memoria asignada para  el nodo 
POST: copia el nodo apuntado por el corriente en la estructura
*/
int ADT_List_get_node (const list_t*, void*);



/*
PRE: -
POST: nodo destruido, el corriente apunta al siguiente nodo
*/
int ADT_List_delete_node (list_t*);


/*
PRE: 
POST: nodo insertado
*/
int ADT_List_insert_node (list_t*, movement_t, const void*);



/*
PRE: lista no vacia 
POST: lista actualizada
*/
int ADT_List_update (list_t*, const void*);




int ADT_List_search (list_t*, void*, list_compare_t);


int empty_list(list_t*);
int is_empty (list_t);
int move_current(list_t*, movement_t);




void dispose_node(node_t*, list_destroy_t);
int build_node(node_t**, size_t, const void*, list_copy_t);
#endif


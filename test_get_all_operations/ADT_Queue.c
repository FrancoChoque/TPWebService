#include "ADT_Queue.h"

int ADT_Queue_create(queue_t *queue, size_t size, queue_copy_t copy, queue_destroy_t destroy){

	queue->first = queue->last = NULL;
	queue->data_size = size;
	queue->copy = copy;
	queue->destroy = destroy;
	
	return OK;
}

void ADT_Queue_destroy(queue_t *queue){
	
	empty_queue(queue);
	return;
}

void empty_queue(queue_t *queue){

	queue_node_t *pAux = queue->first;
	queue_node_t *pnext;
	while (pAux){
		pnext = pAux->next;
		queue->destroy(pAux->data);
		free(pAux->data);
		free(pAux);
		pAux = pnext;
	}
	queue->first = queue->last = NULL;
}

int queue_is_empty(queue_t queue){
	
	return (queue.first==NULL);
}


int ADT_Queue_push(queue_t *queue, void* new_data){
	

	queue_node_t *node; 

	if((node = (queue_node_t*) malloc(sizeof(queue_node_t))) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if((node->data = (void*) malloc (queue->data_size)) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}
	
	if (queue->last)
		queue->last->next = node;
	if (!queue->first) 
		queue->first = node;
	node->next = NULL;
	queue->last = node;
	queue->copy(node->data, new_data);
	return OK;
}


int ADT_Queue_dequeue(queue_t *queue, void* node){

	queue_node_t *pAux = queue->first;
	
	if (!queue->first)
		return ERROR_EMPTY_LIST;
	
	queue->first = queue->first->next;
	
	if (!queue->first){
		queue->last = NULL;
	}
	queue->copy(node, pAux->data);
	queue->destroy(pAux->data);
	free(pAux->data);
	free(pAux);
	return OK;
}
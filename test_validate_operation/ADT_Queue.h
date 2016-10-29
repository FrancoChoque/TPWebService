#ifndef ADT_Queue__H__
#define ADT_Queue__H__

#include <stdlib.h>
#include "errors.h"

	
	#if !defined(FALSE)
		#define FALSE 0
	#endif
	
	#if !defined(TRUE)
		#define TRUE 1
	#endif

	typedef int (*queue_copy_t) (void* dest, const void* src);

	typedef void (*queue_destroy_t) (void*);
	
	typedef struct queue_node_t{
		void* data;
		struct queue_node_t *next;
	}queue_node_t;
	
	
	typedef struct{
		queue_node_t *first, *last;
		size_t data_size;
		queue_copy_t copy;
		queue_destroy_t destroy;
	}queue_t;
	
	
	void ADT_Queue_create(queue_t*, size_t, queue_copy_t, queue_destroy_t);
	
	void ADT_Queue_destroy(queue_t*);

	void empty_queue(queue_t*);
	
	int queue_is_empty(queue_t);

	int ADT_Queue_push(queue_t*, void*);
	
	int ADT_Queue_dequeue(queue_t*, void*);

#endif
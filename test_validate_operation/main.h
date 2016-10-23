#ifndef MAIN__H__
#define MAIN__H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ADT_Client.h"
#include "ADT_List.h"
#include "errors.h"




typedef int (*comparator_t) (const void*, const void*);

char* strdup (const char*);
int split(char*, char***, int*);
int valid_client(list_t*,int);


void print_client(client_t*);
int fill_list(list_t*);

int valid_client(list_t*,int);
int search_list(void*,list_t*,comparator_t);
#endif
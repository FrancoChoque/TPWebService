#ifndef TEST__H__
#define TEST__H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ADT_Client.h"
#include "ADT_List.h"
#include "errors.h"






char* strdup (const char*);
int split(char*, char***, int*);


void print_client(client_t*);
int fill_list(list_t*);
#endif
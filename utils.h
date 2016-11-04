#ifndef UTILS__H__ 
#define UTILS__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

#define CSV_DELIM ';'
#define INIT_CHOP 1
#define STR_LEN 30

typedef void (*print_string_t)(char*, const char*, const char*);


int concat_str_array(int, const char**, char**);
char* strdup(const char*);
int split_csv_string(char*, char***, int*);
void destroy_string_array(char**, int);


#endif
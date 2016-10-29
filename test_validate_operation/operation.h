#ifndef OPERATION__H__
#define OPERATION__H__ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "utils.h"



int compare_operation(const void*, const void*);
int destroy_operation(void*);
int copy_operation(void*, const void*);


#endif
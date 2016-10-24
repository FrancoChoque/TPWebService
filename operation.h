#ifndef OPERATION__H__
#define OPERATION__H__ 

#include <string.h>
#include "errors.h"


typedef int (*ws_operation) (void*);

int compare_operation(const void*, const void*);


#endif
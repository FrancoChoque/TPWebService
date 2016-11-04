#ifndef MAIN__H__
#define MAIN__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADTWS_Op.h"
#include "ADTWS.h"
#include "straight_list.h"
#include "queue.h"
#include "errors.h"
#include "utils.h"
#include "operation.h"


#define MIN_ARGS 2


int validate_arguments(int, char**);
int execute_operation(ADTWS*);


#endif
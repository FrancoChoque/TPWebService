#ifndef ERRORS__H__
#define ERRORS__H__

#include <stdio.h>

#define OK 0
#define ERROR_NULL_POINTER 1
#define ERROR_INVALID_ARGUMENTS 2
#define ERROR_MEMORY_SHORTAGE 3
#define ERROR_SYS_TIME 4
#define ERROR_OPENING_FILE 5
#define ERROR_DISK_SPACE 6
#define ERROR_MISSING_FILE 7
#define ERROR_EMPTY_LIST 8
#define ERROR_INVALID_OPERATION 9
#define ERROR_UNSUPPORTED_CONTENT_TYPE 10
#define ERROR_INVALID_DATA 11
#define ERROR_INVALID_MOVEMENT 12

#define FALSE 0
#define TRUE 1


#define MSG_OK "true"
#define MSG_ERROR_NULL_POINTER "Null pointer"
#define MSG_ERROR_INVALID_ARGUMENTS "Invalid arguments"
#define MSG_ERROR_MEMORY_SHORTAGE "Insufficient memory"
#define MSG_ERROR_SYS_TIME "Unable to obtain system time"
#define MSG_ERROR_OPENING_FILE "File could not be opened"
#define MSG_ERROR_DISK_SPACE "File could not be closed"
#define MSG_ERROR_MISSING_FILE "File not found"

#endif


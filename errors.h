#ifndef ERRORS__H__
#define ERRORS__H__

#include <stdio.h>

#define OK 0

/*Errores del sistema */
#define ERROR_NULL_POINTER 1
#define ERROR_INVALID_ARGUMENTS 2
#define ERROR_MEMORY_SHORTAGE 3
#define ERROR_SYS_TIME 4
#define ERROR_OPENING_FILE 5
#define ERROR_DISK_SPACE 6
/*-------------------------*/



/*Errores del web service*/
#define ERROR_MISSING_FILE 7
#define ERROR_INVALID_OPERATION 8
#define ERROR_UNSUPPORTED_CONTENT_TYPE 9
#define ERROR_INVALID_METHOD 10
/*------------------------*/


/*Errores en la llamada al programa*/
#define ERROR_OPERATION_NOT_FOUND 11
#define ERROR_URL_NOT_FOUND 12
#define ERROR_HOST_NOT_FOUND 13
#define ERROR_DATA_NOT_FOUND 14 
#define ERROR_CONTENT_TYPE_HEADER_NOT_FOUND 15
#define ERROR_INVALID_XML 16

/*Al buscar en request, encontró la bandera pero el campo estaba vacío*/
#define ERROR_MISSING_DATA 17 

#define ERROR_OPERATION_FAILURE 18
/*---------------------------------------------*/


#define ERROR_FLAG "Error"

#define MSG_OK "true"
#define MSG_ERROR_NULL_POINTER "Null pointer"
#define MSG_ERROR_INVALID_ARGUMENTS "Invalid arguments"
#define MSG_ERROR_MEMORY_SHORTAGE "Insufficient memory"
#define MSG_ERROR_SYS_TIME "Unable to obtain system time"
#define MSG_ERROR_OPENING_FILE "File could not be opened"
#define MSG_ERROR_DISK_SPACE "File could not be closed"
#define MSG_ERROR_MISSING_FILE "File not found"
#define MSG_ERROR_INVALID_OPERATION "Invalid operation"
#define MSG_ERROR_UNSUPPORTED_CONTENT_TYPE "Content type not supported"
#define MSG_ERROR_INVALID_METHOD "Invalid method"
#define MSG_ERROR_OPERATION_NOT_FOUND "Missing operation"
#define MSG_ERROR_URL_NOT_FOUND "Missing URL"
#define MSG_ERROR_HOST_NOT_FOUND "Missing host"
#define MSG_ERROR_DATA_NOT_FOUND "Missing data"
#define MSG_ERROR_CONTENT_TYPE_HEADER_NOT_FOUND "Missing content type"
#define MSG_ERROR_INVALID_XML "Invalid XML"
#define MSG_ERROR_MISSING_DATA "Null data"
#define MSG_ERROR_OPERATION_FAILURE "Operation failure"


#endif


#ifndef TYPES_H
#define TYPES_H

/* Typedef for creating the alias to unsigned int data type */
typedef unsigned int uint;

/* Status will be used as Function return type */
typedef enum
{
    SUCCESS,
    FAILURE,
    
} Status;

typedef enum
{
    view_tag,
    edit_tag,
    help,
    unsupported
} OperationType;

#endif
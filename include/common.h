#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include "onegin_file.h"

enum Errors 
{
    EXECUTION_SUCCESS              =-1,
    GETTING_FILE_SIZE_ERROR        = 0,
    INPUT_FILE_OPEN_ERROR          = 1,
    OUTPUT_FILE_OPEN_ERROR         = 2,
    BUFFER_ALLOCATION_ERROR        = 3,
    READ_SYMBOLS_ERROR             = 4,
    STRING_ARRAY_ALLOCATION_ERROR  = 5,
    ONEGINFILE_ALREADY_CONSTRUCTED = 6,
    ONEGINFILE_ALREADY_DESTRUCTED  = 7,
    CORRUPTED_ONEGINFILE           = 8,
};

//-------------------------------------------------------------------------------------------------

size_t getFileSize(const char *filename);

void printError(int error);

void swapVoid(void *element1, void *element2, size_t size);

#endif // COMMON_H

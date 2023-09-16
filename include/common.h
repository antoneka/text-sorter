#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include "onegin_file.h"

enum Errors 
{
    EXECUTION_SUCCESS            =-1,
    GETTING_FILE_SIZE_ERROR      = 0,
    FILE_OPEN_ERROR              = 1,
    BUFFER_INITIALIZE_ERROR      = 2,
    READ_SYMBOLS_ERROR           = 3,
    EXPANDING_STRING_ARRAY_ERROR = 4,
    CALLOC_STRING_ARRAY_ERROR    = 5,
    ONEGINFILE_EXISTENCE_ERROR   = 6,
    MISSING_ONEGINFILE_ERROR     = 7,
};

//-------------------------------------------------------------------------------------------------

size_t getFileSize(const char *filename);

int handleErrors(int status);

void swapVoid(void *data, size_t element1_pos, size_t element2_pos, size_t size);

#endif // COMMON_H

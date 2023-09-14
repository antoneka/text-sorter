#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

enum Errors 
{
    EXECUTION_SUCCESS            =-1,
    FILE_OPEN_ERROR              = 0,
    BUFFER_INITIALIZE_ERROR      = 1,
    READ_SYMBOLS_ERROR           = 2,
    EXPANDING_STRING_ARRAY_ERROR = 3,
    CALLOC_STRING_ARRAY_ERROR    = 4,
    ONEGINFILE_EXISTENCE_ERROR   = 5,
    MISSING_ONEGINFILE_ERROR     = 6,
};

size_t getFileSize(FILE *file_input);
int handleErrors(int status);

#endif // COMMON_H

#ifndef COMMON_H
#define COMMON_H

#include "input_output.h"

enum Errors 
{
    EXECUTION_SUCCESS            =-1,
    FILE_OPEN_ERROR              = 0,
    BUFFER_INITIALIZE_ERROR      = 1,
    READ_SYMBOLS_ERROR           = 2,
    EXPANDING_STRING_ARRAY_ERROR = 3,
    CALLOC_STRING_ARRAY_ERROR    = 4,
};

int expandStringArray(OneginFile *onegin);
size_t getFileSize(FILE *file_input);
void freeFile(OneginFile *onegin);
int statusCheck(int status);

#endif // COMMON_H

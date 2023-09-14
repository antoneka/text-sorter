#include "common.h"
#include <assert.h>

//-------------------------------------------------------------------------------------------------

size_t getFileSize(FILE *file_input)
{
    fseek(file_input, 0, SEEK_END);

    size_t file_size = (size_t)ftell(file_input);

    fseek(file_input, 0, SEEK_SET);


    return file_size;
}

//-------------------------------------------------------------------------------------------------

int handleErrors(int status)
{
    switch (status)
    {
        case FILE_OPEN_ERROR:
            fprintf(stderr, "%s\n", "The file doesn`t exist");
            return 0;


        case BUFFER_INITIALIZE_ERROR:
            fprintf(stderr, "%s\n", "Buffer initialization error");
            return 0;


        case READ_SYMBOLS_ERROR:
            fprintf(stderr, "%s\n", "Text reading error");
            return 0;


        case CALLOC_STRING_ARRAY_ERROR:
            fprintf(stderr, "%s\n", "String array initialization error");
            return 0;


        case EXPANDING_STRING_ARRAY_ERROR:
            fprintf(stderr, "%s\n", "String array expansion error");
            return 0;


        default:
            return EXECUTION_SUCCESS;
    }
}


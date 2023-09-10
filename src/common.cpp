#include "common.h"
#include <assert.h>


int expandStringArray(OneginFile *onegin)
{
    if (onegin->cur_line_num == onegin->total_line_num)
    {
        onegin->total_line_num += STANDART_LINES_NUM;


        char **string_arr_tmp = (char**)realloc(onegin->string_arr, onegin->total_line_num * sizeof(char*));

        if (!string_arr_tmp)
        {
            return EXPANDING_STRING_ARRAY_ERROR;
        }


        onegin->string_arr = string_arr_tmp;
    }


    return EXECUTION_SUCCESS;
}


size_t getFileSize(FILE *file_input)
{
    fseek(file_input, 0, SEEK_END);

    size_t file_size = (size_t)ftell(file_input);

    fseek(file_input, 0, SEEK_SET);


    return file_size;
}


void freeFile(OneginFile *onegin)
{
    if (onegin->file)
    {
        fclose(onegin->file);
        onegin->file = NULL;
    }


    free(onegin->buffer);
    onegin->buffer = NULL;


    free(onegin->string_arr);
    onegin->string_arr = NULL;
}


int statusCheck(int status)
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


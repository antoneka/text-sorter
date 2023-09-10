#include "common.h"
#include "input_output.h"


void outputText(OneginFile *onegin)
{
    for (size_t i = 0; i < onegin->cur_line_num; i++)
    {
        printf("%s\n", onegin->string_arr[i]);
    }
}


int inputText(OneginFile *onegin)
{
    onegin->file = fopen("onegin.txt", "r");

    if (!onegin->file)
    {
        return FILE_OPEN_ERROR;
    }


    onegin->file_size = getFileSize(onegin->file);


    int buffer_init_status = initBuffer(onegin);

    if (buffer_init_status != EXECUTION_SUCCESS)
    {
        return buffer_init_status;
    }


    int string_init_status = initStringArray(onegin);

    if (string_init_status != EXECUTION_SUCCESS)
    {
        return string_init_status;
    }


    return EXECUTION_SUCCESS;
}


int initStringArray(OneginFile *onegin)
{
    onegin->total_line_num = STANDART_LINES_NUM;
    onegin->cur_line_num = 0;


    onegin->string_arr = (char**)calloc(onegin->total_line_num, sizeof(char*));

    if (!onegin->string_arr)
    {
        return CALLOC_STRING_ARRAY_ERROR;
    }


    int lines_counting_status = countLines(onegin);

    if (lines_counting_status != EXECUTION_SUCCESS)
    {
        return lines_counting_status;
    }


    return EXECUTION_SUCCESS;
}


int initBuffer(OneginFile *onegin)
{
    onegin->buffer = (char*)calloc(onegin->file_size, sizeof(char));

    if (!onegin->buffer)
    {
        return BUFFER_INITIALIZE_ERROR;
    }


    size_t read_symbols = fread(onegin->buffer, sizeof(char), onegin->file_size, onegin->file);

    if (read_symbols != onegin->file_size)
    {
        return READ_SYMBOLS_ERROR;
    }


    return EXECUTION_SUCCESS;
}


int countLines(OneginFile *onegin)
{
    onegin->string_arr[onegin->cur_line_num++] = onegin->buffer;


    for (size_t i = 1; i < onegin->file_size; i++)
    {
        if (onegin->buffer[i] == '\n')
        {
            if (i != onegin->file_size - 1)
            {
                onegin->string_arr[onegin->cur_line_num++] = onegin->buffer + i + 1;
            }

            onegin->buffer[i] = '\0';
        }


        int expanding_arr_status = expandStringArray(onegin);

        if (expanding_arr_status != EXECUTION_SUCCESS)
        {
            return expanding_arr_status;
        }
    }


    return EXECUTION_SUCCESS;
}


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

    if (!onegin)
    {
        return FILE_OPEN_ERROR;
    }

    onegin->file_size = getFileSize(onegin->file);

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

    int parser_execution_status = bufferParser(onegin);

    return parser_execution_status;
}

int bufferParser(OneginFile *onegin)
{
    onegin->total_line_num = STANDART_LINES_NUM;
    onegin->cur_line_num = 0;

    onegin->string_arr = (char**)calloc(onegin->total_line_num, sizeof(char*));

    if (!onegin->string_arr)
    {
        return CALLOC_STRING_ARRAY_ERROR;
    }

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

        if (expanding_arr_status == EXPANDING_STRING_ARRAY_ERROR)
        {
            return EXPANDING_STRING_ARRAY_ERROR;
        }
    }

    return EXECUTION_SUCCESS;
}


#include <assert.h>
#include "common.h"
#include "onegin_file.h"

//-------------------------------------------------------------------------------------------------

void outputText(OneginFile *onegin)
{
    for (size_t i = 0; i < onegin->cur_line_num; i++)
    {
        if (onegin->string_arr[i].length > 0)
        {
            printf("%s\n", onegin->string_arr[i].str);
        }
    }
}

//-------------------------------------------------------------------------------------------------

int OneginFileCtor(OneginFile *onegin, const char *file_name)
{
    assert(onegin != nullptr);
    assert(file_name != nullptr);


    if (onegin->status != DESTRUCTED)
    {
        return ONEGINFILE_EXISTENCE_ERROR;
    }


    onegin->file = fopen(file_name, "r");

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


    onegin->status = CONSTRUCTED;


    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

static int initBuffer(OneginFile *onegin)
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

//-------------------------------------------------------------------------------------------------

static int initStringArray(OneginFile *onegin)
{
    onegin->total_lines_num = STANDART_LINES_NUM;

    onegin->cur_line_num = 0;


    onegin->string_arr = (String*)calloc(onegin->total_lines_num, sizeof(String));

    if (!onegin->string_arr)
    {
        return CALLOC_STRING_ARRAY_ERROR;
    }


    int lines_counting_status = fillStringArr(onegin);

    if (lines_counting_status != EXECUTION_SUCCESS)
    {
        return lines_counting_status;
    }


    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

static int fillStringArr(OneginFile *onegin)
{
    onegin->string_arr[onegin->cur_line_num++].str = onegin->buffer;

    size_t string_len = 1;


    for (size_t symbol_cnt = 1; symbol_cnt < onegin->file_size; symbol_cnt++, string_len++)
    {
        if (onegin->buffer[symbol_cnt] == '\n')
        {
            if (symbol_cnt != onegin->file_size - 1)
            {
                onegin->string_arr[onegin->cur_line_num].str = onegin->buffer + symbol_cnt + 1;

                onegin->string_arr[onegin->cur_line_num - 1].length = string_len;

                string_len = -1;

                onegin->cur_line_num++;
            }


            onegin->buffer[symbol_cnt] = '\0';
        }


        if (onegin->cur_line_num == onegin->total_lines_num)
        {
            int expanding_arr_status = expandStringArray(onegin);

            if (expanding_arr_status != EXECUTION_SUCCESS)
            {
                return expanding_arr_status;
            }
        }
    }


    onegin->string_arr[onegin->cur_line_num - 1].length = string_len - 1;
                                                    

    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

static int expandStringArray(OneginFile *onegin)
{
    onegin->total_lines_num += STANDART_LINES_NUM;


    String *string_arr_tmp = (String*)realloc(onegin->string_arr, onegin->total_lines_num * sizeof(String));

    if (!string_arr_tmp)
    {
        return EXPANDING_STRING_ARRAY_ERROR;
    }


    onegin->string_arr = string_arr_tmp;


    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

int oneginFileDtor(OneginFile *onegin)
{
    assert(onegin != nullptr);

    if (onegin->status != CONSTRUCTED)
    {
        return MISSING_ONEGINFILE_ERROR;
    }


    if (onegin->file)
    {
        fclose(onegin->file);

        onegin->file = nullptr;

        onegin->file_size = -1;
    }


    free(onegin->buffer);

    onegin->buffer = nullptr;


    free(onegin->string_arr);

    onegin->string_arr = nullptr;


    onegin->total_lines_num = -1;

    onegin->cur_line_num = -1;


    onegin->status = DESTRUCTED;


    return EXECUTION_SUCCESS;
}


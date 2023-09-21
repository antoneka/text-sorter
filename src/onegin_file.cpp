#include <assert.h>
#include "common.h"
#include "onegin_file.h"

static int initBuffer(OneginFile *onegin);

static int initStringArray(OneginFile *onegin);

static int fillStringArr(OneginFile *onegin);

static size_t countLines(OneginFile *onegin);

//-------------------------------------------------------------------------------------------------

int OneginFileCtor(OneginFile *onegin, const char *input_name, const char *output_name)
{
    assert(onegin != nullptr);
    assert(input_name != nullptr);
    assert(output_name != nullptr);

    if (onegin->status == CONSTRUCTED)
    {
        return ONEGINFILE_ALREADY_CONSTRUCTED;
    }

    onegin->file_input = fopen(input_name, "r");

    if (!onegin->file_input)
    {
        return INPUT_FILE_OPEN_ERROR;
    }

    onegin->file_output = fopen(output_name, "w+");

    if (!onegin->file_output)
    {
        return OUTPUT_FILE_OPEN_ERROR;
    }

    onegin->file_size = getFileSize(input_name);

    if (onegin->file_size == GETTING_FILE_SIZE_ERROR)
    {
        return GETTING_FILE_SIZE_ERROR;
    }

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

    size_t read_symbols = fread(onegin->buffer, sizeof(char), onegin->file_size, onegin->file_input);

    if (read_symbols != onegin->file_size)
    {
        return READ_SYMBOLS_ERROR;
    }

    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

static size_t countLines(OneginFile *onegin)
{
    size_t lines_num = 0;

    char *str = onegin->buffer;

    for (size_t symbol_cnt = 0; symbol_cnt < onegin->file_size; symbol_cnt++)
    {
        if (str[symbol_cnt] == '\n')
        {
            lines_num++;
        }
    }

    return lines_num;
}

//-------------------------------------------------------------------------------------------------

static int initStringArray(OneginFile *onegin)
{
    onegin->total_lines_num = countLines(onegin);

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
    size_t cur_line_num = 0;

    onegin->string_arr[cur_line_num++].str = onegin->buffer;

    size_t string_len = onegin->buffer[0] == '\n' ? 0 : 1;

    for (size_t symbol_cnt = 1; symbol_cnt < onegin->file_size; symbol_cnt++)
    {
        if (onegin->buffer[symbol_cnt] == '\n')
        {
            onegin->buffer[symbol_cnt] = '\0';

            if (symbol_cnt == onegin->file_size - 1) break;

            onegin->string_arr[cur_line_num].str = onegin->buffer + symbol_cnt + 1;
            onegin->string_arr[cur_line_num - 1].length = string_len;

            cur_line_num++;
            string_len = 0;
        }
        else
        {
            string_len++;
        }
    }

    onegin->string_arr[cur_line_num - 1].length = string_len;
                                                    
    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

int oneginFileDtor(OneginFile *onegin)
{
    assert(onegin != nullptr);

    if (onegin->status == DESTRUCTED)
    {
        return ONEGINFILE_ALREADY_DESTRUCTED;
    }

    if (onegin->file_input != nullptr)
    {
        fclose(onegin->file_input);
        onegin->file_input = nullptr;
    }

    if (onegin->file_output != nullptr)
    {
        fclose(onegin->file_output);
        onegin->file_output = nullptr;
    }

    onegin->file_size = 0;

    free(onegin->buffer);
    onegin->buffer = nullptr;

    free(onegin->string_arr);
    onegin->string_arr = nullptr;

    onegin->total_lines_num = 0;

    onegin->status = DESTRUCTED;

    return EXECUTION_SUCCESS;
}


#include <assert.h>
#include "input_output.h"
#include "common.h"

//-------------------------------------------------------------------------------------------------

void inputFileNames(FileNames *names)
{
    assert(names != nullptr);

    names->input = "input_text.txt";

    names->output_sorted = "output_sorted.txt";

    names->output_rsorted = "output_rsorted.txt";

    names->output_original = "output_original.txt";
}

//-------------------------------------------------------------------------------------------------

int outputSorted(OneginFile *onegin, FileNames *names)
{
    assert(onegin != nullptr);

    FILE *output_file = fopen(names->output_sorted, "w");

    if (output_file == nullptr)
    {
        return FILE_OPEN_ERROR;
    }

    for (size_t string_num = 0; string_num < onegin->cur_line_num; string_num++)
    {
        if (onegin->string_arr[string_num].length > 0)
        {
            fprintf(output_file, "%s\n", onegin->string_arr[string_num].str);
        }
    }

    fclose(output_file);

    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

int outputRSorted(OneginFile *onegin, FileNames *names)
{
    assert(onegin != nullptr);

    FILE *output_file = fopen(names->output_rsorted, "w");

    if (output_file == nullptr)
    {
        return FILE_OPEN_ERROR;
    }

    for (size_t string_num = 0; string_num < onegin->cur_line_num; string_num++)
    {
        if (onegin->string_arr[string_num].length > 0)
        {
            fprintf(output_file, "%s\n", onegin->string_arr[string_num].str);
        }
    }

    fclose(output_file);

    return EXECUTION_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

int outputOriginal(OneginFile *onegin, FileNames *names)
{
    assert(onegin != nullptr);

    FILE *output_file = fopen(names->output_original, "w");

    if (output_file == nullptr)
    {
        return FILE_OPEN_ERROR;
    }

    for (size_t string_num = 0, symbol_cnt = 0; string_num < onegin->cur_line_num; string_num++)
    {
        symbol_cnt += fprintf(output_file, "%s\n", onegin->buffer + symbol_cnt);
    }

    fclose(output_file);

    return EXECUTION_SUCCESS;
}


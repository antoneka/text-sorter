#include <assert.h>
#include "output.h"
#include "common.h"

//-------------------------------------------------------------------------------------------------

void outputSorted(OneginFile *onegin)
{
    assert(onegin != nullptr);

    for (size_t string_num = 0; string_num < onegin->cur_line_num; string_num++)
    {
        if (onegin->string_arr[string_num].length > 0)
        {
            fprintf(onegin->file_output, "%s\n", onegin->string_arr[string_num].str);
        }
    }

    fprintf(onegin->file_output, "\n=============================================================\n"
                                 "=============================================================\n\n");
}

//-------------------------------------------------------------------------------------------------

void outputOriginal(OneginFile *onegin)
{
    assert(onegin != nullptr);

    for (size_t string_num = 0, symbol_cnt = 0; string_num < onegin->cur_line_num; string_num++)
    {
        symbol_cnt += fprintf(onegin->file_output, "%s\n", onegin->buffer + symbol_cnt);
    }

    fprintf(onegin->file_output, "\n=============================================================\n"
                                 "=============================================================\n\n");
}


#include <stdio.h>
#include <stdlib.h>
#include "onegin_file.h"
#include "text_sorting.h"
#include "common.h"
#include "input_output.h"

int main()
{
    OneginFile onegin = {};
    FileNames file_names = {};

    inputFileNames(&file_names);

    int creation_status = OneginFileCtor(&onegin, file_names.input);
    
    if (handleErrors(creation_status) != EXECUTION_SUCCESS)
    {
        // printErrors
        oneginFileDtor(&onegin);
        return 1;
    }

    textSort(&onegin, (int (*) (const void*, const void*))stringsCompareFromLeft);

    int output_sorted_status = outputSorted(&onegin, &file_names);

    if (handleErrors(output_sorted_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }

    #if 0
    textSort(&onegin, (int (*) (const void*, const void*))stringsCompareFromRight);

    int output_rsorted_status = outputRSorted(&onegin, &names);

    if (handleErrors(output_rsorted_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }
    #endif

    int output_original_status = outputOriginal(&onegin, &file_names);

    if (handleErrors(output_original_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }
    
    int destruction_status = oneginFileDtor(&onegin);

    if (handleErrors(destruction_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }

    return 0;
}


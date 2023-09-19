#include <stdio.h>
#include <stdlib.h>
#include "onegin_file.h"
#include "text_sorting.h"
#include "common.h"
#include "output.h"

int main()
{
    OneginFile onegin = {};

    int creation_status = OneginFileCtor(&onegin, "input_text.txt", "output1_text.txt");

    if (creation_status != EXECUTION_SUCCESS)
    {
        printError(creation_status);
        oneginFileDtor(&onegin);

        return 1;
    }

    textSort(&onegin, (int (*) (const void*, const void*))stringsCompare);
    outputSorted(&onegin);

    textSort(&onegin, (int (*) (const void*, const void*))stringsReverseCompare);
    outputSorted(&onegin);

    outputOriginal(&onegin);
    
    int destruction_status = oneginFileDtor(&onegin);

    if (destruction_status != EXECUTION_SUCCESS)
    {
        printError(creation_status);
        return 1;
    }

    return 0;
}


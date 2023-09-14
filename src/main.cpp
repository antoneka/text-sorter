#include <stdio.h>
#include <stdlib.h>
#include "onegin_file.h"
#include "text_sorting.h"
#include "common.h"


int main()
{
    OneginFile onegin = {};

    const char *file_name = "onegin.txt";

    int create_onegin_file_status = OneginFileCtor(&onegin, file_name);
    
    if (handleErrors(create_onegin_file_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }

    textSort(&onegin);

    outputText(&onegin);
    

    int destroy_onegin_file_status = oneginFileDtor(&onegin);

    if (handleErrors(destroy_onegin_file_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }

    return 0;
}


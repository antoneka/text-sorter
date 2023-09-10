#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"
#include "text_sorting.h"
#include "common.h"

int main()
{
    OneginFile onegin = {};

    int execution_status = inputText(&onegin);
    
    if (statusCheck(execution_status) != EXECUTION_SUCCESS)
    {
        return 1;
    }

    textSort(&onegin);

    outputText(&onegin);
    
    freeFile(&onegin);

    return 0;
}

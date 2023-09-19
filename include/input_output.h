#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <assert.h>
#include "onegin_file.h"

struct FileNames
{
    const char *input;
    const char *output_sorted;
    const char *output_rsorted;
    const char *output_original;
};

// OneginFile file;

//-------------------------------------------------------------------------------------------------

void inputFileNames(FileNames *names);

int outputSorted(OneginFile *onegin, FileNames *names);

int outputRSorted(OneginFile *onegin, FileNames *names);

int outputOriginal(OneginFile *onegin, FileNames *names);

#endif // INPUT_OUTPUT_H

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

const int STANDART_LINES_NUM = 1000;

enum OnegFileStatus
{
    CONSTRUCTED = 1, DESTRUCTED  = 0,
};

struct String
{
    char *str;
    size_t length;
};

struct OneginFile
{
    FILE *file_input;
    FILE *file_output;

    int status;

    char *buffer;
    size_t file_size;

    String *string_arr;
    size_t total_lines_num;
    size_t cur_line_num;
};

//-------------------------------------------------------------------------------------------------

int OneginFileCtor(OneginFile *onegin, const char *input_name, const char *output_name);

int oneginFileDtor(OneginFile *onegin);

#endif // INPUT_H

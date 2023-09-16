#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

const int STANDART_LINES_NUM = 1000;

enum OnegFileStatus
{
    CONSTRUCTED = 1,
    DESTRUCTED  = 0,
};

struct String
{
    char *str;
    size_t length;
};

struct OneginFile
{
    FILE *file = nullptr;
    int status = DESTRUCTED;

    char *buffer = nullptr;
    size_t file_size = 0;


    String *string_arr = nullptr;
    size_t total_lines_num = 0;
    size_t cur_line_num = 0;
};

//-------------------------------------------------------------------------------------------------

int OneginFileCtor(OneginFile *onegin, const char *file_name);

int oneginFileDtor(OneginFile *onegin);

#endif // INPUT_H

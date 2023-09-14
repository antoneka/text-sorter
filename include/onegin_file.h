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
    FILE *file;
    int status = DESTRUCTED;

    char *buffer;
    size_t file_size;


    String *string_arr;
    size_t total_lines_num;
    size_t cur_line_num;
};

int OneginFileCtor(OneginFile *onegin, const char *file_name);

static int initBuffer(OneginFile *onegin);

static int initStringArray(OneginFile *onegin);

static int fillStringArr(OneginFile *onegin);

static int expandStringArray(OneginFile *onegin);

void outputText(OneginFile *onegin);

int oneginFileDtor(OneginFile *onegin);


#endif // INPUT_H

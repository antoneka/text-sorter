#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdlib.h>

const int STANDART_LINES_NUM = 100;

typedef struct 
{
    FILE *file;

    char *buffer;
    size_t file_size;

    char **string_arr;
    size_t total_line_num;
    size_t cur_line_num;
} OneginFile;

int inputText(OneginFile *onegin);
void outputText(OneginFile *onegin);
int bufferParser(OneginFile *onegin);
int expandStringArray(OneginFile *onegin);
size_t getFileSize(FILE *file_input);

#endif // INPUT_H

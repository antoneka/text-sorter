#ifndef TEXT_SORTING_H
#define TEXT_SORTING_H

#include "onegin_file.h"


void textSort(OneginFile *onegin);

int stringsCompareFromLeft(const String *first_string, const String *second_string);

int stringsCompareFromRight(const String *first_string, const String *second_string);


#endif // TEXT_SORTING_H

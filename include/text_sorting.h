#ifndef TEXT_SORTING_H
#define TEXT_SORTING_H

#include "onegin_file.h"

//-------------------------------------------------------------------------------------------------

void textSort(OneginFile *onegin, int (*comparator) (const void *, const void *));

int stringsCompareFromLeft(const String *first_str_ptr, const String *second_str_ptr);

int stringsCompareFromRight(const String *first_str_ptr, const String *second_str_ptr);

void quickSort(void *data, size_t left, size_t right, size_t size, int (*comparator) (const void*, const void*));

#endif // TEXT_SORTING_H

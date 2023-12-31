#ifndef TEXT_SORTING_H
#define TEXT_SORTING_H

#include "onegin_file.h"

//-------------------------------------------------------------------------------------------------

void textSort(OneginFile *onegin, int (*comparator) (const void *, const void *));

int stringsCompare(const String *first_str_ptr, const String *second_str_ptr);

int stringsReverseCompare(const String *first_str_ptr, const String *second_str_ptr);

void quickSort(void *data, size_t num, size_t size, int (*comparator) (const void*, const void*));

#endif // TEXT_SORTING_H

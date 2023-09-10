#include "text_sorting.h"
#include <ctype.h>


void textSort(OneginFile *onegin)
{
   qsort(onegin->string_arr, onegin->cur_line_num, sizeof(char*), 
        (int (*) (const void *, const void *))symbolsCompare);
}


int symbolsCompare(const char **first_string_ptr, const char **second_string_ptr)
{
    const char *first_string = *first_string_ptr;
    const char *second_string = *second_string_ptr;


    size_t first_string_length = 0, second_string_length = 0;


    while (first_string[first_string_length] != '\0' && second_string[second_string_length] != '\0')
    {
        if (!isalpha(first_string[first_string_length]))
        {
            first_string_length++;

            continue;
        }


        if (!isalpha(second_string[second_string_length]))
        {
            second_string_length++;

            continue;
        }
 

        if (tolower(first_string[first_string_length]) != tolower(second_string[second_string_length]))
        {
            return tolower(first_string[first_string_length]) - tolower(second_string[second_string_length]);
        }
        

        first_string_length++;
        second_string_length++;
    }


    return first_string[first_string_length] - second_string[second_string_length];
}

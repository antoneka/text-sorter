#include <assert.h>
#include <ctype.h>
#include "text_sorting.h"

//---------------------------------------------------------------------------------------

void textSort(OneginFile *onegin)
{
    assert(onegin != nullptr);


    qsort(onegin->string_arr, onegin->cur_line_num, sizeof(String), 
        (int (*) (const void *, const void *))stringsCompareFromRight);
}

//---------------------------------------------------------------------------------------

int stringsCompareFromLeft(const String *first_string, const String *second_string)
{
    assert(first_string != nullptr);
    assert(second_string != nullptr);


    size_t first_string_length = 0;

    size_t second_string_length = 0;


    while (first_string->str[first_string_length] != '\0' && second_string->str[second_string_length] != '\0')
    {
        if (!isalpha(first_string->str[first_string_length]))
        {
            first_string_length++;

            continue;
        }


        if (!isalpha(second_string->str[second_string_length]))
        {
            second_string_length++;

            continue;
        }
 

        if (tolower(first_string->str[first_string_length]) != tolower(second_string->str[second_string_length]))
        {
            return tolower(first_string->str[first_string_length]) - tolower(second_string->str[second_string_length]);
        }
        

        first_string_length++;

        second_string_length++;
    }


    return first_string->str[first_string_length] - second_string->str[second_string_length];
}

int stringsCompareFromRight(const String *first_string, const String *second_string)
{
    assert(first_string != nullptr);
    assert(second_string != nullptr);


    size_t first_string_length = first_string->length - 1;

    size_t second_string_length = second_string->length - 1;


    while (first_string->str[first_string_length] != '\0' && second_string->str[second_string_length] != '\0')
    {
        if (!isalpha(first_string->str[first_string_length]))
        {
            first_string_length--;

            continue;
        }


        if (!isalpha(second_string->str[second_string_length]))
        {
            second_string_length--;

            continue;
        }
 

        if (tolower(first_string->str[first_string_length]) != tolower(second_string->str[second_string_length]))
        {
            return tolower(first_string->str[first_string_length]) - tolower(second_string->str[second_string_length]);
        }
        

        first_string_length--;

        second_string_length--;
    }


    return first_string->str[first_string_length] - second_string->str[second_string_length];
}


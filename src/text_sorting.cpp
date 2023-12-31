#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "text_sorting.h"
#include "common.h"

static void _qsort(void *data, size_t left_idx, size_t right_idx, size_t size, 
                   int (*comparator) (const void*, const void*));

//-------------------------------------------------------------------------------------------------

void quickSort(void *data, size_t num, size_t size, int (*comparator) (const void*, const void*))
{
    if (num == 0)
    {
        return;
    }

    size_t left_idx = 0;
    size_t right_idx = num - 1;

    _qsort(data, left_idx, right_idx, size, comparator);
}

//-------------------------------------------------------------------------------------------------

static void _qsort(void *data, size_t left_idx, size_t right_idx, size_t size, 
                   int (*comparator) (const void*, const void*))
{
    if (left_idx >= right_idx)
    {
        return;
    }

    void *first_elem = (char*)data + left_idx * size;

    size_t pivot_idx = left_idx;

    void *fast_ptr = nullptr;
    void *pivot = nullptr;

    for (size_t i = left_idx + 1; i <= right_idx; i++)
    {
        fast_ptr = (char*)data + i * size;

        if (comparator(first_elem, fast_ptr) > 0)
        {
            pivot_idx++;
            pivot = (char*)data + pivot_idx * size;

            swapVoid(fast_ptr, pivot, size);
        }
    }

    pivot = (char*)data + pivot_idx * size;
    
    swapVoid(first_elem, pivot, size);

    _qsort(data, left_idx, pivot_idx == 0 ? left_idx : pivot_idx - 1, size, comparator);
    _qsort(data, pivot_idx + 1, right_idx, size, comparator);
}

//-------------------------------------------------------------------------------------------------

void textSort(OneginFile *onegin, int (*comparator) (const void *, const void *))
{
    assert(onegin != nullptr);

    quickSort(onegin->string_arr, onegin->total_lines_num, sizeof(String), comparator);
}

//-------------------------------------------------------------------------------------------------

int stringsCompare(const String *first_str_ptr, const String *second_str_ptr)
{
    assert(first_str_ptr != nullptr);
    assert(second_str_ptr != nullptr);

    char *first_string = first_str_ptr->str;
    char *second_string = second_str_ptr->str;

    size_t first_str_size = first_str_ptr->length;
    size_t second_str_size = second_str_ptr->length;

    size_t first_num_chars = 0;
    size_t second_num_chars = 0;

    while (first_num_chars < first_str_size && second_num_chars < second_str_size)
    {
        if (!isalpha(first_string[first_num_chars]))
        {
            first_num_chars++;
            continue;
        }

        if (!isalpha(second_string[second_num_chars]))
        {
            second_num_chars++;
            continue;
        }
 
        if (tolower(first_string[first_num_chars]) != tolower(second_string[second_num_chars]))
        {
            return tolower(first_string[first_num_chars]) - tolower(second_string[second_num_chars]);
        }
        
        first_num_chars++;
        second_num_chars++;
    }

    return first_string[first_num_chars] - second_string[second_num_chars];
}

//-------------------------------------------------------------------------------------------------

int stringsReverseCompare(const String *first_str_ptr, const String *second_str_ptr)
{
    assert(first_str_ptr != nullptr);
    assert(second_str_ptr != nullptr);

    if (first_str_ptr->length == 0 || second_str_ptr->length == 0)
    {
        return first_str_ptr->str[0] - second_str_ptr->str[0];
    }

    char *first_string = first_str_ptr->str;
    char *second_string = second_str_ptr->str;

    size_t first_num_chars = first_str_ptr->length - 1;
    size_t second_num_chars = second_str_ptr->length - 1;

    while (first_num_chars > 0 && second_num_chars > 0)
    {
        if (!isalpha(first_string[first_num_chars]))
        {
            first_num_chars--;
            continue;
        }

        if (!isalpha(second_string[second_num_chars]))
        {
            second_num_chars--;
            continue;
        }
 
        if (tolower(first_string[first_num_chars]) != tolower(second_string[second_num_chars]))
        {
            return tolower(first_string[first_num_chars]) - tolower(second_string[second_num_chars]);
        }

        first_num_chars--;
        second_num_chars--;
    }

    return tolower(first_string[first_num_chars]) - tolower(second_string[second_num_chars]);
}


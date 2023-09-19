#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "text_sorting.h"
#include "common.h"

static void _qsort(void *data, int left_idx, int right_idx, size_t size, 
                   int (*comparator) (const void*, const void*));

//-------------------------------------------------------------------------------------------------

void quickSort(void *data, size_t num, size_t size, int (*comparator) (const void*, const void*))
{
    int left_idx = 0;
    int right_idx = num - 1;

    _qsort(data, left_idx, right_idx, size, comparator);
}

//-------------------------------------------------------------------------------------------------

static void _qsort(void *data, int left_idx, int right_idx, size_t size, int (*comparator) (const void*, const void*))
{
    int mid = left_idx + ((right_idx - left_idx) >> 1);

    if (left_idx >= right_idx)
    {
        return;
    }

    void *left = (char*)data + left_idx * size;
    void *right = (char*)data + mid * size;

    swapVoid(left, right, size);

    int pivot = left_idx;

    void *fast_ptr = nullptr;
    void *slow_ptr = nullptr;

    for (int i = left_idx + 1; i <= right_idx; i++)
    {
        fast_ptr = (char*)data + i * size;

        if (comparator(left, fast_ptr) > 0)
        {
            pivot++;
            slow_ptr = (char*)data + pivot * size;

            swapVoid(fast_ptr, slow_ptr, size);
        }
    }

    slow_ptr = (char*)data + pivot * size;
    
    swapVoid(left, slow_ptr, size);

    _qsort(data, left_idx, pivot - 1, size, comparator);
    _qsort(data, pivot + 1, right_idx, size, comparator);
}

//-------------------------------------------------------------------------------------------------

void textSort(OneginFile *onegin, int (*comparator) (const void *, const void *))
{
    assert(onegin != nullptr);

    qsort(onegin->string_arr, onegin->cur_line_num, sizeof(String), 
        (int (*) (const void *, const void *))comparator);

//    quickSort(onegin->string_arr, onegin->cur_line_num, sizeof(String), comparator);
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

    return first_string[first_num_chars] - second_string[second_num_chars];
}


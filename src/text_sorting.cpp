#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "text_sorting.h"
#include "common.h"

static size_t partition(void *data, size_t left, size_t right, size_t size, int (*comparator) (const void*, const void*));

//-------------------------------------------------------------------------------------------------

static size_t partition(void *data, size_t left, size_t right, size_t size, int (*comparator) (const void*, const void*))
{
    assert(data != nullptr);
    assert(comparator != nullptr);

    void *pivot = calloc(1, size);

    size_t mid_num = left + ((right - left) >> 1);

    memcpy(pivot, (char*)data + mid_num * size, size);

    while (true)
    {
        // TODO; change (size_t) to (char*)
        while (comparator(pivot, (char*)data + left * size) > 0)
        {
            left++;
        }

        while (comparator((char*)data + right * size, pivot) > 0)
        {
            right--;
        }

        if (left >= right)
        {
            free(pivot);
            return right;
        }

        swapVoid((char*)data + left * size, (char*)data + right * size, size);
        
        right--;
        left++;
    }
}

//-------------------------------------------------------------------------------------------------

void quickSort(void *data, size_t left, size_t right, size_t size, int (*comparator) (const void*, const void*))
{
    assert(data != nullptr);
    assert(comparator != nullptr);

    if (left >= right) return;

    size_t mid = partition(data, left, right, size, comparator);

    quickSort(data, left, mid, size, comparator);
    quickSort(data, mid + 1, right, size, comparator);
}

//-------------------------------------------------------------------------------------------------

void textSort(OneginFile *onegin, int (*comparator) (const void *, const void *))
{
    assert(onegin != nullptr);

    /*
    qsort(onegin->string_arr, onegin->cur_line_num, sizeof(String), 
        (int (*) (const void *, const void *))stringsCompareFromRight);
    */

    quickSort(onegin->string_arr, 0, onegin->cur_line_num - 1, sizeof(String), comparator);
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


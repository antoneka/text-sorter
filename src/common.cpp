#include "common.h"
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

//-------------------------------------------------------------------------------------------------

size_t getFileSize(const char *filename)
{
    assert(filename != nullptr);

    struct stat file_info = {};

    stat(filename, &file_info);

    if (file_info.st_size <= 0)
    {
        return GETTING_FILE_SIZE_ERROR;
    }

    return (size_t)file_info.st_size;
}

//-------------------------------------------------------------------------------------------------

void swapVoid(void *element1, void *element2, size_t size)
{
    assert(element1 != nullptr);
    assert(element2 != nullptr);

    size_t size_ll = sizeof(long long);
    size_t size_i = sizeof(int);
    size_t size_ch = sizeof(char);

    while (size > 0)
    {
        if (size_ll <= size)
        {
            long long tmp = 0;

            tmp = *(long long*)element1;
            *(long long*)element1 = *(long long*)element2;
            *(long long*)element2 = tmp;

            element1 = (char*)element1 + size_ll;
            element2 = (char*)element2 + size_ll;

            size -= size_ll;
        }
        else if (size_i <= size)
        {
            int tmp = 0;

            tmp = *(int*)element1;
            *(int*)element1 = *(int*)element2;
            *(int*)element2 = tmp;

            element1 = (char*)element1 + size_i;
            element2 = (char*)element2 + size_i;

            size -= size_i;
        }
        else
        {
            char tmp = 0;

            tmp = *(char*)element1;
            *(char*)element1 = *(char*)element2;
            *(char*)element2 = tmp;

            element1 = (char*)element1 + size_ch;
            element2 = (char*)element2 + size_ch;

            size -= size_ch;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void printError(int error)
{
    switch (error)
    {
        case INPUT_FILE_OPEN_ERROR:
            fprintf(stderr, "Input file doesn`t exist\n");
            break;

        case OUTPUT_FILE_OPEN_ERROR:
            fprintf(stderr, "Failed to create an output file\n");
            break;

        case BUFFER_ALLOCATION_ERROR:
            fprintf(stderr, "Buffer allocation error\n");
            break;

        case READ_SYMBOLS_ERROR:
            fprintf(stderr, "Text reading error\n");
            break;

        case STRING_ARRAY_ALLOCATION_ERROR:
            fprintf(stderr, "String array allocation error\n");
            break;

        case GETTING_FILE_SIZE_ERROR:
            fprintf(stderr, "Getting file size error\n");
            break;

        case ONEGINFILE_ALREADY_CONSTRUCTED:
            fprintf(stderr, "OneginFile has already been constructed. It can`t be constructed again\n");
            break;

        case ONEGINFILE_ALREADY_DESTRUCTED:
            fprintf(stderr, "OneginFile has already been destructed. It can`t be destructed again\n");
            break;

        case CORRUPTED_ONEGINFILE:
            fprintf(stderr, "OneginFile wasn`t created through the constructor.\n"
                            "It can`t be destructed with garbage data in the fields\n");
            break;
 
        default:
            assert(0 && "Unknown error");
    }
}

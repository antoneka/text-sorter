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

// Execution_FAILED 
int handleErrors(int status)
{
    switch (status)
    {
        case FILE_OPEN_ERROR:
            fprintf(stderr, "%s\n", "File doesn`t exist");
            return 0;

        case BUFFER_INITIALIZE_ERROR:
            fprintf(stderr, "%s\n", "Buffer initialization error");
            return 0;

        case READ_SYMBOLS_ERROR:
            fprintf(stderr, "%s\n", "Text reading error");
            return 0;

        case CALLOC_STRING_ARRAY_ERROR:
            fprintf(stderr, "%s\n", "String array initialization error");
            return 0;

        case EXPANDING_STRING_ARRAY_ERROR:
            fprintf(stderr, "%s\n", "String array expansion error");
            return 0;

        case GETTING_FILE_SIZE_ERROR:
            fprintf(stderr, "%s\n", "Getting file size error");
            return 0;

        case ONEGINFILE_EXISTENCE_ERROR:
            fprintf(stderr, "%s\n", "OneginFile already exists. It can`t be constructed again");
            return 0;

        case MISSING_ONEGINFILE_ERROR:
            fprintf(stderr, "%s\n", "OneginFile doesn`t exist. It can`t be destructed");
            return 0;

        default:
            return EXECUTION_SUCCESS;
    }
}


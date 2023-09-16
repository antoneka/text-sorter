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

void swapVoid(void *data, size_t element1_pos, size_t element2_pos, size_t size)
{
    assert(data != nullptr);

    void *tmp = calloc(1, size);

    memcpy(tmp, (char*)data + element2_pos * size, size);

    memcpy((char*)data + element2_pos * size, (char*)data + element1_pos * size, size);

    memcpy((char*)data + element1_pos * size, tmp, size);

    free(tmp);
}

//-------------------------------------------------------------------------------------------------

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


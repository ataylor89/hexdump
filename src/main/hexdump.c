#include "hexdump.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* _hexdump(char* str)
{
    int i, j, size, line;
    char *buffer, *ptr;

    size = strlen(str);
    line = 0;
    buffer = (char *) malloc(sizeof(char) * size * 10);
    ptr = buffer;

    for (i = 0; i < size;)
    {
        sprintf(ptr, "%08x: ", line);

        ptr += 10;

        for (j = 0; j < 16; j++)
        { 
            if (i + j > size - 1)
            {
                int num_spaces = (j % 2 == 1) ? 3 : 2;
                sprintf(ptr, "%*c", num_spaces, ' ');
                ptr += num_spaces;
            }
            else if (j == 15)
            {
                sprintf(ptr, "%02hhx ", str[i + j]);
                ptr += 3;
            }
            else if (j % 2 == 1)
            {
                sprintf(ptr, "%02hhx ", str[i + j]);
                ptr += 3;
            }
            else
            {
                sprintf(ptr, "%02hhx", str[i + j]);
                ptr += 2;
            }
        }

        for (j = 0; j < 16 && i + j < size; j++)
        {
            char ch = isalnum(str[i + j]) ? str[i + j] : '.';
            if (i + j == size - 1)
            {
                sprintf(ptr, "%c", ch);
                ptr += 1;
            }
            else if (j == 15)
            {
                sprintf(ptr, "%c\n", ch);
                ptr += 2;
            }
            else
            {
                sprintf(ptr, "%c", ch);
                ptr++;
            }
        }

        i += j;
        line += 16;
    }
    return buffer;
}

char* hexdump(FILE* file)
{
    int size;
    char *buffer;

    fseek(file, 0, SEEK_END);

    size = ftell(file);
    buffer = (char *) malloc(sizeof(char) * size);

    fseek(file, 0, SEEK_SET);
    fread(buffer, 1, size, file);

    return _hexdump(buffer);
}
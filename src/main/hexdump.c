#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* hexdump(char* str)
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
            if (j == 15 && i + j < size - 1)
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
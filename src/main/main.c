#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_SEG_LENGTH 512

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <path_to_file>\n", argv[0]);
        return 0;
    }

    HEXDUMP *dump;
    FILE *file;
    int offset, filesize, n;
    char *buffer;

    offset = 0;
    file = fopen(argv[1], "r");
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = (char *) malloc(sizeof(char) * MAX_SEG_LENGTH);

    while (offset < filesize)
    {
        n = (filesize - offset) < MAX_SEG_LENGTH ? filesize - offset : MAX_SEG_LENGTH;

        if (fread(buffer, 1, n, file) != n)
        {
            fprintf(stderr, "Error reading from file.\n");
            return 0;
        }

        dump = hexdump(buffer, n, offset);
        offset += n;

        fwrite(dump->buffer, 1, dump->size, stdout);

        if (offset < filesize)
        {
            printf("\n*\n");
        }
    }

    return 0;
}
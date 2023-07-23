#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    Hexdump *dump;
    FILE *file;
    int offset, filesize, n;
    char *buffer;

    if ((file = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    offset = 0;
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char *) malloc(PARTITION_LENGTH);

    while (offset < filesize)
    {
        n = (filesize - offset) < PARTITION_LENGTH ? filesize - offset : PARTITION_LENGTH;

        if (fread(buffer, 1, n, file) != n)
        {
            fprintf(stderr, "Error reading from file.\n");
            return 1;
        }

        dump = hexdump(buffer, n, offset);
        fwrite(dump->buffer, 1, dump->size, stdout);

        offset += n;

        if (offset < filesize)
        {
            printf("\n*\n");
        }
    }

    fclose(file);

    return 0;
}
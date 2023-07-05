#include "hexdump.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <path_to_file>\n", argv[0]);
        return 0;
    }

    FILE *file;
    int filesize;
    char *filecontents, *result;

    file = fopen(argv[1], "r");

    fseek(file, 0, SEEK_END);

    filesize = ftell(file);
    filecontents = (char *) malloc(sizeof(char) * filesize);

    fseek(file, 0, SEEK_SET);
    fread(filecontents, 1, filesize, file);

    result = hexdump(filecontents, filesize);

    printf("%s\n", result);

    return 0;
}
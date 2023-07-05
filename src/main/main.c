#include "hexdump.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <path_to_file>\n", argv[0]);
        return 0;
    }

    FILE *file;
    char *buffer;

    file = fopen(argv[1], "r");
    buffer = hexdump(file);

    printf("%s\n", buffer);

    return 0;
}
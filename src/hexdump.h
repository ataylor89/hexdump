#define PARTITION_LENGTH 512

typedef struct
{
    char *buffer;
    int size;
} Hexdump;

Hexdump* hexdump(char* str, int size, int line_pos);
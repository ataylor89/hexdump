typedef struct
{
    char *buffer;
    int size;
} HEXDUMP;

HEXDUMP* hexdump(char* str, int size, int line_pos);
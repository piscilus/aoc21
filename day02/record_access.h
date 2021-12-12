#define DIRECTION_MAX (10)

typedef struct
{
    char d[DIRECTION_MAX]; /* direction */
    unsigned int v; /* velocity */
} command_t;

int read_data_record(char* fname, command_t commands[], int max);

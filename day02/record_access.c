#include "record_access.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int read_data_record(char* fname, command_t commands[], int max)
{
    int i = 0;

    assert( commands != NULL );
    assert( max > 0 );

    FILE* fp = fopen(fname, "r");

    if (!fp)
    {
        return 0;
    }

    while ( EOF != fscanf(fp, "%s %d", &commands[i].d[0], &commands[i].v))
    {
        if ( i >= max)
        {
            i = -1;
            break;
        }
        i++;
    }

    fclose(fp);

    return i;
}

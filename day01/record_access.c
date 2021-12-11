#include "record_access.h"

#include <stdlib.h>
#include <stdio.h>
// #include <string.h>
#include <assert.h>

int read_data_record(char* fname, unsigned int samples[], int n)
{
    int i = 0;

    assert( samples != NULL );
    assert( n > 0 );

    FILE* fp = fopen(fname, "r");

    if (!fp)
    {
        return 0;
    }

    while ( EOF != fscanf(fp, "%d", &samples[i]))
    {
        if ( i >= n)
        {
            i = -1;
            break;
        }
        i++;
    }

    fclose(fp);

    return i;
}

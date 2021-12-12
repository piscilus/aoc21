/**
 * \file record_access.c
 *
 * \copyright (C) 2021 piscilus
 *
 * \brief Module to access the data record.
 */

/*---- Includes --------------------------------------------------------------*/
#include "record_access.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


/*---- Local macro definitions -----------------------------------------------*/


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int read_data_record(char* fname, diagnostic_t diagnostics[], int n)
{
    int i = 0; /* count number of records */

    assert( diagnostics != NULL );

    FILE* fp = fopen(fname, "r");

    if (!fp)
    {
        return 0;
    }

    while ( EOF != fscanf(fp, "%s", &diagnostics[i].raw[0]))
    {
        if ( i >= n)
        {
            i = -1;
            break;
        }

        diagnostics[i].raw_len = strlen(diagnostics[i].raw);
        for ( size_t n = 0; n < diagnostics[i].raw_len; n++ )
        {
            if ( diagnostics[i].raw[n] == '1')
            {
                diagnostics[i].data |= (1U << (diagnostics[i].raw_len-1-n));
            }
        }

        i++;
    }

    fclose(fp);

    return i;
}


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

/**
 * \file record_access.c
 *
 * \copyright (C) 2021 piscilus
 *
 * \brief Module to access the data record.
 */

/*---- Includes --------------------------------------------------------------*/
#include "record_access.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/*---- Local macro definitions -----------------------------------------------*/


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
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

    while ( EOF != fscanf(fp, "%u", &samples[i]))
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


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

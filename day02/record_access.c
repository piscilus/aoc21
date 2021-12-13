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

    while ( EOF != fscanf(fp, "%s %u", &commands[i].d[0], &commands[i].v))
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


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

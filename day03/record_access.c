/**
 * \file record_access.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
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
int read_data_record(char* fname, diagnostic_t* diagnostics)
{
    assert( diagnostics != NULL );

    diagnostics->data_len = 0U;
    diagnostics->num_data = 0U;

    FILE* fp = fopen(fname, "r");

    if ( !fp )
    {
        fprintf(stderr, "Could not open file!");
        return EXIT_FAILURE;
    }

    while ( EOF != fscanf(fp, "%s\n", &diagnostics->data[diagnostics->num_data].raw[0]) )
    {
        uint32_t len;

        if ( diagnostics->num_data > RECORD_MAX_SIZE ) /* end of buffer size reached */
        {
            fprintf(stderr, "More than %u records found. Please increase buffer size.", RECORD_MAX_SIZE);
            fclose(fp);
            return EXIT_FAILURE;
        }

        len = (uint32_t) strlen(diagnostics->data[diagnostics->num_data].raw);

        if ( (len == 0U) || (len > RAW_DATA_MAX_LEN) ) /* empty raw data or too long */
        {
            fprintf(stderr, "Length %u of data in line %u is 0 or exceeds limit of %d", len, diagnostics->num_data, RAW_DATA_MAX_LEN);
            fclose(fp);
            return EXIT_FAILURE;
        }

        if (diagnostics->data_len == 0U) /* set len to length of first line (length reference) */
        {
            diagnostics->data_len = len;
        }
        else if ( diagnostics->data_len != len) /* any further line must have same length */
        {
            fprintf(stderr, "Length %u of data in line does not match with length of previous line(s) %u", len, diagnostics->data_len);
            fclose(fp);
            return EXIT_FAILURE;
        }

        for ( size_t n = 0; n < len; n++ )
        {
            if ( diagnostics->data[diagnostics->num_data].raw[n] == '1')
            {
                diagnostics->data[diagnostics->num_data].num |= (1U << (len-1-n));
            }
        }

        diagnostics->num_data++;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

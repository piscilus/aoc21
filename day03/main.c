/**
 * \file main.c
 *
 * \copyright (C) 2021 piscilus
 *
 * \brief Main program for advent of code 2021 day 3.
 */

/*---- Includes --------------------------------------------------------------*/
#include "record_access.h"

#include <stdio.h>
#include <stdlib.h>


/*---- Local macro definitions -----------------------------------------------*/
#define RECORD_MAX_SIZE (2000)


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    int n;

    unsigned int gamma_rate = 0;
    unsigned int epsilon_rate = 0;
    unsigned int power_consumption = 0;

    diagnostic_t diag[RECORD_MAX_SIZE] = { 0 };

    printf("Advent of Code 2021 - Day 3: Binary Diagnostic\n\n");

        if ( argc != 2)
    {
        printf("Please provide data record file name.");
        return EXIT_FAILURE;
    }

    n = read_data_record(argv[1], diag, RECORD_MAX_SIZE);
    if ( n == 0 )
    {
        printf("Reading data record failed");
        return EXIT_FAILURE;
    }
    if ( n < 0)
    {
        printf("Buffer too small, more data available");
        return EXIT_FAILURE;
    }

    for ( int b = 0; b < RAW_DATA_MAX_LEN; b++)
    {
        int ones = 0;
        int zeros = 0;
        for (int i = 0; i < n; i++)
        {
            if (b < diag[i].raw_len)
            {
                if ( (diag[i].data & (1U<<b)) != 0U)
                {
                    ones++;
                }
                else
                {
                    zeros++;
                }
            }
        }
        if ( ones > zeros)
        {
            gamma_rate |= (1<<b);
        }
        if ( zeros > ones )
        {
            epsilon_rate |= (1<<b);
        }
    }

    printf("\tGamma rate: %d\n", gamma_rate);
    printf("\tEpsilon rate: %d\n", epsilon_rate);

    power_consumption = (gamma_rate * epsilon_rate);
    printf("\tPower consumption: %d\n", power_consumption);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

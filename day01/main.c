/**
 * \file main.c
 *
 * \copyright (C) 2021 piscilus
 *
 * \brief Main program for advent of code 2021 day 2.
 */

/*---- Includes --------------------------------------------------------------*/
#include "record_access.h"

#include <stdio.h>
#include <stdlib.h>


/*---- Local macro definitions -----------------------------------------------*/
#define SAMPLE_BUFFER_SIZE (2000)


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/
int algorithm_part1(unsigned int samples[], int n);
int algorithm_part2(unsigned int samples[], int n);


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    int count = 0;
    unsigned int samples[SAMPLE_BUFFER_SIZE] = { 0 };
    int n;

    printf("Advent of Code 2021 - Day 1: Sonar Sweep\n\n");

    if ( argc != 2)
    {
        printf("Please provide data record file name.");
        return EXIT_FAILURE;
    }

    n = read_data_record(argv[1], samples, SAMPLE_BUFFER_SIZE);
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

    printf("Part 1:\n");
    count = algorithm_part1(samples, n);
    printf("result: %d\n", count);

    printf("Part 2:\n");
    count = algorithm_part2(samples, n);
    printf("result: %d\n", count);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
int algorithm_part1(unsigned int samples[], int n)
{
    int c = 0;

    for ( int i = 1; i < n; i++ )
    {
        if ( samples[i] > samples[i-1])
        {
            c++;
        }
    }
    return c;
}

int algorithm_part2(unsigned int samples[], int n)
{
    int c = 0;
    unsigned int prev_window = samples[0] + samples[1] + samples[2];

    for ( int i = 2; i < n-1; i++ )
    {
        unsigned int window = samples[i-1] + samples[i] + samples[i+1];
        if (window > prev_window)
        {
            c++;
        }
        prev_window = window;
    }

    return c;
}



/*----------------------------------------------------------- END OF FILE ----*/

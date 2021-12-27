/**
 * \file main.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 1.
 */

/*---- Includes --------------------------------------------------------------*/
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
    unsigned int samples[SAMPLE_BUFFER_SIZE] = { 0 };
    int num_samples = 0;
    int result = 0;

    printf("Advent of Code 2021 - Day 1: Sonar Sweep\n\n");

    if ( argc != 2 )
    {
        fprintf(stderr, "Please provide data record file name.");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(argv[1], "r");

    if ( !fp )
    {
        fprintf(stderr, "Could not open file!");
        exit(EXIT_FAILURE);
    }

    while ( EOF != fscanf(fp, "%u\n", &samples[num_samples]) )
    {
        if ( num_samples >= SAMPLE_BUFFER_SIZE )
        {
            fprintf(stderr, "Buffer overflow, too much data!");
            exit(EXIT_FAILURE);
        }
        num_samples++;
    }

    fclose(fp);

    printf("Part 1:\n");
    result = algorithm_part1(samples, num_samples);
    printf("\tresult = %d\n", result);

    printf("Part 2:\n");
    result = algorithm_part2(samples, num_samples);
    printf("\tresult = %d\n", result);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
int algorithm_part1(unsigned int samples[], int n)
{
    int c = 0;

    for ( int i = 1; i < n; i++ )
    {
        if ( samples[i] > samples[i - 1] )
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

    for ( int i = 2; i < (n - 1); i++ )
    {
        unsigned int window = samples[i - 1] + samples[i] + samples[i + 1];
        if ( window > prev_window )
        {
            c++;
        }
        prev_window = window;
    }

    return c;
}



/*----------------------------------------------------------- END OF FILE ----*/

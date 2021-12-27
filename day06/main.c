/**
 * \file main.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 6.
 */

/*---- Includes --------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


/*---- Local macro definitions -----------------------------------------------*/
#define STAGES (9)


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/
static void print_population( uint64_t f[], int d );


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    uint64_t fishes_per_stage[STAGES] = {0};

    printf("Advent of Code 2021 - Day 6: Lanternfish \n\n");

    if ( argc != 3)
    {
        fprintf(stderr, "Please provide data record file name and number of days.");
        exit(EXIT_FAILURE);
    }

    int days = atoi(argv[2]);

    FILE* fp = fopen(argv[1], "r");

    if ( !fp )
    {
        fprintf(stderr, "Could not open file!");
        exit(EXIT_FAILURE);
    }

    int a;
    char c;
    while ( EOF != fscanf(fp, "%d%c", &a, &c) )
    {
        if ( a >= STAGES )
        {
            fprintf(stderr, "invalid data %d", a);
            exit(EXIT_FAILURE);
        }
        fishes_per_stage[a]++;
        if ( c == '\n' )
            break;
    }

    fclose(fp);

    /* initial population: */
    print_population(fishes_per_stage, 0);

    for ( int d = 0; d < days; d++ )
    {
        uint64_t tmp = fishes_per_stage[0];
        for ( int s = 0; s < STAGES; s++ )
        {
            if ( (s + 1) < STAGES )
            {
                fishes_per_stage[s] = fishes_per_stage[s + 1];
            }
        }
        fishes_per_stage[6] += tmp;
        fishes_per_stage[8] = tmp;
        print_population(fishes_per_stage, (d + 1));
    }

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
static void print_population( uint64_t f[], int d )
{
    printf("Day %03d: ", d);
    uint64_t total = 0;
    for ( int s = 0; s < STAGES; s++ )
    {
        printf("\t%llu", f[s]);
        total += f[s];
    }
    printf("\ttotal = %llu\n", total);
}


/*----------------------------------------------------------- END OF FILE ----*/

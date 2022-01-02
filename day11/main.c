/**
 * \file main.c
 *
 * \copyright (C) 2022 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 11.
 */

/*---- Includes --------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>


/*---- Local macro definitions -----------------------------------------------*/
#define GRID_ROWS (10)
#define GRID_COLS (10)
#define NUM_STEPS (100) /* part 1 */
#define MAX_ENERGY_LEVEL (9U)


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    unsigned int octopuses[GRID_ROWS][GRID_COLS] = { 0 };

    printf("Advent of Code 2021 - Day 9: Smoke Basin\n\n");

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

    int c;
    int row = 0;
    int col = 0;
    while ( (c = fgetc(fp)) != EOF )
    {
        if ( row > GRID_ROWS )
        {
            fprintf(stderr, "Too many rows (max = %d)!", GRID_ROWS);
            exit(EXIT_FAILURE);
        }
        if ( col > GRID_COLS )
        {
            fprintf(stderr, "Too many columns (max = %d)!", GRID_COLS);
            exit(EXIT_FAILURE);
        }
        if ( c == '\n' )
        {
            col = 0;
            row++;
        }
        else
        {
            octopuses[row][col] = atoi((const char*)&c);
            col++;
        }
    }

    int step = 0;
    int num_flashes = 0;
    int running = 1;
    while ( running )
    {
        int flashing;
        int prev_num_flashes = num_flashes;

        /* increase energy level */
        for ( int row = 0U; row < GRID_ROWS; row++ )
        {
            for ( int col = 0U; col < GRID_COLS; col++ )
            {
                octopuses[row][col]++;
            }
        }

        /* calculate flashes */
        do
        {
            flashing = 0;
            for ( int row = 0; row < GRID_ROWS; row++ )
            {
                for ( int col = 0; col < GRID_COLS; col++ )
                {
                    if ( octopuses[row][col] > MAX_ENERGY_LEVEL )
                    {
                        octopuses[row][col] = 0U; /* reset energy level */
                        flashing = 1; /* at least one flash, do another loop */
                        num_flashes++;
                        /* increase energy level of neighbors: */
                        for ( int y = row - 1; y <= row + 1; y++ )
                        {
                            for ( int x = col - 1; x <= col + 1; x++ )
                            {
                                if ( (y >= 0) && (x >= 0) && (y < GRID_ROWS) && (x < GRID_COLS) )
                                {
                                    /* increase only octopuses that haven't already flashed: */
                                    if ( octopuses[y][x] > 0U )
                                    {
                                        octopuses[y][x]++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } while ( flashing );

        step++;
        if ( step == NUM_STEPS )
        {
            printf("Part 1: %d flashes occured after %d steps.\n", num_flashes, NUM_STEPS);
        }

        if ( (num_flashes - prev_num_flashes) >= (GRID_ROWS * GRID_COLS) )
        {
            printf("Part 2: All octopuses flashed during step %d!\n", step);
            running = 0;
        }
    }

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

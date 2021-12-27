/**
 * \file main.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 5.
 */

/*---- Includes --------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/*---- Local macro definitions -----------------------------------------------*/
#define MAX_LINES (500)
#define DIAGRAM_SIZE (1000)


/*---- Local type definitions ------------------------------------------------*/
typedef struct coords
{
    int x1;
    int y1;
    int x2;
    int y2;
} coords_t;


/*---- Local function prototypes ---------------------------------------------*/


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    coords_t lines[MAX_LINES] = {0};
    static int diagram[DIAGRAM_SIZE][DIAGRAM_SIZE] = {0};
    int result = 0;

    printf("Advent of Code 2021 - Day 5: Hydrothermal Venture\n\n");

    if ( argc != 2 )
    {
        fprintf(stderr, "Please provide data record file name and part selection.");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(argv[1], "r");

    if ( !fp )
    {
        fprintf(stderr, "Could not open file!");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while ( EOF != fscanf(fp, "%d,%d -> %d,%d\n", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2) )
    {
        if ( i >= MAX_LINES )
        {
            fprintf(stderr, "Buffer overflow, too much data!");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    for ( int n = 0; n < i; n++ )
    {
        // printf("%d: %d,%d -> %d,%d\n", n, lines[n].x1, lines[n].y1, lines[n].x2, lines[n].y2);
        if ( lines[n].x1 == lines[n].x2 )
        {
            // printf("vertical\n");
            if ( lines[n].y1 > lines[n].y2 )
            {
                // printf("y1>y2\n");
                for ( int j=lines[n].y2; j<=lines[n].y1; j++ )
                    diagram[j][lines[n].x1]++;
            }
            else
            {
                // printf("y1<=y2\n");
                for ( int j=lines[n].y1; j<=lines[n].y2; j++ )
                    diagram[j][lines[n].x1]++;
            }
        }
        else if ( lines[n].y1 == lines[n].y2 )
        {
            // printf("horizontal\n");
            if ( lines[n].x1 > lines[n].x2 )
            {
                // printf("x1>x2\n");
                for ( int j=lines[n].x2; j<=lines[n].x1; j++ )
                    diagram[lines[n].y1][j]++;
            }
            else
            {
                // printf("x1<=x2\n");
                for ( int j=lines[n].x1; j<=lines[n].x2; j++ )
                    diagram[lines[n].y1][j]++;
            }
        }
        else
        {
            // nop
            ;
        }
    }

    for ( int y = 0; y < DIAGRAM_SIZE; y++ ) //rows
    {
        for ( int x = 0; x < DIAGRAM_SIZE; x++ ) //cols
        {
            // printf("%d", diagram[y][x]);
            if ( diagram[y][x] >= 2 )
                result++;
        }
        // printf("\n");
    }

    printf("result: %d\n", result);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

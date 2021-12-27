/**
 * \file main.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 2.
 */

/*---- Includes --------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---- Local macro definitions -----------------------------------------------*/
#define COMMAND_BUFFER_SIZE (2000)
#define DIRECTION_MAX (10)


/*---- Local type definitions ------------------------------------------------*/
typedef struct command
{
    char d[DIRECTION_MAX];  /* direction */
    unsigned int v;         /* velocity */
} command_t;


/*---- Local function prototypes ---------------------------------------------*/
unsigned int dive_part1(command_t commands[], int n);
unsigned int dive_part2(command_t commands[], int n);


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    command_t commands[COMMAND_BUFFER_SIZE] = { 0 };
    int num_cmds = 0;
    unsigned int result;

    printf("Advent of Code 2021 - Day 2: Dive!\n\n");

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

    while ( EOF != fscanf(fp, "%s %u\n", &commands[num_cmds].d[0], &commands[num_cmds].v) )
    {
        if ( num_cmds >= COMMAND_BUFFER_SIZE )
        {
            fprintf(stderr, "Buffer overflow, too much data!");
            exit(EXIT_FAILURE);
        }
        num_cmds++;
    }

    fclose(fp);

    printf("Part 1:\n");
    result = dive_part1(commands, num_cmds);
    printf("\tresult = %d\n\n", result);

    printf("Part 2:\n");
    result = dive_part2(commands, num_cmds);
    printf("\tresult = %d\n", result);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
unsigned int dive_part1(command_t commands[], int n)
{
    struct
    {
        unsigned int h; /* horizontal */
        unsigned int d; /* depth */
    } position = {0U, 0U};

    for ( int i = 0; i < n; i++ )
    {
        if ( strcmp("forward", commands[i].d) == 0 )
        {
            position.h += commands[i].v;
        }
        else if ( strcmp("down", commands[i].d) == 0 )
        {
            position.d += commands[i].v;
        }
        else if ( strcmp("up", commands[i].d) == 0 )
        {
            position.d -= commands[i].v;
        }
        else
        {
             return EXIT_FAILURE;
        }
    }

    printf("\tpos: h=%d, d=%d\n", position.h, position.d);

    return (position.h * position.d);
}

unsigned int dive_part2(command_t commands[], int n)
{
    struct
    {
        unsigned int h; /* horizontal */
        unsigned int d; /* depth */
        unsigned int a; /* aim */
    } position = {0U, 0U, 0U};

    for ( int i = 0; i < n; i++ )
    {
        if ( strcmp("forward", commands[i].d) == 0 )
        {
            position.h += commands[i].v;
            position.d += (position.a * commands[i].v);
        }
        else if ( strcmp("down", commands[i].d) == 0 )
        {
            position.a += commands[i].v;
        }
        else if ( strcmp("up", commands[i].d) == 0 )
        {
            if ( position.a < commands[i].v )
                return EXIT_FAILURE;
            position.a -= commands[i].v;
        }
        else
        {
             return EXIT_FAILURE;
        }
    }

    printf("\tpos: h=%d, d=%d\n", position.h, position.d);

    return (position.h * position.d);
}



/*----------------------------------------------------------- END OF FILE ----*/

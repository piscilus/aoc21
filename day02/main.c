#include "record_access.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE_BUFFER_SIZE (2000)

unsigned int dive_part1(command_t commands[], int n);
unsigned int dive_part2(command_t commands[], int n);

int main ( int argc, char *argv[] )
{
    unsigned int result;
    int n;
    command_t commands[SAMPLE_BUFFER_SIZE] = {0};

    printf("Advent of Code - Day 2\n\n");

    if ( argc != 2)
    {
        printf("Please provide data record file name.");
        return EXIT_FAILURE;
    }

    n = read_data_record(argv[1], commands, SAMPLE_BUFFER_SIZE);
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
    result = dive_part1(commands, n);
    printf("result: %d\n\n", result);

    printf("Part 2:\n");
    result = dive_part2(commands, n);
    printf("result: %d\n", result);

    return EXIT_SUCCESS;
}

unsigned int dive_part1(command_t commands[], int n)
{
    struct
    {
        unsigned int h; /* horizontal */
        unsigned int d; /* depth */
    } position = {0U, 0U};

    for (int i = 0; i < n; i++)
    {
        if (strcmp("forward", commands[i].d) == 0)
        {
            position.h += commands[i].v;
        }
        else if (strcmp("down", commands[i].d) == 0)
        {
            position.d += commands[i].v;
        }
        else if (strcmp("up", commands[i].d) == 0)
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

    for (int i = 0; i < n; i++)
    {
        if (strcmp("forward", commands[i].d) == 0)
        {
            position.h += commands[i].v;
            position.d += (position.a * commands[i].v);
        }
        else if (strcmp("down", commands[i].d) == 0)
        {
            position.a += commands[i].v;
        }
        else if (strcmp("up", commands[i].d) == 0)
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


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "record_access.h"

#define SAMPLE_RECORD ("data_contest.txt")
#define SAMPLE_BUFFER_SIZE (2000)

int algorithm_part1(unsigned int samples[], int n);
int algorithm_part2(unsigned int samples[], int n);

int main (void)
{
    int count = 0;
    unsigned int samples[SAMPLE_BUFFER_SIZE] = { 0 };
    int n;

    printf("AOC - Day 1\n\n");

    n = read_data_record(SAMPLE_RECORD, samples, SAMPLE_BUFFER_SIZE);
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

    for ( int i = 2; i < n-1U; i++ )
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


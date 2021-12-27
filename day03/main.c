/**
 * \file main.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 3.
 */

/*---- Includes --------------------------------------------------------------*/
#include "record_access.h"
#include "data.h"

#include <stdio.h>
#include <stdlib.h>


/*---- Local macro definitions -----------------------------------------------*/


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/
static unsigned int part1_power_consumption(diagnostic_t* diag);
static unsigned int part2_life_support(diagnostic_t* diag);
static analysis_t check_bit(diagnostic_t* diag, uint32_t bit);
static int delete_zeros(uint32_t mask, uint32_t value);
static int delete_ones(uint32_t mask, uint32_t value);
static unsigned int oxygen_generator_rating(diagnostic_t* diag);
static unsigned int co2_scrubber_rating(diagnostic_t* diag);


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    unsigned int result = 0;
    diagnostic_t diag = { 0 };

    printf("Advent of Code 2021 - Day 3: Binary Diagnostic\n\n");

    if ( argc != 2 )
    {
        fprintf(stderr, "Please provide data record file name.");
        exit(EXIT_FAILURE);
    }

    if ( EXIT_FAILURE == read_data_record(argv[1], &diag) )
    {
        exit(EXIT_FAILURE);
    }

    printf("Part1\n");
    result = part1_power_consumption(&diag);
    printf("\tPower consumption: %d\n\n", result);

    printf("Part2\n");
    result = part2_life_support(&diag);
    printf("\tLife support rating: %d\n\n", result);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
static unsigned int part1_power_consumption(diagnostic_t* diag)
{
    analysis_t analysis;
    unsigned int gamma_rate = 0U;
    unsigned int epsilon_rate = 0U;

    for ( uint32_t b = 0U; b < diag->data_len; b++ )
    {
        analysis = check_bit(diag, b);

        if ( analysis.ones > analysis.zeros )
        {
            gamma_rate |= (1<<b);
        }
        if ( analysis.zeros > analysis.ones )
        {
            epsilon_rate |= (1<<b);
        }
    }

    printf("\tGamma rate: %d\n", gamma_rate);
    printf("\tEpsilon rate: %d\n", epsilon_rate);

    return (gamma_rate * epsilon_rate);
}

static unsigned int part2_life_support(diagnostic_t* diag)
{

    uint32_t Oxygen_generator_rating = 0U;
    uint32_t CO2_scrubber_rating = 0x1FU;

    Oxygen_generator_rating = oxygen_generator_rating(diag);
    CO2_scrubber_rating = co2_scrubber_rating(diag);

    printf("\tOxygen_generator_rating %x %u\n", Oxygen_generator_rating, Oxygen_generator_rating);
    printf("\tCO2_scrubber_rating %x %u\n", CO2_scrubber_rating, CO2_scrubber_rating);

    return (Oxygen_generator_rating * CO2_scrubber_rating);
}

static unsigned int oxygen_generator_rating(diagnostic_t* diag)
{
    analysis_t analysis;
    node_t* l1_head = NULL;

    for ( uint32_t i = diag->num_data; i-- > 0U; )
    {
        push(&l1_head, diag->data[i].num);
    }

    uint32_t Oxygen_generator_rating = 0U;

    for ( uint32_t bit = diag->data_len; bit-- > 0U; )
    {
        analysis = list_check_bit(l1_head, bit);

        if ( analysis.ones >= analysis.zeros )
        {
            do
            {
                if ( count(l1_head) == 1 )
                {
                    (void) getFirst(l1_head, &Oxygen_generator_rating);
                    break;
                }
            }
            while ( EXIT_SUCCESS == deleteNode(&l1_head, bit, delete_zeros) );
        }
        else
        {
            do
            {
                if ( count(l1_head) == 1 )
                {
                    (void) getFirst(l1_head, &Oxygen_generator_rating);
                    break;
                }
            }
            while ( EXIT_SUCCESS == deleteNode(&l1_head, bit, delete_ones) );
        }
    }

    return Oxygen_generator_rating;
}

static unsigned int co2_scrubber_rating(diagnostic_t* diag)
{
    analysis_t analysis;
    node_t* head = NULL;

    for ( uint32_t i = 0; i < diag->num_data; i++ )
    {
        append(&head, diag->data[i].num);
    }
    uint32_t CO2_scrubber_rating = 0U;

    for ( uint32_t bit = diag->data_len; bit-- > 0U; )
    {
        analysis = list_check_bit(head, bit);
        if ( analysis.ones < analysis.zeros )
        {
            do
            {
                if ( count(head) == 1 )
                {
                    (void) getFirst(head, &CO2_scrubber_rating);
                    break;
                }
            }
            while ( EXIT_SUCCESS == deleteNode(&head, bit, delete_zeros) );
        }
        else
        {
            do
            {
                if ( count(head) == 1 )
                {
                    (void) getFirst(head, &CO2_scrubber_rating);
                    break;
                }
            }
            while ( EXIT_SUCCESS == deleteNode(&head, bit, delete_ones) );
        }
    }

    return CO2_scrubber_rating;
}

static analysis_t check_bit(diagnostic_t* diag, uint32_t bit)
{
    analysis_t analysis = { 0 };

    for ( uint32_t i = 0U; i < diag->num_data; i++ )
    {
        if ( (diag->data[i].num & (1U<<bit)) != 0U )
        {
            analysis.ones++;
        }
        else
        {
            analysis.zeros++;
        }
    }

    return analysis;
}

static int delete_zeros(uint32_t bit, uint32_t value)
{
    uint32_t mask = (1U << bit);

    if ( (value & mask) != 0U ) /* this is a one, keep it */
    {
        return 0;
    }
    else
    {
        return 1;               /* this is a zero, delete it */
    }
}

static int delete_ones(uint32_t bit, uint32_t value)
{
    uint32_t mask = (1U << bit);

    if ( (value & mask) != 0U ) /* this is a one, delete it */
    {
        return 1;
    }
    else
    {
        return 0;           /* this is a zero, keep it */
    }
}


/*----------------------------------------------------------- END OF FILE ----*/

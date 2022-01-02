/**
 * \file main.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Main program for advent of code 2021 day 21.
 */

/*---- Includes --------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>


/*---- Local macro definitions -----------------------------------------------*/
#define NUM_PLAYERS (2U)
#define TRACK_MIN   (1U)
#define TRACK_MAX   (10U)
#define DIE_MAX     (100U)
#define WINNING_SCORE (1000U)
#define ROLLS_PER_PLAYER (3U)


/*---- Local type definitions ------------------------------------------------*/
typedef struct player
{
    unsigned int space; /* position on the track */
    unsigned int score; /* game score */
} player_t;


/*---- Local function prototypes ---------------------------------------------*/
unsigned int move( unsigned int position, unsigned int steps );


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    player_t players[NUM_PLAYERS] = { 0 };

    printf("Advent of Code 2021 - Day 21: Dirac Dice\n\n");

    if ( argc != (NUM_PLAYERS + 1) )
    {
        fprintf(stderr, "Please provide start positions per player.");
        exit(EXIT_FAILURE);
    }

    for ( unsigned int p = 0U; p < NUM_PLAYERS; p++ )
    {
        players[p].space = (unsigned int) atoi(argv[p + 1U]);
        if ( (players[p].space < TRACK_MIN) || (players[p].space > TRACK_MAX) )
        {
            fprintf(stderr, "Invalid start position %d for player %u.", players[p].space, p + 1U);
            exit(EXIT_FAILURE);
        }
        printf("\tPlayer %u starting on space %u.\n", p + 1U, players[p].space);
    }

    unsigned int die = 0U;
    unsigned int num_die_rolls = 0U;
    unsigned int winner_id = 0U;
    unsigned int loser_id = 0U;

    int running = 1;
    while ( running )
    {
        for ( unsigned int p = 0U; p < NUM_PLAYERS; p++ )
        {
            for ( unsigned int r = 0U; r < ROLLS_PER_PLAYER; r++ )
            {
                die++;
                if ( die > DIE_MAX )
                    die = 1U;
                num_die_rolls++;
                players[p].space = move(players[p].space, die);
            }
            players[p].score += players[p].space;
            if ( players[p].score >= WINNING_SCORE )
            {
                winner_id = p;
                loser_id = (winner_id + 1U) % NUM_PLAYERS;
                running = 0; /* stop the game */
                break;
            }
        }
    }
    printf("\nWe have a winner after %d times rolling the die:\n", num_die_rolls);

    printf("\tPlayer %u won the game with score of %u!\n", winner_id + 1U, players[winner_id].score);
    printf("\tPlayer %u lost the game with score of %u!\n", loser_id + 1U, players[loser_id].score);

    printf("\nPart 1 result is %u\n", num_die_rolls * players[loser_id].score);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
unsigned int move( unsigned int position, unsigned int steps )
{
    unsigned int new_pos = position + steps;

    while ( new_pos > TRACK_MAX )
    {
        new_pos = (new_pos % (TRACK_MAX + 1U)) + (new_pos / (TRACK_MAX + 1U));
    }

    return new_pos;
}


/*----------------------------------------------------------- END OF FILE ----*/

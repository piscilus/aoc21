/**
 * \file main.c
 *
 * \copyright (C) 2021 piscilus
 *
 * \brief Main program for advent of code 2021 day 4.
 */

/*---- Includes --------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>


/*---- Local macro definitions -----------------------------------------------*/
#define NUMBERS_MAX (100) /* size of buffer for numbers to be drawn */
#define PLAYERS_MAX (100) /* maximum number of players */
#define BOARD_SIZE (5)    /* size of the board (rows and columns) */


/*---- Local type definitions ------------------------------------------------*/
typedef struct board
{
    int num[BOARD_SIZE][BOARD_SIZE];  /* numbers on the player board */
    int mark[BOARD_SIZE][BOARD_SIZE]; /* marks on the player board */
} board_t;


/*---- Local function prototypes ---------------------------------------------*/
void print_board(int data[BOARD_SIZE][BOARD_SIZE]);


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
int main ( int argc, char *argv[] )
{
    int numbers[NUMBERS_MAX] = {0};
    board_t boards[PLAYERS_MAX] = {0};
    int number_count = 0;

    printf("Advent of Code 2021 - Day 4: Binary Diagnostic\n\n");

    if ( argc != 2)
    {
        fprintf(stderr, "Please provide data record file name.");
        exit(EXIT_FAILURE);
    }

    FILE* fp = fopen(argv[1], "r");

    if (!fp)
    {
        printf("Could not open file!");
        return EXIT_FAILURE;
    }

    char c = '\0';
    while ( EOF != fscanf(fp, "%d%c", &numbers[++number_count], &c))
    {
        if (c == '\n')
        {
            break;
        }
        if (number_count >= NUMBERS_MAX)
        {
            printf("Number buffer exceeded!");
            return EXIT_FAILURE;
        }
    }

#ifndef NDEBUG
    printf("%d", number_count);
#endif

    size_t players = 0U;
    size_t row = 0U;
    size_t col = 0U;
    while ( EOF != fscanf(fp, "%d", &boards[players].num[row][col]))
    {
        col++;
        if ( col == BOARD_SIZE)
        {
            col = 0;
            row++;
        }
        if ( row == BOARD_SIZE)
        {
            row = 0;
#ifndef NDEBUG
            printf("\nBoard player %llu:\n", (players + 1U));
            print_board(boards[players].num);
#endif
            players++;
            if (players > PLAYERS_MAX)
            {
                printf("Too many players!");
                return EXIT_FAILURE;
            }
        }
    }
    printf("\n");

    size_t idx_num;
    size_t winner = 0U;
    for (idx_num = 0U; idx_num < sizeof(numbers)/sizeof(int); idx_num++)
    {
        printf("Draw number: %u\n", numbers[idx_num]);
        for (size_t p = 0U; p < players; p++)
        {
            for (size_t r = 0U; r < BOARD_SIZE; r++)
            {
                for (size_t c = 0U; c < BOARD_SIZE; c++)
                {
                    if (numbers[idx_num] == boards[p].num[r][c])
                    {
                        boards[p].mark[r][c] = 1;
                    }
                }
            }
            /* check for a winner: */
            for (size_t r = 0U; r < BOARD_SIZE; r++) /* check cols */
            {
                int col = 0;
                for (size_t c = 0U; c < BOARD_SIZE; c++)
                {
                    if (boards[p].mark[r][c])
                    {
                        col++;
                        if (col == BOARD_SIZE)
                        {
                            winner = p;
                            goto EndOfGame;
                        }
                    }
                }
            }
            for (size_t c = 0U; c < BOARD_SIZE; c++) /* check rows */
            {
                int row = 0;
                for (size_t r = 0U; r < BOARD_SIZE; r++)
                {
                    if (boards[p].mark[r][c])
                    {
                        row++;
                        if (row == BOARD_SIZE)
                        {
                            winner = p;
                            goto EndOfGame;
                        }
                    }
                }
            }
        }
    }

    EndOfGame:
    printf("\nWinner is player %llu\n\n", winner+1);
    print_board(boards[winner].mark);
    printf("\n");

    int result = 0;
    for (size_t r = 0U; r < BOARD_SIZE; r++)
    {
        for (size_t c = 0U; c < BOARD_SIZE; c++)
        {
            if (0 == boards[winner].mark[r][c])
            {
                result += boards[winner].num[r][c];
            }
        }
    }

    result *= numbers[idx_num];
    printf("\nFinal result: %d", result);

    return EXIT_SUCCESS;
}


/*---- Local functions -------------------------------------------------------*/
void print_board(int data[BOARD_SIZE][BOARD_SIZE])
{
    for (size_t r = 0U; r < BOARD_SIZE; r++)
    {
        for (size_t c = 0U; c < BOARD_SIZE; c++)
        {
            printf("%2d ", data[r][c]);
        }
        printf("\n");
    }
}


/*----------------------------------------------------------- END OF FILE ----*/

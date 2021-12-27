/**
 * \file data.c
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Module for data analysis.
 */

/*---- Includes --------------------------------------------------------------*/
#include "data.h"

#include <stdlib.h>
#include <stdio.h>


/*---- Local macro definitions -----------------------------------------------*/


/*---- Local type definitions ------------------------------------------------*/


/*---- Local function prototypes ---------------------------------------------*/


/*---- Global constants ------------------------------------------------------*/


/*---- Global data -----------------------------------------------------------*/


/*---- Local constants -------------------------------------------------------*/


/*---- Local data ------------------------------------------------------------*/


/*---- Exported functions ----------------------------------------------------*/
void push(node_t** head, uint32_t data)
{
    node_t* new_node = (node_t *) malloc(sizeof(node_t));
    if ( new_node == NULL )
    {
        fprintf(stderr,"malloc() failed in file %s at line # %d", __FILE__,__LINE__);
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;

    return;
}

node_t* list_clone(node_t* head)
{
    node_t* current = head;
    node_t* tail;
    node_t dummy;

    dummy.next = NULL;
    tail = &dummy;

    while ( current != NULL )
    {
        push(&(tail->next), current->data);
        tail = tail->next;
        current = current->next;
    }

    return dummy.next;
}

void append(node_t** head, uint32_t data)
{
    node_t *newNode = (node_t*) malloc(sizeof(node_t));

    if ( newNode == NULL )
    {
        fprintf(stderr, "Unable to allocate memory for new node.");
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if ( *head == NULL )
    {
        *head = newNode;
    }
    else
    {
        node_t *current = *head;
        while ( current->next != NULL )
        {
            current = current->next;
        }
        current->next = newNode;
    }

    return;
}

void print_list(node_t* head) {
    node_t* current = head;

    while ( current != NULL )
    {
        printf("%02d = 0x%02X\n", current->data, current->data);
        current = current->next;
    }

    return;
}

analysis_t list_check_bit(node_t* head, uint32_t bit)
{
    analysis_t analysis = { 0 };

    node_t* current = head;

    while ( current != NULL )
    {
        if ( (current->data & (1U<<bit)) != 0U )
        {
            analysis.ones++;
        }
        else
        {
            analysis.zeros++;
        }
        current = current->next;
    }

    return analysis;
}

int count(node_t* head)
{
    int c = 0;
    node_t* current = head;

    while ( current != NULL )
    {
        c++;
        current = current->next;
    }

    return c;
}

node_t *free_list(node_t* head)
{
    node_t *tmpPtr = head;
    node_t *followPtr;
    while ( tmpPtr != NULL )
    {
        followPtr = tmpPtr;
        tmpPtr = tmpPtr->next;
        free(followPtr);
    }

    return NULL;
}

int deleteNode(node_t** head, uint32_t data, int (*comp)(uint32_t, uint32_t))
{
    node_t *temp = *head;
    node_t *prev;

    if ( (temp != NULL) && (*comp)(data, temp->data) )
    {
        *head = temp->next;
        free(temp);
        return EXIT_SUCCESS;
    }

    while ( (temp != NULL) && !(*comp)(data, temp->data) )
    {
        prev = temp;
        temp = temp->next;
    }

    if ( temp == NULL )
    {
        return EXIT_FAILURE;
    }

    prev->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}

int getFirst(node_t* head, uint32_t* data)
{
    if ( head != NULL )
    {
        *data = head->data;
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}


/*---- Local functions -------------------------------------------------------*/



/*----------------------------------------------------------- END OF FILE ----*/

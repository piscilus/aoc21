/**
 * \file data.h
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Module for data analysis.
 */

/*---- Include Guard ---------------------------------------------------------*/
#ifndef DATA_H_
#define DATA_H_


/*---- Includes --------------------------------------------------------------*/
#include <stdint.h>


/*---- Global macro definitions ----------------------------------------------*/


/*---- Global type definitions -----------------------------------------------*/
typedef struct node
{
    uint32_t data;
    struct node* next;
} node_t;

typedef struct
{
    unsigned int ones;
    unsigned int zeros;
    unsigned int total;
} analysis_t;


/*---- Exported constant declarations ----------------------------------------*/


/*---- Exported data declarations --------------------------------------------*/


/*---- Exported function declarations ----------------------------------------*/
void push(node_t** head, uint32_t data);
node_t* list_clone(node_t* head);
void append(node_t** head, uint32_t data);
void print_list(node_t* head);
int count(node_t* head);
node_t *free_list(node_t *head);
int deleteNode(node_t** head, uint32_t data, int (*comp)(uint32_t, uint32_t));
analysis_t list_check_bit(node_t* head, uint32_t bit);
int getFirst(node_t* head, uint32_t* data);



#endif /* DATA_H_ */

/*----------------------------------------------------------- END OF FILE ----*/

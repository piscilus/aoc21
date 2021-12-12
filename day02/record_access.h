/**
 * \file record_access.h
 *
 * \copyright (C) 2021 piscilus
 *
 * \brief Module to access the data record.
 */

/*---- Include Guard ---------------------------------------------------------*/
#ifndef RECORD_ACCESS_H_
#define RECORD_ACCESS_H_

#ifdef __cplusplus
extern "C"
{
#endif


/*---- Includes --------------------------------------------------------------*/


/*---- Global macro definitions ----------------------------------------------*/
#define DIRECTION_MAX (10)


/*---- Global type definitions -----------------------------------------------*/
typedef struct
{
    char d[DIRECTION_MAX];  /* direction */
    unsigned int v;         /* velocity */
} command_t;


/*---- Exported constant declarations ----------------------------------------*/


/*---- Exported data declarations --------------------------------------------*/


/*---- Exported function declarations ----------------------------------------*/
int read_data_record(char* fname, command_t commands[], int max);



#ifdef __cplusplus
}
#endif

#endif /* RECORD_ACCESS_H_ */

/*----------------------------------------------------------- END OF FILE ----*/

/**
 * \file record_access.h
 *
 * \copyright (C) 2021 "piscilus" Julian Kraemer
 *
 * Distributed under MIT license.
 * See file LICENSE for details or copy at https://opensource.org/licenses/MIT
 *
 * \brief Module to access the data record.
 */

/*---- Include Guard ---------------------------------------------------------*/
#ifndef RECORD_ACCESS_H_
#define RECORD_ACCESS_H_


/*---- Includes --------------------------------------------------------------*/
#include <stdlib.h>
#include <stdint.h>


/*---- Global macro definitions ----------------------------------------------*/
#define RECORD_MAX_SIZE (2000)
#define RAW_DATA_MAX_LEN (32)


/*---- Global type definitions -----------------------------------------------*/
typedef struct
{
    struct data
    {
        char        raw[RAW_DATA_MAX_LEN];
        uint32_t    num;
    } data[RECORD_MAX_SIZE];
    uint32_t data_len;
    uint32_t num_data;
} diagnostic_t;


/*---- Exported constant declarations ----------------------------------------*/


/*---- Exported data declarations --------------------------------------------*/


/*---- Exported function declarations ----------------------------------------*/
int read_data_record(char* fname, diagnostic_t* diagnostics);



#endif /* RECORD_ACCESS_H_ */

/*----------------------------------------------------------- END OF FILE ----*/

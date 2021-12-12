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
#include <stdlib.h>


/*---- Global macro definitions ----------------------------------------------*/
#define RAW_DATA_MAX_LEN (32)


/*---- Global type definitions -----------------------------------------------*/
typedef struct
{
    char        raw[RAW_DATA_MAX_LEN];
    size_t      raw_len;
    unsigned int data;
} diagnostic_t;


/*---- Exported constant declarations ----------------------------------------*/


/*---- Exported data declarations --------------------------------------------*/


/*---- Exported function declarations ----------------------------------------*/
int read_data_record(char* fname, diagnostic_t diagnostics[], int n);



#ifdef __cplusplus
}
#endif

#endif /* RECORD_ACCESS_H_ */

/*----------------------------------------------------------- END OF FILE ----*/

/*
 * gpio_type.h
 *
 * Author: Gautam Tadavarthi
 */



#ifndef GPIO_TYPE_H_
#define GPIO_TYPE_H_

#include "global.h"

/*****************************************************************************************
 *************** Type Definition for GPIO signal                     **************************
 *****************************************************************************************/


//#error "Provide your data structure"
typedef struct
{
   boolean_t breakLightState;   
} GPIO_data_t;

//#error "Provide a sensible init value"
#define GPIO_INIT_DATA ((GPIO_data_t){FALSE})


/**
 * Default IN driver API - may be deleted if not required
 * \param GPIO_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t GPIO_driverIn(GPIO_data_t *const data);


/**
 * Default IN driver API - may be deleted if not required
 * \param const GPIO_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t GPIO_driverOut(const GPIO_data_t  *const data);



#endif /* GPIO_TYPE_H_ */


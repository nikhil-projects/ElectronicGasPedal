/*
 * pwm_type.h
 *
 * Author: Gautam Tadavarthi
 */



#ifndef PWM_TYPE_H_
#define PWM_TYPE_H_

#include "global.h"

/*****************************************************************************************
 *************** Type Definition for PWM signal                     **************************
 *****************************************************************************************/

//#error "Provide your data structure"
typedef struct
{
uint8_t engineValue;
} PWM_data_t;


//#error "Provide a sensible init value"
#define PWM_INIT_DATA ((PWM_data_t){0})


/**
 * Default IN driver API - may be deleted if not required
 * \param PWM_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t PWM_driverIn(PWM_data_t *const data);


/**
 * Default IN driver API - may be deleted if not required
 * \param const PWM_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t PWM_driverOut(const PWM_data_t  *const data);



#endif /* PWM_TYPE_H_ */


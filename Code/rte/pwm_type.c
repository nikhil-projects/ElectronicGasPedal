/*
 * pwm_type.c
 *
 * Author: Gautam Tadavarthi
 */


#include "project.h"
#include "global.h"

#include "pwm_type.h"



/*****************************************************************************************
 *************** Port Wrapper Implementation for PWM signal                     **************************
 *****************************************************************************************/


/**
 * Default IN driver API - may be deleted if not required
 */
inline RC_t PWM_driverIn(PWM_data_t *const data)
{
//#error "Add your code here"

	//Read data from the MCAL driver

	//Scale it to the application type

	return RC_SUCCESS;
}

/**
 * Default IN driver API - may be deleted if not required
 */
inline RC_t PWM_driverOut(const PWM_data_t  *const data)
{
//#error "Add your code here"

	//Scale application data to drive format

	//Write scaled data to driver
    RGB_PWM_Green_WriteCompare(data->engineValue);
	return RC_SUCCESS;
}

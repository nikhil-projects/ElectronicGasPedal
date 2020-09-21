/*
 * adc_type.c
 *
 * Author: Gautam Tadavarthi
 */


#include "project.h"
#include "global.h"

#include "adc_type.h"
#include "joystick.h"

/*****************************************************************************************
 *************** Port Wrapper Implementation for ADC signal                     **************************
 *****************************************************************************************/


/**
 * Default IN driver API - may be deleted if not required
 */
inline RC_t ADC_driverIn(ADC_data_t *const data)
{
//#error "Add your code here"

	//Read data from the MCAL driver
    data->joystickValue = JOYSTICK_getPosition(); 
	//Scale it to the application type
    

	return RC_SUCCESS;
}

/**
 * Default IN driver API - may be deleted if not required
 */
inline RC_t ADC_driverOut(const ADC_data_t  *const data)
{
//#error "Add your code here"

	//Scale application data to drive format

	//Write scaled data to driver

	return RC_SUCCESS;
}

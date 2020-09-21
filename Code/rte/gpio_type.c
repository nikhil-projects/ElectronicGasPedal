/*
 * gpio_type.c
 *
 * Author: Gautam Tadavarthi
 */


#include "project.h"
#include "global.h"

#include "gpio_type.h"


/*****************************************************************************************
 *************** Port Wrapper Implementation for GPIO signal                     **************************
 *****************************************************************************************/


/**
 * Default IN driver API - may be deleted if not required
 */
inline RC_t GPIO_driverIn(GPIO_data_t *const data)
{
//#error "Add your code here"

	//Read data from the MCAL driver

	//Scale it to the application type

	return RC_SUCCESS;
}

/**
 * Default IN driver API - may be deleted if not required
 */
inline RC_t GPIO_driverOut(const GPIO_data_t  *const data)
{
//#error "Add your code here"

	//Scale application data to drive format

	//Write scaled data to driver
     Red_Led_Write(data->breakLightState); 

	return RC_SUCCESS;
}

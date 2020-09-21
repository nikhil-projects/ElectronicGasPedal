/**
* \file <filename>
* \author <Gautam Tadavarthi>
* \date <date>
*
* \brief <Symbolic File name>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "electronic_gaspedal.h"
#include "watchdog.h"
#include "led.h"
#include "joystick.h"


/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * <Description>
 * @param <first para>
 * @return <return value>
 */

void electronic_gaspedal_init()
{
    LED_Init();
    JOYSTICK_init();
    LED_RGB_Set(0,0,0);
   
}

void run_readJoystick(){
    //can make use of return type for error scenario of lldrivers, and age for the communication handling issue
    RTE_ADC_pullPort(&JOYSTICK_signal);
    WD_Alive(readJoystick);
}
void run_calculateControl(){

    PWM_data_t pwm_value;    
    
    if(JOYSTICK_signal.value.joystickValue>0)
    {
        pwm_value.engineValue=2*JOYSTICK_signal.value.joystickValue;
    }
    else
    {
        pwm_value.engineValue=0;
    }
    RTE_PWM_set(&ENGINE_signal,pwm_value);
    WD_Alive(calcControl);
}

void run_setEngine(){
    RTE_PWM_pushPort(&ENGINE_signal);
    WD_Alive(setEngine);
}

void run_setBrakeLight(){
    
  GPIO_data_t gpio_Value;  
    if(ENGINE_signal.value.engineValue==0)
    {
        gpio_Value.breakLightState=TRUE;
    }
    else
    {
        gpio_Value.breakLightState=FALSE;
    }

   RTE_GPIO_set(&BRAKELIGHT_signal,gpio_Value);
   RTE_GPIO_pushPort(&BRAKELIGHT_signal);
   WD_Alive(setBrakeLight);
}


/**************************************************
 ** author: Gautam Tadavarthi
 ** The RTE signals 
 **************************************************/

#include "project.h" 
#include "global.h" 
#include "rte_signalpool.h" 


/* Generated signal classes */
#include "adc_signal.h"
#include "pwm_signal.h"
#include "gpio_signal.h"


/*****************************************************
 ** RTE Object joystick
 ** Input signal for joystick position (ADC), range -100..100
 *****************************************************/


/* signal configuration */

static const ADC_cfg_t JOYSTICK_cfg = 
{
   /* indriver      */  ADC_driverIn,
   /* outdriver     */  0,
   /* onUpdate      */  ev_joystick_onUpdate
}; /* configuration joystick */


/* signal data */

ADC_t JOYSTICK_signal = 
{
   /* init value    */  ADC_INIT_DATA,
   /* status        */  RTE_SIGNALSTATUS_STARTUP,
   /* age           */  0,
   /* cfg           */  &JOYSTICK_cfg
}; /* data joystick */


/*****************************************************
 ** RTE Object engine
 ** Input signal for engine
 *****************************************************/


/* signal configuration */

static const PWM_cfg_t ENGINE_cfg = 
{
   /* indriver      */  0,
   /* outdriver     */  PWM_driverOut,
   /* onUpdate      */  ev_engine_onUpdate
}; /* configuration engine */


/* signal data */

PWM_t ENGINE_signal = 
{
   /* init value    */  PWM_INIT_DATA,
   /* status        */  RTE_SIGNALSTATUS_STARTUP,
   /* age           */  0,
   /* cfg           */  &ENGINE_cfg
}; /* data engine */


/*****************************************************
 ** RTE Object brakeLight
 ** Input signal for brakeLight
 *****************************************************/


/* signal configuration */

static const GPIO_cfg_t BRAKELIGHT_cfg = 
{
   /* indriver      */  0,
   /* outdriver     */  GPIO_driverOut,
   /* onUpdate      */  ev_engine_onUpdate
}; /* configuration brakeLight */


/* signal data */

GPIO_t BRAKELIGHT_signal = 
{
   /* init value    */  GPIO_INIT_DATA,
   /* status        */  RTE_SIGNALSTATUS_STARTUP,
   /* age           */  0,
   /* cfg           */  &BRAKELIGHT_cfg
}; /* data brakeLight */


/*******************************************************************************
 ** Central timertick function for ticktime 10 
 *******************************************************************************/ 

void RTE_timertick()
{
    RTE_ADC_incAge( &JOYSTICK_signal, 10);
    RTE_PWM_incAge( &ENGINE_signal, 10);
    RTE_GPIO_incAge( &BRAKELIGHT_signal, 10);
}


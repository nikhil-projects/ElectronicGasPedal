/**************************************************
 ** author: Gautam Tadavarthi
 ** The RTE signal blackboard 
 **************************************************/

#ifndef RTE_SIGNALPOOL_H
#define RTE_SIGNALPOOL_H


/* Generated signal classes */
#include "adc_signal.h"
#include "pwm_signal.h"
#include "gpio_signal.h"


/* Generated objects */

/* Input signal for joystick position (ADC), range -100..100 */
extern ADC_t JOYSTICK_signal;

/* Input signal for engine */
extern PWM_t ENGINE_signal;

/* Input signal for brakeLight */
extern GPIO_t BRAKELIGHT_signal;

/** Central Timertick function 
 *  must be called every 10ms 
 **/  
void RTE_timertick();


#endif

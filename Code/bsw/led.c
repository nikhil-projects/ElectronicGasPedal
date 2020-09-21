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
#include "led.h"

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

//static LED_ONOFF_t LED__state[LED_ALL] = {LED_OFF, LED_OFF, LED_OFF}; /**< On/Off State of the LED */


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
/**
 * Inverts the parameter
 * @param LED_ONOFF_t ledOnOff - Value to be inverted
 * @return inverted parameter
 */
//static inline LED_ONOFF_t LED__toggleValue(LED_ONOFF_t ledOnOff);

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/


/**
 * Initialises the LED's and turns them off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Init()
{
    RC_t result = RC_SUCCESS;
    
    Red_Led_Write(0); 
    
    //Init RGB
    RGB_PWM_Blue_Start();
    RGB_PWM_Green_Start();
    RGB_PWM_Red_Start();
    
    Red_Led_Write(0);

    
    RGB_PWM_Blue_WriteCompare(0);
    RGB_PWM_Green_WriteCompare(0);
    RGB_PWM_Red_WriteCompare(0);
    
    return result;
}

/**
 * Sets the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @param LED_ONOFF_t ledOnOff - Trun the led on or off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
//RC_t LED_Set(LED_select_t ledId, LED_ONOFF_t ledOnOff)
//{
//    //set individual LED
//    switch (ledId)
//    {
//        case LED_RED : 
//            Red_Led_Write(ledOnOff); 
//            LED__state[ledId] = ledOnOff; 
//            break;
//        
//        case LED_YELLOW : 
//            Yellow_Led_Write(ledOnOff); 
//            LED__state[ledId] = ledOnOff;
//            break;
//            
//        case LED_GREEN : 
//            Green_Led_Write(ledOnOff); 
//            LED__state[ledId] = ledOnOff;
//            break;
//           
//        case LED_ALL : 
//            for (LED_select_t i = LED_RED; i < LED_ALL; i++)
//            {
//                LED_Set(i, ledOnOff);
//            }
//            break;
//        default: return RC_ERROR_BAD_PARAM;
//    }
//    
//    return RC_SUCCESS;
//}

/**
 * Toggle the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
//RC_t LED_Toggle(LED_select_t ledId)
//{
//    //set individual LED
//    switch (ledId)
//    {
//        case LED_RED : 
//            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
//            Red_Led_Write(LED__state[ledId]);
//            break;
//        
//        case LED_YELLOW : 
//            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
//            Yellow_Led_Write(LED__state[ledId]);
//            break;
//            
//        case LED_GREEN : 
//            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
//            Green_Led_Write(LED__state[ledId]);
//            break;
//           
//        case LED_ALL : 
//            for (LED_select_t i = LED_RED; i < LED_ALL; i++)
//            {
//                LED_Toggle(i);
//            }
//            break;
//        default: return RC_ERROR_BAD_PARAM;
//    }
//    
//    return RC_SUCCESS;
//}


/**
 * Inverts the parameter
 * @param LED_ONOFF_t ledOnOff - Value to be inverted
 * @return inverted parameter
 */
//static inline LED_ONOFF_t LED__toggleValue(LED_ONOFF_t ledOnOff)
//{
//    if (ledOnOff == LED_ON) 
//    {
//        return LED_OFF;
//    }
//    else
//    {
//        return LED_ON;
//    }
//}

///**
// * Set the RGB LED
// * @param uint16_t red - brightness 
// * @param uint16_t green - brightness 
// * @param uint16_t blue - brightness 
// * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
// */
//RC_t LED_RGB_GLow()
//{
//    uint8_t i;
//    for(i=0;i<9;i++){
//        RGB_PWM_Red_WriteCompare(RG_glowtable_1[i].Red);
//        RGB_PWM_Green_WriteCompare(RG_glowtable_1[i].Green);
//        RGB_PWM_Blue_WriteCompare(RG_glowtable_1[i].Blue);
//        CyDelay(RG_glowtable_1[i].TimeinMs);
//    }
// 
//    return RC_SUCCESS;
//}

/**
 * Set the RGB LED
 * @param uint16_t red - brightness 
 * @param uint16_t green - brightness 
 * @param uint16_t blue - brightness 
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_RGB_Set(uint8_t red, uint8_t green, uint8_t blue)
{
    RGB_PWM_Red_WriteCompare(red);
    RGB_PWM_Green_WriteCompare(green);
    RGB_PWM_Blue_WriteCompare(blue);
 
    return RC_SUCCESS;
}

/**
 * Set the LED
 * @param uint16_t red - brightness 
 * @param uint16_t green - brightness 
 * @param uint16_t yellow - brightness 
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
//RC_t LED_PWM_Set(uint8_t red, uint8_t green, uint8_t yellow)
//{
//    PWM_Red_Led_WriteCompare(red);
//    PWM_Green_Led_WriteCompare(green);
//    PWM_Yellow_Led_WriteCompare(yellow);
// 
//    return RC_SUCCESS;
//}

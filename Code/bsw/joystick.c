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
#include "joystick.h"
#include "uart.h"

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

void JOYSTICK_init()
{
   uint8_t X_Axis=0,Y_Axis=0;
   float voltage = 0; //voltage reading
   static uint8_t counts = 0; // ADC Counts 
    
   ADC_SAR_Horizontal_Start();
   ADC_SAR_Horizontal_StartConvert(); 
   ADC_SAR_Horizontal_IsEndConversion(ADC_SAR_Horizontal_WAIT_FOR_RESULT);
   X_Axis = ADC_SAR_Horizontal_GetResult8(); //read ADC 
   voltage = ADC_SAR_Horizontal_CountsTo_Volts(counts);

   ADC_SAR_Vertical_Start();
   ADC_SAR_Vertical_StartConvert(); 
   ADC_SAR_Vertical_IsEndConversion(ADC_SAR_Vertical_WAIT_FOR_RESULT);
   Y_Axis = ADC_SAR_Vertical_GetResult8(); //read ADC 
   voltage = voltage+ADC_SAR_Vertical_CountsTo_Volts(counts);
   
    if(0.0!=voltage)
    {
        UART_TxMessage("Reset the position of the JoyStick to normal state");
    }
    else
        UART_TxMessage("JoyStick is initialized..");
}

sint8_t JOYSTICK_getPosition()
{  
    uint8_t X_Axis=0,Y_Axis=0;
    sint8_t X_Data=0,Y_Data=0;
    
    X_Axis=0;
    Y_Axis=0;
   
    ADC_SAR_Horizontal_IsEndConversion(ADC_SAR_Horizontal_WAIT_FOR_RESULT);  
    X_Axis = ADC_SAR_Horizontal_GetResult8(); //read ADC 
   
    
    ADC_SAR_Vertical_IsEndConversion(ADC_SAR_Vertical_WAIT_FOR_RESULT);  
    Y_Axis = ADC_SAR_Vertical_GetResult8(); //read ADC 
  
    
    if(X_Axis <= 119)
        X_Data = 119-X_Axis;
    else
       X_Data = 127-X_Axis;
    
     if(Y_Axis <= 122)
        Y_Data = 122-Y_Axis;
    else
       Y_Data = 127-Y_Axis;

    
    if(X_Data!=0)
        return X_Data;  
    else if(Y_Data!=0)
        return Y_Data;
   
    
    return 0; 
}




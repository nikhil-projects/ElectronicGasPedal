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
#include "watchdog.h"
#include "uart.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
 extern sRunnable_t runnable_alive;
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
 * @return <return valu
 */
RC_t WD_Start(WDT_TimeOut_t timeout){
    
    runnable_alive.run_readJoystick = 0;
    runnable_alive.run_calcControl = 0;
    runnable_alive.run_setEngine = 0;
    runnable_alive.run_setBrakeLight = 0;    
    CyWdtClear();
    
    CyWdtStart(timeout,CYWDT_LPMODE_NOCHANGE);    
    return RC_SUCCESS;
}

/**
* Service the Watchdog Trigger
* @return RC_SUCCESS
*/
RC_t WD_Trigger(){
    
    CyWdtClear();
    return RC_SUCCESS;
}

/**
* Checks the watchdog bit
* @return TRUE if watchdog reset bit was set
*/
boolean_t WD_CheckResetBit(){
 
   if (( CyResetStatus) & 0x8)
    return TRUE;
   else
     return FALSE; 
}

void WD_Alive(uint8_t myBitPosition){
    
    switch(myBitPosition)
    {
        case readJoystick:
            runnable_alive.run_readJoystick = 1;
        break;
        case calcControl:
            runnable_alive.run_calcControl = 1;
        break;
        case setEngine:
            runnable_alive.run_setEngine = 1;
        break;
        case setBrakeLight:
            runnable_alive.run_setBrakeLight = 1;
        break;
    }
}

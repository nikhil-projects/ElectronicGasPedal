/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "electronic_gaspedal.h"
#include "rte.h"
#include "rte_activation.h"
#include "watchdog.h"
#include "uart.h"

volatile static uint8_t timerTick=0;
sRunnable_t runnable_alive;

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main(void)
{
        
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
	EE_systick_start();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

/**
 * Initialization task, whic is a autostart task
 * 
 */
TASK(tsk_Init)
{    
    if(WD_CheckResetBit())
        UART_TxMessage("Watchdog reset");
    else
        UART_TxMessage("POR");
        
    //Init MCAL Drivers
    electronic_gaspedal_init();
    WD_Start(WDT_1024_TICKS);
        
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();      
 
    //Start the Alarm_10ms with 10ms cycle time
    SetRelAlarm(Alarm_10ms,10,10);

    ActivateTask(tsk_EventDispatcher);      
    ActivateTask(tsk_Background);  
    TerminateTask();    
}
/**
 * Background task, least priporty task which executes if no other tasks are executing
 * 
 */
TASK(tsk_Background)
{
    while(1){
        if(runnable_alive.run_calcControl & runnable_alive.run_readJoystick &runnable_alive.run_setBrakeLight &runnable_alive.run_setEngine)
        {
           WD_Trigger();
            
            //clear flags
            runnable_alive.run_calcControl =0;
            runnable_alive.run_readJoystick =0;
            runnable_alive.run_setBrakeLight =0;
            runnable_alive.run_setEngine =0;
        }
    }    
    asm("nop");
    TerminateTask();
}

TASK(tsk_EventDispatcher)
{    
    while(1)
    {
        EventMaskType ev=0;
        RTE_ProcessEventTable(RTE_eventActivationTable,RTE_eventActivation_size,ev); 
    }
    TerminateTask(); 
}

TASK(tsk_CyclicDispatcher)
{ 
   RTE_ProcessCyclicTable(RTE_cyclicActivationTable,RTE_cyclicActivation_size,timerTick);
   if(100 == timerTick) timerTick =0;
   timerTick=timerTick+10;
   TerminateTask(); 
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

/* [] END OF FILE */

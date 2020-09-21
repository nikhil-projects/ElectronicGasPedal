/* ========================================
 * author: Gautam Tadavarthi
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
#include "global.h"

#include "rte.h"

RC_t RTE_ProcessEventTable(RTE_eventTable_t const *const table, uint16_t tableSize, EventMaskType ev)
{
    //incremening the pointer required
     WaitEvent(ev_joystick_onUpdate|ev_engine_onUpdate); 
     GetEvent(tsk_EventDispatcher,&ev);
     ClearEvent(ev);    

    for(uint16_t loop=0;loop<tableSize;loop++)   
        { 
            if(table[loop].event&ev)
            {
                table[loop].run();
                //watch dog alive here for each runnable
            }            
       }
 return RC_SUCCESS;
}

RC_t RTE_ProcessCyclicTable(RTE_cyclicTable_t const *const table, uint16_t tableSize, uint16_t time)
{    
    for(uint16_t loop=0;loop<tableSize;loop++)   
        { 
            if(table[loop].cycleTime==time)
            {
                    table->run();
            }        
        }
        
   return RC_SUCCESS;
}

/* [] END OF FILE */

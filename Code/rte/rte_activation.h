/**************************************************
 ** author: Gautam Tadavarthi
 ** The RTE activation engine
 ** 
 **************************************************/

#ifndef RTE_ACTIVATION_H
#define RTE_ACTIVATION_H

#include "project.h"
#include "global.h"
#include "rte.h"


/** 
 ** Cyclic Activation Table
 **/ 
 extern const RTE_cyclicTable_t RTE_cyclicActivationTable[]; 
 extern const uint16_t RTE_cyclicActivation_size; 

/** 
 ** Event Activation Table
 **/ 
 extern const RTE_eventTable_t RTE_eventActivationTable[]; 
 extern const uint16_t RTE_eventActivation_size; 



#endif

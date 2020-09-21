/**
*  file    GPIO_signal.h
*
*  brief   signal base class for signal gpio
*
*  author Gautam Tadavarthi
*
*
*/

#ifndef GPIO_SIGNAL_H_INCLUDED
#define GPIO_SIGNAL_H_INCLUDED

/*================================================[ configuration  ]================================================*/
#define GPIO_SYNCHRONOUS

/*================================================[ public includes  ]================================================*/
#include "global.h"
#include "project.h"
#include "rte.h"

#include "gpio_type.h"


/********************************************************************************************************************/
/* The driver API block																						*/
/********************************************************************************************************************/
                                                                                                                       
/**
 *  Definition of function types for driver interfaces.
 *  I-Port
 */
typedef RC_t (*GPIO_driverIn_t)(GPIO_data_t * const);

/**
 *  Definition of function types for driver interfaces.
 *  O-Port
 */
typedef RC_t (*GPIO_driverOut_t)( const GPIO_data_t * const);


/********************************************************************************************************************/
/* The signal configuration API block																				*/
/********************************************************************************************************************/

/**
 * Instances of the struct GPIO_cfg_t represent the signal object configuration.
 */
struct GPIO_cfg_s
{
    /**
     * Function pointer to the input driver
     */
    GPIO_driverIn_t const inDriver;

    /**
     * Function pointer to the output driver table
     */
   GPIO_driverOut_t const outDriver;
   
    /**
     * Event onUpdate
     */
    EventMaskType const evOnUpdate;

};                                                                                                                     
typedef const struct GPIO_cfg_s GPIO_cfg_t;
                              
/********************************************************************************************************************/
/* The data interface block																							*/
/********************************************************************************************************************/

                                                                                                                       
							  
/**
 * Instances of the struct GPIO_t represent the signal objects.
 * A signal object contains the current application value 'value' as well as relevant meta data.
 */
struct GPIO_s
{                                                                                                                      

	/**
	 * Data buffer for the application value
	 */
    GPIO_data_t value;

    /**
     * Current signal status
     */
    RTE_signalStatus_t status;

    /**
     * Current age of the signal (in calling cycles)
     */
    uint32_t age;

    /**
     * Pointer to the signal configuration
     */
	const GPIO_cfg_t * const    pSigCfg;

};                                                                                                                     
typedef struct GPIO_s GPIO_t;

/********************************************************************************************************************/
/* Signal initialisation   																							*/
/********************************************************************************************************************/

/**
 * Initializes a signal instance with a passed init value.
 * Depending on the configured conversion or scaling function the raw_value will be calculated.
 * Signal status will change from RTE_SIGNALSTATUS_STARTUP to RTE_SIGNALSTATUS_INITIALIZED.
 *
 * @param  GPIO_t * const signal: Pointer to the signal object which will be initialised
 * @param const gpio_data_t * const value: Pointer to initial value of the application data
 * @return RC_t: standard return code, currently only RC_SUCCESS
 *
 **/
inline RC_t RTE_GPIO_init( GPIO_t * const signal, const GPIO_data_t * const value )
{                                                                                                                      

   RC_t ret = RC_SUCCESS;

   //Set value and raw value
   signal->value  = *value;
   signal->age    = 0;
   signal->status = RTE_SIGNALSTATUS_INITIALIZED;

   return ret;
}

/********************************************************************************************************************/
/* Status and timeout control																						*/
/********************************************************************************************************************/

/**
 *  Returns the current signal status of the passed signal instance.
 *
 * @param  GPIO_t * const signal: Pointer to the signal object
 * @return  sig_status_t: The current signal status
 *
 **/
inline RTE_signalStatus_t RTE_GPIO_getStatus( const GPIO_t * const signal )
{
   return signal->status;
}


/**
 *  Sets a new signal status of the passed signal instance by passing the new status.
 *
 * @param  GPIO_t * const signal: Pointer to the signal object
 * @param  const sig_status_t status: New signal status
 * @return RC_t: standard return code, currently only RC_SUCCESS
 *
 */
inline RC_t RTE_GPIO_setStatus( GPIO_t * const signal, const RTE_signalStatus_t status )
{
   signal->status = status;
   return RC_SUCCESS;
}


/**
 * Returns the count of refreshing trials (refresh, set or set_raw) that failed.
 * Prerquisite: The signal is refreshed cyclically
 *
 * @param  GPIO_t * const signal: Pointer to the signal object
 * @return uint32_t: Number of cycles since the signal has been updated for the last time
 */
inline uint32_t RTE_GPIO_getAge( const GPIO_t * const signal )
{
   return signal->age;
}

/**
 * Should be called by application or driver if no new value can be provided.
 * @param  GPIO_t * const signal: Pointer to the signal object
 * @param uint32_t increment: incrementvalue, typically in [ms]
 * @return void
 */
inline void RTE_GPIO_incAge(  GPIO_t * const signal , uint32_t increment)
{
	   //Hack....
	   if ( 0xFFFF0000 > (signal->age + increment) )
	   {
	      signal->age += increment;
	   }
}


/********************************************************************************************************************/
/* Application Data read/write Interface																			*/
/********************************************************************************************************************/

/**
 * Returns the current application value of the passed signal instance.
 *
 * @param  GPIO_t * const signal: Pointer to the signal object
 * @return gpio_data_t: current value of the application data buffer
 *
 **/
inline GPIO_data_t RTE_GPIO_get( const GPIO_t * const signal )
{                                                                                                                      
   return signal->value;                                                                                               
}                                                                                                                      
                                                                                                                       
                                                                                                                    
                                                                                                                       
/**
 * Sets a new application value to the passed signal instance by passing the new value.
 * The corresponding driver raw value will be calculated immediately by using the default conversion or calling the
 * signal specific scaling function.
 * The signal age will be set to 0 and the new status will be 'RTE_SIGNALSTATUS_VALID'.
 *
 * @param  GPIO_t * const signal: Pointer to the signal object
 * @param  gpio_data_t const value: value for the application data buffer
 * @return RC_t: standard return code, currently only RC_SUCCESS
 *
 **/
inline RC_t RTE_GPIO_set(GPIO_t * const signal, const GPIO_data_t value  )
{

   RC_t ret = RC_SUCCESS;


   //Todo: critical section
    signal->value  = value;
	signal->age    = 0;
	signal->status = RTE_SIGNALSTATUS_VALID;

#ifdef GPIO_ASYNCHRONOUS
	SetEvent( tsk_EventDispatcher, signal->pSigCfg->evOnUpdate);
#endif                                                                                                              
   return ret;
}                                                                                                                      
                                                                                                                       
                                                                                                                      
/********************************************************************************************************************/
/* Call functions to the connected drivers																			*/
/********************************************************************************************************************/

                                                                                                                       
/**
 *  Calls the connected driver interface to get a new value.
 *
 * @param GPIO_t * const signal: Pointer to the signal object
 * @return  RC_t: Return value of the driver call
 *
 */
inline RC_t RTE_GPIO_pullPort( GPIO_t * const signal )
{                                                                                                                      
   RC_t ret = RC_SUCCESS;

                                                                                                                       
   if ( NULL != signal->pSigCfg->inDriver )
   {
	  GPIO_data_t value;
      ret = signal->pSigCfg->inDriver(&value);
                                                                                                                       
      if ( ret == RC_SUCCESS )                                                                                         
      {
    	  //Critical Section
    	  RTE_GPIO_set(signal, value);
      }
      else
      {
    	  signal->status = RTE_SIGNALSTATUS_INVALID;
      }

   }                                                                                                                   
                                                                                                                       
   return ret;                                                                                                         
}                                                                                                                      
                                                                                                                       
/**
 *  Calls the connected driver interfaces to send a value. Value will not be sent if it is INVALID.
 *
 * @param GPIO_t * const signal: Pointer to the signal object
 * @return  RC_t: Return value of the driver call
 *
 **/
inline RC_t RTE_GPIO_pushPort( const GPIO_t * const signal )
{                                                                                                                      
   RC_t ret = RC_ERROR;

   if (RTE_SIGNALSTATUS_VALID == signal->status)
   {
	   ret = signal->pSigCfg->outDriver(&(signal->value));
   }
   return ret;                                                                                                         
}                                                                                                                      

#endif /* include guard */


/* 
 * File:   timers.h
 * Author: peio.gil
 *
 * Created on 29 de diciembre de 2020, 20:37
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


 /*** Timers  Definitions *****************************************/



uint16_t timerCounter;

typedef enum
{
    TIMER_0 = 0,
} TIMER_NUMBER;

typedef enum
{
    TIMER_CONFIGURATION_DEFAULT
} TIMER_CONFIGURATION;
/*********************************************************************
* Function: bool TIMER0_SetConfiguration(TIMER_CONFIGURATION configuration)
*
* Overview: Configures the TIMER0 module to specified setting
*
* PreCondition: none
*
* Input: TIMER_CONFIGURATION configuration - the mode in which to run the TIMER0
*
* Output: bool - true if successfully configured.  false otherwise.
*
********************************************************************/

bool TIMER0_SetConfiguration(void);

//bool TIMER0_SetConfiguration(TIMER_CONFIGURATION configuration);




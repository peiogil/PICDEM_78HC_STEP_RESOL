/*******************************************************************************
   TC78H670FTG_  abstraction layer for SparkFun_ProDriver_TC78H670FTG_demo board.

  Company:
    myself.

  File Name:
    SparkFun_ProDriver_TC78H670FTG.c

  Summary:
    TC78H670FTG_  abstraction layer for SparkFun_ProDriver_TC78H670FTG_demo board.

  Description:
    TC78H670FTG_  abstraction layer for SparkFun_ProDriver_TC78H670FTG_demo board..
*******************************************************************************/
// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "SparkFun_ProDriver_TC78H670FTG_Library.h"
#include <xc.h>
#include "timers.h"



// *****************************************************************************
// *****************************************************************************
// Section: Macros or Functions
// *****************************************************************************
// *****************************************************************************
//****************************************************************************//
//
//  Constructor
//
//    Initalizes settings to default.
//
//****************************************************************************//
//struct 
PRODRIVERSettings settings;
void IniSettingsDefault( void )
{
    //PRODRIVERSettings settings;                                                                             
	//Construct with these default settings if nothing is specified
	//Select control mode
                                                                                  
settings.controlMode = PRODRIVER_MODE_CLOCKIN; // PRODRIVER_MODE_CLOCKIN or PRODRIVER_MODE_SERIAL
settings.stepResolutionMode = PRODRIVER_STEP_RESOLUTION_FIXED_FULL; // many options, see header file or ds pg 8
settings.stepResolution = PRODRIVER_STEP_RESOLUTION_1_1; // IC default on bootup
  
    //Select default settings for SERIAL MODE specific settings
  settings.phaseA = PRODRIVER_PHASE_PLUS;
  settings.phaseB = PRODRIVER_PHASE_PLUS;
  settings.currentLimA = 1023; // max
  settings.currentLimB = 1023; // max
  settings.torque = PRODRIVER_TRQ_100;
  settings.openDetection = PRODRIVER_OPD_OFF;
  settings.mixedDecayA = PRODRIVER_MD_FAST_37;
  settings.mixedDecayB = PRODRIVER_MD_FAST_37;
  settings.phasePosition = 1;

  //statuses/flags
  settings.enableStatus = PRODRIVER_STATUS_DISABLED;  
  settings.standbyStatus = PRODRIVER_STATUS_STANDBY_OFF;
  settings.errorFlag = false; // false = no error
}
// *****************************************************************************
//Select default 18f4550 pin modes for hardware connections
// *****************************************************************************
void Pin_SetUp_PortB_Driver ( void )
 {
    
  // enable is active high 
  // note, hardware slide (MTROFF ENABLE) switch can also over-ride this
  //when set to position "OFF" 
    
  TRIS_PRODRIVER_DEFAULT_PIN_EN     = OUTPUT;
  PORT_PRODRIVER_DEFAULT_PIN_EN     = LOW;
  settings.enableStatus = PRODRIVER_STATUS_DISABLED;
  // standby is active low. 
  // OUTPUT, LOW = standby
  // OUTPUT, HIGH = not in standby
  TRIS_PRODRIVER_DEFAULT_PIN_STBY   = OUTPUT;
  PORT_PRODRIVER_DEFAULT_PIN_STBY   = LOW;// hold in standby, until we're ready to go
  settings.standbyStatus = PRODRIVER_STATUS_STANDBY_OFF;
  // error is active low 
  // This will always be an input pin (on your microcontroller)
  // note, this pin on the IC has a dual purpose (both EN and ERR).
  TRIS_PRODRIVER_DEFAULT_PIN_ERROR  = INPUT;
  // All mode pins to output low
  
  TRIS_PRODRIVER_DEFAULT_PIN_MODE_0 = OUTPUT;
  PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
  TRIS_PRODRIVER_DEFAULT_PIN_MODE_1 = OUTPUT;
  PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
  TRIS_PRODRIVER_DEFAULT_PIN_MODE_2 = OUTPUT;       
  PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
  TRIS_PRODRIVER_DEFAULT_PIN_MODE_3 = OUTPUT;
  PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;
 
 }
bool controlModeSelect()
{
    PORT_PRODRIVER_DEFAULT_PIN_STBY = PRODRIVER_STATUS_STANDBY_OFF;
  // set mode pins according to desired mode
  switch (settings.controlMode)
  {
  case PRODRIVER_MODE_SERIAL:
    // set mode pins to all LOW for serial mode
   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;  
   break;

  case PRODRIVER_MODE_CLOCKIN:
  
    // set mode pins as needed
    // note, when you set controlmode to CLOCKIN,
    // you are also setting the step resolution, which can
    // be a variety of options.

    // grab "bits" from the desired step resolution
    // these will be used to set each mode pin high/low
    // mode0Pin
  switch (settings.stepResolutionMode)
      {
case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2:
    
   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW; 
  
   break;
   
case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;  
   
   break;

case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_8:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;  

   break;

case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_16:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;  

   break;   

case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_32:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW; 

   break;
   
case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_64:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;

   break;
case PRODRIVER_STEP_RESOLUTION_VARIABLE_1_128:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_FULL:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;  

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_2:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;  

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_4:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;  

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_8:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH; 

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_16:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_32:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_64:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = LOW;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;

   break;
case PRODRIVER_STEP_RESOLUTION_FIXED_1_128:

   PORT_PRODRIVER_DEFAULT_PIN_MODE_0 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_1 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_2 = HIGH;
   PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH;  

      break;
}
  //Con el paso a alto STBY se configura el modo de control del 78HC
   // wait TmodeSU (mode setting setup time) minimum 1 microsecond
 __delay_us(3);
  
  // release standby (write it HIGH)
  PORT_PRODRIVER_DEFAULT_PIN_STBY = PRODRIVER_STATUS_STANDBY_ON; 
  // wait TmodeHO (mode setting Data hold time) minimum 100 microseconds
  __delay_us(100);
  settings.standbyStatus=HIGH;// update setting to check as needed
 
       
  
    }
   //return errorStat();
  return errorStat();

}
bool TC78H_enable_pin(bool enable_disable)
{
    if (enable_disable==true) 
    {
        PORT_PRODRIVER_DEFAULT_PIN_EN = HIGH;
    settings.enableStatus == PRODRIVER_STATUS_ENABLED;
    }
    else
    {
        PORT_PRODRIVER_DEFAULT_PIN_EN = LOW;
        settings.enableStatus == PRODRIVER_STATUS_DISABLED;
  // Check to see if we are already enabled. If so, then leave pin alone.
  // If we are not enabled, then enable.
  
    }
   //return errorStat();
  return errorStat();

}
// errorStat( void )
// checks the status of the ERR net.
// Note, one pin on the IC shares the purpose of both ERR and EN (enable)
// If ERR reads low, then one of three things is wrong:
// Thermal shutdown (TSD) 
// Overcurrent (ISD)
// Motor Load Open (OPD)
// returns true if things are good and there is no error detected

bool errorStat( void )
{
  if(PORT_PRODRIVER_DEFAULT_PIN_ERROR  == HIGH)
  {
    return true; // there is no error, so let's indicate that with a true.
  }
  return false; // if we get here, then errorPin was low, indicating an error
  // false means error!
}
bool step( uint16_t steps, bool direction, uint8_t clockDelay)
{
   //uint16_t i;  
   TC78H_enable_pin(true);

  // set CW-CWW pin (aka mode3Pin) to the desired direction
  // CW-CCW pin controls the rotation direction of the motor. 
  // When set to H, the current of OUT_A is output first, with a phase difference of 90Ã‚Â°. 
  // When set to L, the current of OUT_B is output first with a phase difference of 90Ã‚Â°
  if(direction == true)
  {
    PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH; // let on-board external pullup to 3.3V pull this pin HIGH
  }
  else{
    PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;
  }
  
  // step the motor the desired amount of steps
  // each up-edge of the CLK signal (aka mode2Pin) 
  // will shift the motor's electrical angle per step.
  
   //for( i = 0 ; i < steps ; i++)
  //{
  //  PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;
   //__delay_us(1)); // even out the clock signal, error check takes about 2uSec
    //delay(clockDelay);
    //pinMode(settings.mode2Pin, INPUT); // let on-board external pullup to 3.3V pull this pin HIGH
    // check for error
    //if(errorStat() == false) return false; // error detected, exit out of here!
    //delay(clockDelay);
  //}
  
  return errorStat();
}

bool setupMovimientoContinuo( )
{
   
   TC78H_enable_pin(true);
  //settings.byte_TMROH=byte_TMR0H;
  //settings.byte_TMROL=byte_TMR0L;
  // set CW-CWW pin (aka mode3Pin) to the desired direction
  // CW-CCW pin MODE_3 controls the rotation direction of the motor. 
  // When set to H, the current of OUT_A is output first, with a phase difference of 90Â°. 
  // When set to L, the current of OUT_B is output first with a phase difference of 90Â°
  if(settings.direction == true)
  {
    PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = HIGH; // let on-board external pullup to 3.3V pull this pin HIGH
  }
  else{
    PORT_PRODRIVER_DEFAULT_PIN_MODE_3 = LOW;
  }
   //PORT_PRODRIVER_DEFAULT_PIN_STBY=HIGH;
  //activa el contador con la frecuencia de CLK programada
  
        TMR0H=settings.byte_TMROH;
        TMR0L=settings.byte_TMROL;
        INTCONbits.TMR0IF=0;
        T0CONbits.TMR0ON = 1; //Comienza a contar 
    
  //return errorStat();
}
bool stopMovimientoContinuo( )
{
    TC78H_enable_pin(false);
    T0CONbits.TMR0ON = 0; //No vuelvas a contar hasta nueva orden
    INTCONbits.TMR0IF=0; //Flag int del contador a cero
    return errorStat();
}
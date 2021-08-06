/* 
 * File:   SparkFun_ProDriver_TC78H670FTG_Library.h
 * Author: peio.gil
 *
 * Created on 1 de julio de 2021, 21:15
 */

#ifndef SPARKFUN_PRODRIVER_TC78H670FTG_LIBRARY_H
#define	SPARKFUN_PRODRIVER_TC78H670FTG_LIBRARY_H
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

//  mapeado pins 18f4550 & IC TC78H670FTG
#define TRIS_PRODRIVER_DEFAULT_PIN_STBY   TRISBbits.TRISB1
#define TRIS_PRODRIVER_DEFAULT_PIN_EN     TRISBbits.TRISB2
#define TRIS_PRODRIVER_DEFAULT_PIN_MODE_0 TRISBbits.TRISB3
#define TRIS_PRODRIVER_DEFAULT_PIN_MODE_1 TRISBbits.TRISB4
#define TRIS_PRODRIVER_DEFAULT_PIN_MODE_2 TRISBbits.TRISB5
#define TRIS_PRODRIVER_DEFAULT_PIN_MODE_3 TRISCbits.TRISC6
#define TRIS_PRODRIVER_DEFAULT_PIN_ERROR  TRISAbits.TRISA5 
// PORTbits.RB7 configurar,si es el caso para INT on change
// step resolution modes. 
// These are used to set the MODE PINS (0:3) during begin 
// to "bootup" the driver IC in the desired mode.
// see datasheet pg 8
// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
#define _XTAL_FREQ 20000000 //Frecuencia del XTAL en la mchpfusb para los __delays 
#define PORT_PRODRIVER_DEFAULT_PIN_STBY   PORTBbits.RB1
#define PORT_PRODRIVER_DEFAULT_PIN_EN     PORTBbits.RB2
#define PORT_PRODRIVER_DEFAULT_PIN_MODE_0 PORTBbits.RB3
#define PORT_PRODRIVER_DEFAULT_PIN_MODE_1 PORTBbits.RB4
#define PORT_PRODRIVER_DEFAULT_PIN_MODE_2 PORTBbits.RB5
#define PORT_PRODRIVER_DEFAULT_PIN_MODE_3 PORTCbits.RC6
#define PORT_PRODRIVER_DEFAULT_PIN_ERROR  PORTAbits.RA5

#define INPUT  1
#define OUTPUT 0
#define HIGH   1
#define LOW    0
//CLK mode Step Resolution Select Function pg. 8
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_2 1
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_4 2
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_8 3
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_16 4
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_32 5
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_64 6
#define PRODRIVER_STEP_RESOLUTION_VARIABLE_1_128 7
#define PRODRIVER_STEP_RESOLUTION_FIXED_FULL 8
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_2 9
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_4 10
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_8 11
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_16 12
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_32 13
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_64 14
#define PRODRIVER_STEP_RESOLUTION_FIXED_1_128 15

// step resolution options
// note, these are limited by which mode you choose.
// no usada 
#define PRODRIVER_STEP_RESOLUTION_1_1 1
#define PRODRIVER_STEP_RESOLUTION_1_2 2
#define PRODRIVER_STEP_RESOLUTION_1_4 4
#define PRODRIVER_STEP_RESOLUTION_1_8 8
#define PRODRIVER_STEP_RESOLUTION_1_16 16
#define PRODRIVER_STEP_RESOLUTION_1_32 32
#define PRODRIVER_STEP_RESOLUTION_1_64 64
#define PRODRIVER_STEP_RESOLUTION_1_128 128

// statuses
// used primarily to check current status
// and avoid re-writing a pin, which causes a toggle in arduino
#define PRODRIVER_STATUS_ENABLED 1
#define PRODRIVER_STATUS_DISABLED 0
#define PRODRIVER_STATUS_STANDBY_ON 1
#define PRODRIVER_STATUS_STANDBY_OFF 0

//  Setting options for controlMode
#define PRODRIVER_MODE_CLOCKIN 0 
#define PRODRIVER_MODE_SERIAL 1

// Serial control mode settings options
#define PRODRIVER_PHASE_MINUS 0
#define PRODRIVER_PHASE_PLUS 1
#define PRODRIVER_TRQ_100 0x00
#define PRODRIVER_TRQ_75 0x01
#define PRODRIVER_TRQ_50 0x02
#define PRODRIVER_TRQ_25 0x03
#define PRODRIVER_OPD_OFF 0
#define PRODRIVER_OPD_ON 1
#define PRODRIVER_MD_FAST_37 0x00
#define PRODRIVER_MD_FAST_75 0x01
#define PRODRIVER_MD_FAST_50 0x02
#define PRODRIVER_MD_FAST_100 0x03

//  PRODRIVERSettings
//
//  This is used by the PRODRIVER class to hold settings.  It is public within that class
//  and the user is expected to write desired values into the settings before calling
//  .begin();
 typedef struct PRODRIVERSettings
{
  
	
  //Main control mode and pin number variables
    uint8_t controlMode;  //Set equal to PRODRIVER_MODE_CLOCKIN or PRODRIVER_MODE_SERIAL
    uint8_t stepResolutionMode; // only used if in CLOCKIN mode, otherwise ignored
    uint8_t stepResolution; // active resolution within bounds set by stepResolutionMode
    uint8_t byte_TMROH; //byte H del TIMER0 la frecuencia del CLOCK de pin del TC78H
    uint8_t byte_TMROL;//byte L del TIMER0 la frecuencia del CLOCK de pin del TC78H
    bool errorFlag; // true = error, false = no error
    bool enableStatus;
    bool standbyStatus;
    bool direction; // CW-CCW pin MODE_3 controls the rotation direction of the motor. 

    // Serial Mode specific settings (these are not used for CLOCKIN mode)
    bool phaseA;
    bool phaseB;
    uint16_t currentLimA; // can be only 10 bits (aka 0-1023) see datasheet pg 20
    uint16_t currentLimB; // can be only 10 bits (aka 0-1023) see datasheet pg 20
    uint8_t torque;
    bool openDetection;
    uint8_t mixedDecayA;
    uint8_t mixedDecayB;
    uint8_t phasePosition; // Used to keep track of phaseA/B to allow single steps in either direction
}PRODRIVERSettings;

void Pin_SetUp_PortB_Driver ( void );
void IniSettingsDefault( void );
  bool begin( void ); // Call to apply PRODRIVERSettings and returns ERR stat
  bool errorStat( void );
  bool step( uint16_t steps, bool direction, uint8_t clockDelay ); // returns ERR stat
  bool setupMovimientoContinuo( void );
  bool stopMovimientoContinuo( void );
  bool stepSerial( uint16_t steps, bool direction , uint8_t stepDelay ); // only 1:1 stepping, (no microstep support)
  bool changeStepResolution( uint8_t resolution ); // only works with "variable" step modes
  bool controlModeSelect(void);
  bool TC78H_enable_pin( bool enable_disable );
  bool disable( void );
  bool sendSerialCommand( void );
  bool setTorque( uint8_t newTorque );
  bool setCurrentLimit( uint16_t currentLimit );
  


//private:
  bool pinSetup();
  bool stepSerialSingle(bool direction);
//};

#endif	/* SPARKFUN_PRODRIVER_TC78H670FTG_LIBRARY_H */


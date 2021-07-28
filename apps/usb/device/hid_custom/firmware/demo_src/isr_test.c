#include <SparkFun_ProDriver_TC78H670FTG_Library.h>
#include "timers.h"
//De momento se programa para clockin del driver =100ms
//Fclk=19531Hz=>65535-0,1*19531=63582=>

extern PRODRIVERSettings settings;
void __interrupt(__low_priority) ISR_TIMER_0(void)    
                                                    // Low priority interrupt
                                                    //High priority interrupt ya estÃ¡ ocupada
{
    if (INTCONbits.TMR0IF)
    {
        TMR0H=settings.byte_TMROH;       
        TMR0L=settings.byte_TMROL;
      
        if(PORT_PRODRIVER_DEFAULT_PIN_MODE_2==HIGH)
            PORT_PRODRIVER_DEFAULT_PIN_MODE_2=LOW;
        else
            PORT_PRODRIVER_DEFAULT_PIN_MODE_2=HIGH;
    }
    INTCONbits.TMR0IF=0;
}
 


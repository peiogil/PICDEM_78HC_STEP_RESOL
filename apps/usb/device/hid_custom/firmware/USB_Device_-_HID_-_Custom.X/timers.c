#include <stdint.h>
#include <stdbool.h>
#include "timers.h"
#include <xc.h>


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
bool TIMER0_SetConfiguration(void)
{
    
     
    INTCONbits.GIE = 0;
    T0CONbits.TMR0ON=0;         //No empieces a contar hasta que se te diga
    T0CONbits.T0CS=0;           //Como Temporizador no como Contador
    T0CONbits.PSA=0;            // Habilita preescalado   
    T0CONbits.T0PS=0b111;       // divide por 256
    T0CONbits.T08BIT=0;         //Contador de 16 bits
    INTCONbits.TMR0IF=0;        // Flag del timer 0 apagado
    INTCONbits.TMR0IE=1;        //Permitir el desbordamiento del Timer
    INTCONbits.PEIE = 1;        //Permitir las interrupciones de perifericos
    INTCON2bits.TMR0IP=0;       //Timer0  low priority interrupts
    RCONbits.IPEN=1;        //Permite high y low priority interrupts
    INTCONbits.GIEL=1;//Permite prioridad de bajo nivel
    INTCONbits.GIE = 1; //Permitir interrupciones
      

    return false;
}


/*******************************************************************************
 End of File
*/
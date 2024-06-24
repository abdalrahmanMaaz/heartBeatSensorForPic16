#include <xc.h>
#include <stdint.h>
#include "tmr0.h"

const uint8_t tmr0_mask = 0xFF;

void TMR0_Initialize(void) {
    

    
    //OPTION_REG = 0x04;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 1;
    OPTION_REGbits.PSA = 0;             
    OPTION_REGbits.PS = 0x07;

    TMR0 = (uint8_t)(tmr0_mask & (256-(((2 *_XTAL_FREQ)/(256*4))/1000)));     
                                                                 
    INTCONbits.TMR0IF = 0;
}


void TMR0_StartTimer(void) {
   
    INTCONbits.TMR0IE = 1;
}

void TMR0_StopTimer(void) {
    
    INTCONbits.TMR0IE = 0;
}

void TMR0_ISR(void) {
    static volatile uint16_t CountCallBack = 0;

    INTCONbits.TMR0IE = 0;
   
    INTCONbits.TMR0IF = 0;

    
    TMR0 = (uint8_t)(tmr0_mask & (256-(((2 *_XTAL_FREQ)/(256*4))/1000)));    
    
	                                                        
    if (++CountCallBack >= TMR0_INTERRUPT_TICKER_FACTOR)
    {
        
        timer_isr();

        
        CountCallBack = 0;
    }
    
    
    INTCONbits.TMR0IE = 1;
}

#include <xc.h>
#include "eusart1.h"


void EUSART1_Initialize(void) {
    TRISC=0x80;     
  	TXSTA=0x20;      
	RCSTA=0x90;      
	SPBRG=31;        
    RCSTAbits.CREN=1;
  }

uint8_t EUSART1_Read(void) {

    while (PIR1bits.RCIF==0); {
    }
    return RCREG;
    PIR1bits.RCIF=0;
}

void EUSART1_Write(uint8_t txData) {
    while (0 == PIR1bits.TXIF) {
    }

    TXREG = txData; 
}

void put_string(const unsigned char* str) {
    while (*str != NULL) {
        while (0 == PIR1bits.TXIF) {
        }

        TXREG = *str++; 
    }
}
void UART_RxString(char *string_ptr)
 {
     char ch;
     while(1)
       {
          ch=EUSART1_Read();    
 
        if((ch=='\r') || (ch=='\n')) 
           {				     
              *string_ptr=0;           
                break;			     
             }
         *string_ptr=ch;               
         string_ptr++;			    
      }
 }

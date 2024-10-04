#include <xc.h>
#include "timer0.h"

/* Config Timer0 */
void TIMER0_Initialize(void)
{
	/* Timer0 disabled; 16-bit; no postscaler */
	T0CON0 = 0x10;
    
    /* HFINTOSC; counter not synchronized; prescaler 1:256 */
	T0CON1 = 0x7E;   
}

void TIMER0_Delay(void)
{
	
	/* Load TMR0 with initial value 0BDB(hex) = 3035(dec) */
    /* TIMER0_time = (1/TMR0_clock_source) x (end_value - initial_value) x prescaler */
    /*             = (1/64MHz ) x (65535-3035) x 256 = 250 ms */
	TMR0H = 0x0B;
	TMR0L = 0xDB;

    /* Timer0 enabled */
	T0CON0 |= 0x80; 
                 
    /* Wait for TMR0IF = 1 */
    while ((PIR3 & 0x80) != 0x80)
          ;
        
    /* Clear TMR0IF bit */
    PIR3 &= 0x7F;
             
    /* Timer0 disabled */
	T0CON0 &= 0x7F;
}
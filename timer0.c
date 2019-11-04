#include "Timer0.h"
#include <math.h>

// Timer 0 initialize set up
void TIMER0_Initialize(void) {
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.GIE = 1;
    T0CON = 0x57; // 0b 0101 0111
    TMR0L = 177;
}

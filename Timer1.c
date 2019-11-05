#include "Timer1.h"
#include <math.h>

// Timer 1 initialize set up
void TIMER1_Initialize(void) {
    T1CON = 0x0F;
    TMR1H = 0x80;
    TMR1L = 0x00;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
}

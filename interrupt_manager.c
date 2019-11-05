#include "interrupt_manager.h"
// Interrupt routine
void __interrupt() ISR(void) {
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        TMR0L = 0;
    }
}

#include "interrupt_manager.h"
// Interrupt routine
void __interrupt() ISR(void) {
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        button();
        if (State != MODIFY_SECOND)
            normal_clock();
        if (flag == 1) {
            stop_watch();
        }
        TMR0L = 177;
    }
}

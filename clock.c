#include "clock.h"

int start_timer(unsigned char *timer_vaddr) {
    T1CONbits.TMR1ON = 1;
}

int stop_timer(void) {
    T1CONbits.TMR1ON = 0;
}

timestamp_t get_time(void) {
    timestamp_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    
    readValHigh = TMR0H;
    readValLow = TMR0;
    
    readVal = ((timestamp_t) readValHigh << 8) | readValLow;
    return readVal;
}

//uint32_t register_timer(uint32_t delay, timer_callback_t callback, void *data) {
    
//}
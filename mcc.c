#include "mcc.h"

void SYSTEM_Initialize(void) {
    LCDInit();
    OSCCILATOR_Initialize();
    TIMER0_Initialize();
    Button_Initialize();
}

// Osccilator initialize set up
void OSCCILATOR_Initialize(void) {
    OSCCON = 0x77; // 0b 0111 0111 - 4 MHz 
    OSCTUNE = 0x0F;
}
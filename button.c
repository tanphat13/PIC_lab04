#include "button.h"
#include "mcc.h"
// Button initialize 
void Button_Initialize() {
    TRISAbits.TRISA5 = 1;
    TRISBbits.TRISB0 = 1;
    ADCON1 = 0x0F; // Set all the received value from port A are in digital form
}
// Function - Read button RA5 and RB0
char read_ButtonRB0() {
    firstReadRB0 = secondReadRB0;
    secondReadRB0 = PORTBbits.RB0;
    if(secondReadRB0 == firstReadRB0) {
        if (secondReadRB0 == 0) 
            return 2;
        else 
            return 1;
    }
    return 0;
}

char read_ButtonRA5() {
    firstReadRA5 = secondReadRA5;
    secondReadRA5 = PORTAbits.RA5;
    if(secondReadRA5 == firstReadRA5) {
        if (secondReadRA5 == 0) 
            return 2;
        else 
            return 1;
    }
    return 0;
}

void button() {
    check_RA5 = read_ButtonRA5();
    check_RB0 = read_ButtonRB0();
    if (check_RA5 == 2) {
        move_State = 1;
    }
    else if (check_RB0 == 2) {
        count_Up++;
        if (count_Up > pressed1s)
            count_More++;
    }
    else {
        move_State = 0;
        count_Up = 0;
        count_More = 0;
    }
}
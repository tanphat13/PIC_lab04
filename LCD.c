#include "LCD.h"

void LCDInit (void) {               // Initialize LCD
    InitBBSPI();                    // initialize SPI
    LCD_RST_TRIS = 0;               // set RF6 as output to control RESET pin
    LCD_RST = 0;                    // reset MCP23S17
    __delay_ms(LCD_delay);
    LCD_RST = 1;
    Port_BBSPIInit (PORTA_DIR);     // initialize MCP23S17 PORTA
    Port_BBSPIInit (PORTB_DIR);     // initialize MCP23S17 PORTB
    WritePort_BBSPI (PORTA_ADD, 0);
    __delay_ms(LCD_Startup);        // required by display controller to allow power to stabilize
    LCDPutInst(0x32);               // required by display initialization
    LCDPutInst(FUNCTION_SET);       // set interface size, # of lines and font
    LCDPutInst(DISPLAY_SETUP);      // turn on display and sets up cursor
    mLCD_CLEAR;                     // clear the display
    LCDPutInst(ENTRY_MODE);         // set cursor movement direction
}

void InitBBSPI (void) {     // Initialize I/O Ports for Bit Bang SPI
    LCD_CS_TRIS = 0;        // make the CS pin an output
    LCD_DIN_TRIS = 1;       // make the DIN pin an input
    LCD_DOUT_TRIS = 0;      // make the DOUT pin an output
    LCD_SCLK_TRIS = 0;      // make the SCLK pin an output

    LCD_CS = 1;             // raise the CS pin
    LCD_DIN = 1;            // set the DIN pin
    LCD_DOUT = 0;           // clear the DOUT pin
    LCD_SCLK = 0;           // clear the SCLK pin
}

void SendByteBBSPI (unsigned char output) {  // Output a byte through the DOUT pin and receives dummy datea through the DIN pin
    unsigned char bitcount;
    unsigned char input = output;
    
    for(bitcount=0;bitcount<8;bitcount++)
    {
       // transmit data MSB
        if(output & 0x80)                // condition if transmit byte MSB is 1
            LCD_DOUT = 1;                // make SDO pin output high
        else                             // condition if byte MSB is 0
            LCD_DOUT = 0;                // make SDO pin output low
        // receive dummy data
        if (LCD_DIN)                     // condition if receive byte MSB is 1
            input = (input << 1) | 0x1;  // shift input 1 bit to the left and move carry bit to LSB
        else                             // condition if receive bit is 0
            input = input << 1;          // shift input 1 bit to the left
        LCD_SCLK = 1;                           // set the SCLK pin
        NOP();NOP();NOP();NOP();NOP();NOP();    // produces ~50% duty cycle clock
        NOP();NOP();NOP();NOP();NOP();NOP();
        LCD_SCLK = 0;                           // clear the SCLK pin
        output <<= 1;                           // shift output 1 bit to the left
    }
}

void Port_BBSPIInit (unsigned char port_dir) { // Initialize MCP923S17 Portx as output
    // IOCON.BANK POR/RST Value = 0
    // Sequence = Device Opcode + Register Address + 1 Data Byte

    LCD_CS = 0;                 // lower CS to initialize SPI write operation on MCP923S17
    SendByteBBSPI(0x40);        // transmit device opcode (slave address and write enable)
    SendByteBBSPI(port_dir);    // point to address of IODIRx(I/O Direction register of PORTx)
    SendByteBBSPI(0x00);        // set all PORTx pins as output
    LCD_CS = 1;                 // end sequence
}

void WritePort_BBSPI (unsigned char port_add, unsigned char a) { // Writes to PORTx and selects between data and instruction register
    LCD_CS = 0;                 // lower CS to initialize SPI write operation on MCP923S17
    SendByteBBSPI(0x40);        // transmit device opcode (slave address and write enable)
    SendByteBBSPI(port_add);    // point to address of GPIOx (General Purpose I/O of PORTx)
    SendByteBBSPI(a);           // write value to GPIOx
    LCD_CS = 1;                 // end sequence
}

void LCDPutChar (unsigned char ch) { // Writes character to LCD at current cursor position
    __delay_ms(LCD_delay);
    WritePort_BBSPI (PORTA_ADD, data);        // prepare to send data to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTB_ADD, ch);          // write the character to be displayed
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD, send_data);   // send data to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD, 0x00);        // stop sending data to LCD
}

void LCDPutInst (unsigned char ch) { // Writes character to LCD instruction register
    __delay_ms(LCD_delay);
    WritePort_BBSPI (PORTA_ADD, instr);       // prepare to send instruction to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTB_ADD, ch);          // write the instruction to be sent to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD,send_instr);   // send instruction to LCD
    __delay_ms(1);
    WritePort_BBSPI (PORTA_ADD, 0x00);        // stop sending instruction to LCD
}

void LCDPutInst2 (unsigned char ch) { // Writes character to LCD instruction register
    __delay_ms(LCD_delay);
    WritePort_BBSPI (PORTA_ADD, instr);       // prepare to send instruction to LCD
    __delay_ms(50);
    WritePort_BBSPI (PORTB_ADD, ch);          // write the instruction to be sent to LCD
    __delay_ms(50);
    WritePort_BBSPI (PORTA_ADD,send_instr);   // send instruction to LCD
    __delay_ms(50);
    WritePort_BBSPI (PORTA_ADD, 0x00);        // stop sending instruction to LCD
}

void LCDPutStr (const char *ptr) { // Writes string to LCD at current cursor position
    while(*ptr) LCDPutChar(*(ptr++));
}
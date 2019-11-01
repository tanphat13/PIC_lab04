/* 
 * File:   LCD.h
 * Author: phat
 *
 * Created on October 28, 2019, 9:33 AM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "mcc.h"

#define LCD_delay           0                                // ~5mS
#define LCD_Startup         15     

// Command set for LCD display controller
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_CURSOR_BACK     0x10
#define LCD_CURSOR_FWD      0x14
#define LCD_PAN_LEFT        0x18
#define LCD_PAN_RIGHT       0x1C
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_BLINK    0x0F
#define LCD_CURSOR_LINE1    0x80
#define LCD_CURSOR_LINE2    0xC0

// Macros recommended for new labs
#define mOPEN_LCD           LCDInit()
#define mLCD_PAN_RIGHT      LCDPutInst(LCD_PAN_RIGHT)
#define mLCD_PAN_LEFT       LCDPutInst(LCD_PAN_LEFT)
#define mLCD_CURSOR_BLINK   LCDPutInst2(LCD_CURSOR_BLINK)
#define mLCD_HOME           LCDPutInst(LCD_HOME)
#define mLCD_CLEAR          LCDPutInst(LCD_CLEAR)

#define mCURSOR_ON          LCDPutInst(LCD_CURSOR_ON)
#define mCURSOR_OFF         LCDPutInst(LCD_CURSOR_OFF)
#define mCURSOR_FWD         LCDPutInst(LCD_CURSOR_FWD)
#define mCURSOR_BACK        LCDPutInst(LCD_CURSOR_BACK)
#define mCURSOR_LINE1       LCDPutInst(LCD_CURSOR_LINE1)
#define mCURSOR_LINE2       LCDPutInst(LCD_CURSOR_LINE2)

// Common legacy macros
#define LCDHome()           LCDPutInst(LCD_HOME)            // legacy support
#define LCDClr()            LCDPutInst(LCD_CLEAR)           // legacy support
#define LCDPutChar          LCDPutChar                      // legacy support

#define PORTA_DIR               0x00        // I/O Direction register of PORTA
#define PORTB_DIR               0x01        // I/O Direction register of PORTB
#define PORTA_ADD               0x12        // address of General Purpose I/O of PORTA
#define PORTB_ADD               0x13        // address of General Purpose I/O of PORTB

// Display controller setup commands
#define FUNCTION_SET        0x3C                         // 8 bit interface, 2 lines, 5x8 font
#define ENTRY_MODE          0x06                         // increment mode
#define DISPLAY_SETUP       0x0C                         // display on, cursor off, blink offd

// selecting between instruction register or data register
#define instr        0x00
#define data         0x80

// to send instruction or data to LCD
#define send_instr   0x40
#define send_data    0xC0

// These #defines create the pin connections to the LCD in case they are changed on a future demo board
#define LCD_CS          LATAbits.LATA2          //LCD chip select
#define LCD_CS_TRIS     TRISAbits.TRISA2        //LCD chip select
#define LCD_RST         LATFbits.LATF6          //LCD hardware reset
#define LCD_RST_TRIS    TRISFbits.TRISF6        //LCD hardware reset
#define LCD_DOUT        LATCbits.LATC5          //Serial Data Output pin
#define LCD_DOUT_TRIS   TRISCbits.TRISC5        //Serial Data Output pin
#define LCD_DIN         LATCbits.LATC4          //Serial Data Input pin
#define LCD_DIN_TRIS    TRISCbits.TRISC4        //Serial Data Input pin
#define LCD_SCLK        LATCbits.LATC3          //Serial Clock pin
#define LCD_SCLK_TRIS   TRISCbits.TRISC3        //Serial Clock pin

void LCDInit(void); // Initialize LCD
void InitBBSPI(void); // Initialize I/O Ports for Bit Bang SPI
void SendByteBBSPI(unsigned char output); // Output a byte through the DOUT pin and receives dummy datea through the DIN pin
void Port_BBSPIInit(unsigned char port_dir); // Initialize MCP923S17 Portx as output
void WritePort_BBSPI(unsigned char port_add, unsigned char a); // Writes to PORTx and selects between data and instruction register
void LCDPutChar(unsigned char); // Writes character to LCD at current cursor position
void LCDPutInst(unsigned char); // Writes character to LCD instruction register
void LCDPutInst2(unsigned char);
void LCDPutStr(const char *); // Writes string to LCD at current cursor position

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */


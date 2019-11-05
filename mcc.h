/* 
 * File:   mcc.h
 * Author: phat
 *
 * Created on September 28, 2019, 2:21 PM
 */

#ifndef MCC_H
#define	MCC_H

// Configuration 
#ifdef _18F8722
#pragma config  OSC = HSPLL
#pragma config 	FCMEN = OFF
#pragma config 	IESO = OFF
#pragma config 	PWRT = OFF
#pragma config 	BOREN = OFF
#pragma config 	WDT = OFF
#pragma config 	MCLRE = ON
#pragma config 	LVP = OFF
#pragma config 	XINST = OFF
#endif

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "interrupt_manager.h"
#include "button.h"
#include "LCD.h"
#include "Timer1.h"
#include "clock.h"
#include "link_list.h"

typedef unsigned long int timestamp_t;
typedef unsigned long int timer_callback_t;

//#define _XTAL_FREQ  1000000
#define _XTAL_FREQ  10000000

// Define condition state
#define pressed1s 100
#define auto_time 10

// Global Variable
/* button variable */
int counter;
char firstReadRA5 = 1;
char secondReadRA5 = 1;
char firstReadRB0 = 1;
char secondReadRB0 = 1;
char check_RA5 = 0;
char check_RB0 = 0;
bool move_State = 0;
int count_Up = 0;
int count_More = 0;
bool flag = 0;
/* clock variable */
unsigned char centisecond_Clock = 0; // 1/100 second
unsigned char second_Clock = 0;
unsigned char  minute_Clock = 0;
unsigned char hour_Clock = 0;
unsigned char character = 0;
unsigned char centisecond_StopWatch = 0;
unsigned char second_StopWatch = 0;
unsigned char minute_StopWatch = 0;

// State 
enum {NORMAL_CLOCK,MODIFY_HOUR,MODIFY_MINUTE,MODIFY_SECOND,STOP_WATCH,/*AUTO_INCREASE*/} State;

void SYSTEM_Initialize(void);
void OSCCILATOR_Initialize(void);
#endif	/* MCC_H */


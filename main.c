/* 
 * File:   main.c
 * Author: phat
 *
 * Created on September 23, 2019, 10:36 AM
 */
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "mcc.h"
/*
 * 
 */
int main(int argc, char** argv) {
    SYSTEM_Initialize();
    while (1) {
        switch(State) {
            case NORMAL_CLOCK: {
                disp_Clock();
                if (check_RA5 == 2) {
                    character = 1;
                    State = MODIFY_HOUR;
                }
                break;
            }
            case MODIFY_HOUR: {
                if (count_Up > 0 && count_Up <= pressed1s) {
                    hour_Clock++;
                }
                if (count_More > auto_time) {
                    hour_Clock++;
                    count_More = 0;
                }
                if (hour_Clock > 23) {
                    hour_Clock = 0;
                }
                set_Clock();
                if (check_RA5 == 2) {
                    character = 2;
                    State = MODIFY_MINUTE;
                }
                break;
            }
            case MODIFY_MINUTE: {
                if (count_Up > 0 && count_Up <= pressed1s) {
                    minute_Clock++;   
                }
                if (count_More > auto_time) {
                    minute_Clock++;
                    count_More = 0;
                }
                if (minute_Clock > 59) {
                    minute_Clock = 0;
                    hour_Clock++;
                }
                set_Clock();
                if (check_RA5 == 2) {
                    character = 3;
                    State = MODIFY_SECOND;
                }
                break;
            }
            case MODIFY_SECOND: {
                if (count_Up > 0 && count_Up <= pressed1s) {
                    second_Clock++;
                }
                if (count_More > auto_time) {
                    second_Clock++;
                    count_More = 0;
                }
                if (second_Clock > 59) {
                    second_Clock = 0;
                    minute_Clock++;
                }
                set_Clock();
                if (check_RA5 == 2) { 
                        character = 0;
                        State = STOP_WATCH;
                }
                break;
            }
            case STOP_WATCH: {
                if (count_Up > 0) { 
                    if (!flag)
                        flag = 1; // run stop watch
                    else
                        flag = 0; // stop stop watch
                }
                disp_StopWatch();
                if (check_RA5 == 2) { 
                        reset_StopWatch();
                        State = NORMAL_CLOCK;
                }
                break;
            }
        }
    }
    return 0;
}


/* 
 * File:   clockk.h
 * Author: phat
 *
 * Created on October 28, 2019, 9:15 AM
 */

#ifndef CLOCKK_H
#define	CLOCKK_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "mcc.h"
int start_timer(unsigned char *timer_vaddr); // initialize the driver. start internal counter
timestamp_t get_time(void); // read the current time in millisec from internal counter
uint32_t register_timer(uint64_t delay, timer_callback_t callback, void *data); 
int remove_timer(uint32_t id);
int stop_timer(void);
int timer_ISR();


#ifdef	__cplusplus
}
#endif

#endif	/* CLOCKK_H */


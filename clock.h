/* 
 * File:   clock.h
 * Author: phat
 *
 * Created on September 29, 2019, 1:48 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include "mcc.h"
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus 
extern "C" {
   
#endif
   typedef struct {
      timer_callback_t pTask();
      uint32_t Delay;
      
   }register_data;
   
   #define MAX_REGISTER 10
   register_data register_G[MAX_REGISTER];
   
   int start_timer(unsigned char *timer_vaddr);
   timestamp_t get_time(void);
   uint32_t register_timer(uint32_t delay, timer_callback_t callback, void *data);
   int remove_timer(uint32_t id);
   int stop_timer(void);
   int timer_ISR();
   
#ifdef __cplusplus
}
#endif
#endif	/* CLOCK_H */


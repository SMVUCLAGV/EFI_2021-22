#include "timer.h"
#include <stdint.h>

void timers_init();
	// initialize all timers: injection timer, calculation flag timer, hid flag timer

#define SYSTIME_TO_US 

// time since the system turned on (miscros())
uint64_t timer_systime(){
    return micros();
}

// Injection Timer
void timer_inj_attachint(void (*f)());
	// attach interrupt function
void timer_inj_setperiod(uint32_t period);
	// set the period for injection timer
void timer_inj_start();

// Calculation Flag Timer
void timer_calc_attachint(void (*f)());
	// attach interrupt function
void timer_calc_setperiod(uint32_t period);
	// set the period for injection timer
void timer_calc_start();

// hid Flag Timer
void timer_hid_attachint(void (*f)());
	// attach interrupt function
void timer_hid_setperiod(uint32_t period);
	// set the period for injection timer
void timer_hid_start();
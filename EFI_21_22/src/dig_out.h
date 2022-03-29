#ifndef DIG_OUT_H
#define DIG_OUT_H

#include <stdint.h>

// setup each output pin to be an output. Setup PWM timer here!
void dig_out_init();

// writes to digital sensor with 
void dig_out_write(uint32_t m_dig_out_sensor, uint32_t m_dig_out_state);

// return the most recent state written to pin
void dig_out_read(uint32_t m_dig_out_sensor, uint32_t* value, uint32_t* timestamp);

// write a PWM duty cycle to the specified sensor. Period for PWM should be 20 ms.
void dig_out_writepwm(uint32_t m_dig_out_sensor, double dutyCycle);


#endif
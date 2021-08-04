#ifndef DIG_OUT_H
#define DIG_OUT_H

void dig_out_init();
	// setup each output pin to be an output. Setup PWM timer here!

#define M_DIG_OUT_LOW 0
#define M_DIG_OUT_HIGH 1
void dig_out_write(uint32_t m_dig_out_sensor, uint32_t m_dig_out_state);
	// writes to digital sensor with 

void dig_out_read(uint32_t m_dig_out_sensor, uint32_t* value, uint32_t* timestamp);
	// return the most recent state written to pin

void dig_out_writepwm(uint32_t m_dig_out_sensor, double dutyCycle);
	// write a PWM duty cycle to the specified sensor. Period for PWM should be 20 ms.


#endif
#include "dig_out.h"
#include "timer.h"

// setup each output pin to be an output. Setup PWM timer here!
void dig_out_init(){
    return;
}

// writes to digital sensor with 
void dig_out_write(uint32_t m_dig_out_sensor, uint32_t m_dig_out_state){
    digitalWrite(m_dig_out_sensor, m_dig_out_state);
}


// return the most recent state written to pin
void dig_out_read(uint32_t m_dig_out_sensor, uint32_t* value, uint32_t* timestamp){
    value = digitalRead(m_dig_out_sensor);
    timestamp = timer_systime();
}


// write a PWM duty cycle to the specified sensor. Period for PWM should be 20 ms.
//  dutyCycle is [0, 1)
void dig_out_writepwm(uint32_t m_dig_out_sensor, double dutyCycle){
    analogWrite(m_dig_out_sensor, (uint32_t)(dutyCycle * 255));
}
	
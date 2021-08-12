#ifndef DIG_IN_H
#define DIG_IN_H

#include <stdint.h>

#define DIG_IN_DEREF(U_32_BIT_VEC, M_DIG_IN_SENSOR) ((U_32_BIT_VEC >> M_DIG_IN_SENSOR) | 1)

// setup each input pin to be an input
void dig_in_init();

// captures values form the GPIO, logging timestamp
void dig_in_meas();

// returns digital read from given sensor (pass by reference). (Use a switch case to read from each sensor)  
void dig_in_read(uint32_t m_dig_in_sensor, uint32_t* value, uint32_t* timestamp);


#define M_INT_RISING 0
#define M_INT_FALLING 1
#define M_INT_BOTH 2
void dig_in_attachint(uint32_t m_dig_in_sensor, void (*func)(), uint32_t m_int_type);

#endif // DIG_IN_H
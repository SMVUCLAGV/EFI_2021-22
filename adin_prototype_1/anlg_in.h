#ifndef ANLG_IN_H
#define ANLG_IN_H

#include <stdint.h>

  // initializes input pins
void anlg_in_init(); 
  // tells the ADC to start making measurements
void anlg_in_meas(); 
  // output value after conversion, switch to read from each sensor like dig_in. The values received here will be converted to usable units (e.g. kPa)
void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp); 
uint32_t validVals;
uint32_t fetchVals;
uint32_t convTime;

#endif // ANLG_IN_H
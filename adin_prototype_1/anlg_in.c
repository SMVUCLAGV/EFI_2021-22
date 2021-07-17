#include "anlg_in.h"
#include "flags.h"

static double arr[2
void anlg_in_init(){
  pinMode(ADC_nCNVST_PIN, OUTPUT);
  digitalWrite(ADC_nCNVST_PIN, HIGH);

  // End-of-Conversion Pin, Attach Interrupt
  attachInterrupt(digitalPinToInterrupt(ADC_nEOC_PIN), dummy, FALLING);
  detachInterrupt(digitalPinToInterrupt(ADC_nEOC_PIN));
  attachInterrupt(digitalPinToInterrupt(ADC_nEOC_PIN), handle_EOC, FALLING);

  // Setup SPI
  pinMode(ADC_nCS_PIN, OUTPUT);
  digitalWrite(ADC_nCS_PIN, HIGH);
}
  // initializes input pins
void anlg_in_meas(){
  FLAG_CLR(FLAG_ANLG_IN_VALID);
} 
  // tells the ADC to start making measurements
void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp); 
  // output value after conversion, switch to read from each sensor like dig_in. The values received here will be converted to usable units (e.g. kPa)
void anlg_in_readall(double* value_a, uint32_t* timestamp); 
  // returns an array of doubles, dereference using the macros

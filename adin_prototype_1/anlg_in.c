#include "anlg_in.h"
#include "flags.h"
#include "sensors.h"

static double arr[M_ANLG_IN_NUM_SENSORS];

  // initializes input pins
void anlg_in_init(){
  pinMode(ADC_nCNVST_PIN, OUTPUT); digitalWrite(ADC_nCNVST_PIN, HIGH); 
  // End-of-Conversion Pin, Attach Interrupt
  attachInterrupt(digitalPinToInterrupt(ADC_nEOC_PIN), dummy, FALLING);
  detachInterrupt(digitalPinToInterrupt(ADC_nEOC_PIN));
  attachInterrupt(digitalPinToInterrupt(ADC_nEOC_PIN), handle_EOC, FALLING);

  // Setup SPI
  pinMode(ADC_nCS_PIN, OUTPUT);
  digitalWrite(ADC_nCS_PIN, HIGH);
}

 
  // tells the ADC to start making measurements
void anlg_in_meas() {
  _FLAG_CLR(FLAG_ANLG_IN_READY);
  // Get Conversion Time
  convTime = timer_systime();

  // Pull CNVST low for atleast 40 ns to start conversion
  digitalWrite(ADC_nCNVST_PIN, LOW);
  unsigned long temp = timer_systime();
    
  while(timer_systime() < temp + 1); // waiting 100 ns (CHANGE TO TIMER?)
  digitalWrite(ADC_nCNVST_PIN, HIGH);
  validVals = 0;
} 

// output value after conversion, switch to read from each sensor like dig_in. The values received here will be converted to usable units (e.g. kPa)
void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp)
  {
    switch(m_anlg_in_sensor){
      case M_ANLG_IN_ECT:

    }
  }

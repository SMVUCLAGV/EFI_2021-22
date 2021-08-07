#include "anlg_in.h"
#include "flags.h"
#include "sensors.h"
#include "spi.h"
#include "pins.h"

#include <Arduino.h>

#define ANLG_IN_FLAG_VALID_DATA 0
#define ANLG_IN_FLAG_

static double arr[M_ANLG_IN_NUM_SENSORS];
static uint64_t convTime;
static uint32_t validVals;
static uint32_t fetchVals;
struct spi* spi_adc;

  // initializes input pins
void anlg_in_init(){
  
  pinMode(M_PIN_ADC_nCNVST_PIN, OUTPUT); digitalWrite(M_PIN_ADC_nCNVST_PIN, HIGH); 
  // End-of-Conversion Pin, Attach Interrupt
  attachInterrupt(digitalPinToInterrupt(M_PIN_ADC_nEOC_PIN), anlg_in_dummy, FALLING);
  detachInterrupt(digitalPinToInterrupt(M_PIN_ADC_nEOC_PIN));
  attachInterrupt(digitalPinToInterrupt(M_PIN_ADC_nEOC_PIN), anlg_in_eoc, FALLING);

  // Setup SPI
  pinMode(M_PIN_ADC_nCS_PIN, OUTPUT);
  digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);
}

 
  // tells the ADC to start making measurements
void anlg_in_meas() {
  f.ANLG_IN_READY = 0;
  // Get Conversion Time
  convTime = timer_systime();

  // Pull CNVST low for atleast 40 ns to start conversion
  digitalWrite(M_PIN_ADC_nCNVST_PIN, LOW);
  unsigned long temp = timer_systime();
    
  while(timer_systime() < temp + 1); // waiting 100 ns (CHANGE TO TIMER?)
  digitalWrite(M_PIN_ADC_nCNVST_PIN, HIGH);
  validVals = 0;
} 

// output value after conversion, switch to read from each sensor like dig_in. The values received here will be converted to usable units (e.g. kPa)
void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp){
  if (validVals) {
    int data;
    unsigned long temp;
    if (fetchVals) {
        // Read from ADC's FIFO
      data = 0;
        
      comm_spi_begin(spi_adc);     // Get and store values from ADC FIFO
      digitalWrite(M_PIN_ADC_nCS_PIN, LOW);       // Select ADC
      data |= ((int)comm_spi_read(spi_adc) << 8);  // MSBs first
      digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);      // De-Select ADC
      comm_spi_end(spi_adc);

      temp = timer_systime();
      while(timer_systime() < temp + 5);

      comm_spi_begin(spi_adc);     // Get and store values from ADC FIFO
      digitalWrite(M_PIN_ADC_nCS_PIN, LOW);       // Select ADC
      data |= (int)comm_spi_read(spi_adc);         // LSBs next
      digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);      // De-Select ADC
      comm_spi_end(spi_adc);

      fetchVals = 0;
    }

    timestamp = temp;
    //will figure out specific outputs for each sensor later
    switch(m_anlg_in_sensor){
      case M_ANLG_IN_ECT:
        value = data;
      case M_ANLG_IN_IAT:
        value = data;
      case M_ANLG_IN_MAP:
        value = data;
      case M_ANLG_IN_O2:
        value = data;
      case M_ANLG_IN_TPS:
        value = data;
    }
  }
}
        value = data;
    }
  }
}

void anlg_in_eoc(){
  validVals = 1;
  fetchVals = 1;
}

void anlg_in_dummy(){
  return;
}
#include "anlg_in.h"
#include "flags.h"
#include "sensors.h"
#include "spi.h"
#include "pins.h"
#include "timer.h"
#include "max11624_adc.h"

#include <Arduino.h>

static double arr[M_ANLG_IN_NUM_SENSORS]; //array storing analog in sensor values
static uint64_t convTime; //stores the timestamp of the most recent SPI reading
static uint32_t validVals; //boolean, whether the values read are valid
static uint32_t fetchVals; //boolean, whether values are available to be fetched

  // initializes input pins
void anlg_in_init(){
  Serial.println("anlg_in setup starting");
  pinMode(M_PIN_ADC_nCNVST_PIN, OUTPUT); 
  digitalWrite(M_PIN_ADC_nCNVST_PIN, HIGH); 

  // End-of-Conversion Pin, Attach Interrupt
  attachInterrupt(digitalPinToInterrupt(M_PIN_ADC_nEOC_PIN), anlg_in_dummy, FALLING);
  detachInterrupt(digitalPinToInterrupt(M_PIN_ADC_nEOC_PIN));
  attachInterrupt(digitalPinToInterrupt(M_PIN_ADC_nEOC_PIN), anlg_in_eoc, FALLING);

  // Setup SPI
  pinMode(M_PIN_ADC_nCS_PIN, OUTPUT);
  digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);

  comm_spi_init();

  // MAX11624  Setup
  comm_spi_begin();

    // Select ADC
  digitalWrite(M_PIN_ADC_nCS_PIN, LOW);
    // Write to conversion, setup, and avg registers
  comm_spi_write(MAX11624_CONV_REG);
  comm_spi_write(MAX11624_SETUP_REG);
  comm_spi_write(MAX11624_AVG_REG);
    // De-Select ADC
  digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);

  comm_spi_end();
  Serial.println("anlg_in setup complete");
}

 
  // tells the ADC to start making measurements
void anlg_in_meas() {
  Serial.println("anlg_in measure starting");
  f.ANLG_IN_READY = 0;

  // Get Conversion Time
  convTime = timer_systime();

  // Pull CNVST low for atleast 40 ns to start conversion
  digitalWrite(M_PIN_ADC_nCNVST_PIN, LOW);
  unsigned long temp = timer_systime();
    
  while(timer_systime() < temp + 1); // waiting 100 ns (CHANGE TO TIMER?)
  digitalWrite(M_PIN_ADC_nCNVST_PIN, HIGH);
  validVals = 0;

  Serial.println("anlg_in measure complete");
} 

// output value after conversion, switch to read from each sensor like dig_in. The values received here will be converted to usable units (e.g. kPa)
void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp){
  Serial.println("anlg_in read starting");

  if (validVals) {
    if (fetchVals) {
      //fetchVals = true, validVals = true
      // Read from ADC's FIFO
      int data;
      int i = 0;
      //Read from all available sensors
      for (; i < M_ANLG_IN_NUM_SENSORS; i++){
        data = 0;

        comm_spi_begin();     // Get and store values from ADC FIFO
        digitalWrite(M_PIN_ADC_nCS_PIN, LOW);       // Select ADC
        data |= ((uint32_t)comm_spi_read()) << 6;   // MSBs first
        digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);      // De-Select ADC
        comm_spi_end();

        unsigned long temp = timer_systime();
        while(timer_systime() < temp + 5);

        comm_spi_begin();     // Get and store values from ADC FIFO
        digitalWrite(M_PIN_ADC_nCS_PIN, LOW);       // Select ADC
        data |= ((uint32_t)comm_spi_read()) >> 2;        // LSBs next
        digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);      // De-Select ADC
        comm_spi_end();

        Serial.print("ANLG_IN: Value received: ");
        Serial.print(data);
        Serial.print(" at channel: ");
        Serial.print(i);
        Serial.println(" in for loop");
        arr[i] = (double) data;
      }
      //Read from other channels that are not connected to a set sensor, since the ADC has 16 channels
      for (; i < 16; i++){
        data = 0;

        comm_spi_begin();     // Get and store values from ADC FIFO
        digitalWrite(M_PIN_ADC_nCS_PIN, LOW);       // Select ADC
        data |= ((uint32_t)comm_spi_read()) << 6;   // MSBs first
        digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);      // De-Select ADC
        comm_spi_end();

        unsigned long temp = timer_systime();
        while(timer_systime() < temp + 5);

        comm_spi_begin();     // Get and store values from ADC FIFO
        digitalWrite(M_PIN_ADC_nCS_PIN, LOW);       // Select ADC
        data |= ((uint32_t)comm_spi_read()) >> 2;        // LSBs next
        digitalWrite(M_PIN_ADC_nCS_PIN, HIGH);      // De-Select ADC
        comm_spi_end();

        Serial.print("ANLG_IN: Value received: ");
        Serial.print(data);
        Serial.print(" at channel: ");
        Serial.print(i);
        Serial.println(" in for loop");
      }

      fetchVals = 0;
    }
    else {
      //fetchVals = false, validVals = true
      Serial.println("No action, validVals is true but fetchVals is false");
    }

    *timestamp = convTime;
    *value = arr[m_anlg_in_sensor];
    Serial.println("anlg_in read complete - successful");
    return;
  } 

  //ERROR CHANNELS
  for (int i = 0; i < M_ANLG_IN_NUM_SENSORS; i++){
    arr[i] = -1;
  }
  *timestamp = timer_systime();
  *value = arr[m_anlg_in_sensor];
  Serial.println("anlg_in read complete - validVals is FALSE");
  
}

void anlg_in_eoc(){
  validVals = 1;
  fetchVals = 1;
}

void anlg_in_dummy(){;}

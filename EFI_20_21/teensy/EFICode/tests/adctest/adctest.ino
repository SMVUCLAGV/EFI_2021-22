// Test file for adc class
#include "spi_adc.h"

SPI_ADC* a;

char str[100];
const int * data = a->getChannels();

void setup() {
  Serial.begin(115200);
  while(!Serial);
  a = new SPI_ADC();

//// Test code
//  // Conversion Start Pin
//  pinMode(ADC_nCNVST_PIN, OUTPUT);
//  digitalWrite(ADC_nCNVST_PIN, HIGH);
//
//  // Setup SPI
//  pinMode(ADC_nCS_PIN, OUTPUT);
//  digitalWrite(ADC_nCS_PIN, HIGH);
//
//  SPI.begin();
//
//  
//  SPISettings SPI_PARAMS(1000000, MSBFIRST, SPI_MODE0); // 1 MHz, MODE0
//  SPI.beginTransaction(SPI_PARAMS);
//
//  // Select ADC
//  digitalWrite(ADC_nCS_PIN, LOW);
//    // Write to conversion, setup, and avg registers
//  SPI.transfer(MAX11624_CONV_REG);
//  SPI.transfer(MAX11624_SETUP_REG);
//  SPI.transfer(MAX11624_AVG_REG);
//    // De-Select ADC
//  digitalWrite(ADC_nCS_PIN, HIGH);
//
//  SPI.endTransaction();
//// Test code
}

void loop() {
// Test code
//  SPISettings SPI_PARAMS(1000000, MSBFIRST, SPI_MODE0); // 1 MHz, MODE0
//
//  // Pull CNVST low for atleast 40 ns to start conversion
//  digitalWrite(ADC_nCNVST_PIN, LOW);
//  unsigned long temp = micros();
//  while(micros() < temp + 1); // waiting 100 ns (CHANGE TO TIMER?)
//  digitalWrite(ADC_nCNVST_PIN, HIGH);
//  
//  
//  while(digitalRead(ADC_nEOC_PIN)){;}
//
//    // Read from ADC's FIFO
//  int data;
//  for (int i = 0; i < ADC_CHANNELS; i++) {
//  
//    data = 0;
//    
//    SPI.beginTransaction(SPI_PARAMS);
//    digitalWrite(ADC_nCS_PIN, LOW);
//    data |= (int(SPI.transfer(0)) << 8); // MSBs first
//    digitalWrite(ADC_nCS_PIN, HIGH);
//    SPI.endTransaction();
//
//    temp = micros();
//    while(micros() < temp + 5); // waiting 100 ns (CHANGE TO TIMER?)
//    
//    SPI.beginTransaction(SPI_PARAMS);
//    digitalWrite(ADC_nCS_PIN, LOW);
//    data |= int(SPI.transfer(0));        // LSBs next
//    digitalWrite(ADC_nCS_PIN, HIGH);
//    SPI.endTransaction();
//
//    temp = micros();
//    while(micros() < temp + 1); // waiting 100 ns (CHANGE TO TIMER?)
//    
//    valChannel[i] = data;
//  }
//
//
//  
//  
//  // Get Data once then print it
//  char str[100];
//  for (int i = 0; i < ADC_CHANNELS; i++) {
//    sprintf(str, "%06i", valChannel[i]);
//    Serial.print(str);
//    Serial.print(", ");
//  }
//  Serial.print("\n");
//  Serial.println(millis());
// Test code
  
  
  // MAX11624  Setup
  
  delay(20);
  a->refresh();

  /*// Data should be invalid here
  data = a->getChannels();
  for (int i = 0; i < ADC_CHANNELS; i++) {
    sprintf(str, "%06i", data[i]);
    Serial.print(str);
    Serial.print(", ");
  }
  Serial.print("\n");
*/
  delay(20); 
  
  // Get Data once then print it
  data = a->getChannels();
  for (int i = 0; i < ADC_CHANNELS; i++) {
    sprintf(str, "%06i", data[i]);
    Serial.print(str);
    Serial.print(", ");
  }
  Serial.print("\n");

 /* // Get Data agains to make sure it doesn't change
  data = a->getChannels();
  for (int i = 0; i < ADC_CHANNELS; i++) {
    sprintf(str, "%06i", data[i]);
    Serial.print(str);
    Serial.print(", ");
  }
  Serial.print("\n");

  Serial.println(a->getConvTime());*/
}

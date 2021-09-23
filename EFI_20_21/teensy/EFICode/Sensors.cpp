#include "Controller.h"
#include "Arduino.h"
#include "Constants.h"
#include "math.h"

// timepassed is in microseconds
long Controller::getRPM (long int timePassed, int rev) {
  return (60 * 1E6 * rev) / (timePassed);
}

//TPS Measurement
/*
const double TPSConversion = .0019685;
const double TPSOffset = -.33746;
*/
const double TPS_0Deg = 60;
const double TPS_90Deg = 865;

double Controller::getTPS() {
  unsigned long currThrottleMeasurementTime = micros();
  // calculate open throttle area (i think)
  //double newTPS = 1 - cos(((double(analogRead(TPS_Pin))-TPS_0Deg)/(TPS_90Deg - TPS_0Deg))*HALF_PI);

  double newTPS_V = sensorVals[TPS_CHAN] * voltConv;
  double newTPS = newTPS_V; //need to re-adjust TPS_0Deg and TPS_90Deg
  
  if(newTPS < 0)
    newTPS = 0;
  if(newTPS > 1)
    newTPS = 1;
  if(currThrottleMeasurementTime - lastThrottleMeasurementTime > 0)
    DTPS = (newTPS - TPS) / (currThrottleMeasurementTime - lastThrottleMeasurementTime);
  lastThrottleMeasurementTime = currThrottleMeasurementTime;
  return newTPS;
}

double Controller::computeThrottleAdjustment() { // SHOULD THIS INCORPORATE DTPS?
  // Looks at the change in throttle position and determines a proper adjusment for the fuel input.
  // DTPS
  return 1 + TPS * TPS;
}

// Identify the constant for each temperature sensor
const int IAT_INDEX = 0;
const int ECT_INDEX = 1;

//The following constants are to complete the following eq for temperature
//
// Temp = tempBeta / (ln(R) + (tempBeta/T_0 - lnR_0)) //	where R is the resistance of the sensor (found using voltage divider) //	eq from: https://en.wikipedia.org/wiki/Thermistor#B_or_%CE%B2_parameter_equation //
const double tempBetaIAT = 3988; // tolerance: {+/-1%,+/-1.5%}
const double tempBetaECT = 3988;
const double T_0 = 298.15; // temp in Kelvin at which R_0 values are taken
const double lnR_0_IAT = 9.21034; //8.45531}; // {ln(10000 (10000 +/-1%)),ln(4700 (4559 to 4841))}
const double lnR_0_ECT = 8.4849;
const double tempConstIAT = tempBetaIAT/T_0 - lnR_0_IAT;
const double tempConstECT = tempBetaECT/T_0 - lnR_0_ECT;
const double R_divIAT = 9300; // resistance of other resistor in voltage divider
const double R_divECT = 10000;

double Controller::getIAT() {
  double tempR = R_divIAT / (maxADC/sensorVals[IAT_CHAN] - 1);
  return tempBetaIAT / (log(tempR) + tempConstIAT);
}

double Controller::getECT() {
  double tempR = R_divECT / (maxADC/sensorVals[ECT_CHAN] - 1);
  return tempBetaECT / (log(tempR) + tempConstECT);
}

//MAP Measurement

// MPX4115A MAP sensor calibration
const double MAPVs = Vs_5;
const double MAPDelta = 0.045; // should be between +/- 0.0675 volts (1.5 * 0.009 * Vs where Vs is 5)
const double MAPSlope = 1E3/(MAPVs*0.009);  //Pa / Volt
const double MAPOffset = 1E3*MAPDelta/(MAPVs*0.009) + 1E3*0.095/0.009;   //Pa
const double MAPConversion = MAPSlope * voltConv;    // Pascals / 1023

double Controller::getMAP() {
  //Calculates MAP, outputs in Pa
  return MAPConversion * sensorVals[MAP_CHAN] + MAPOffset;
}

// Analog output 1 factory default settings for voltage ranges.
const double AO1minAFR = 7.35;     //grams air to grams fuel at zero Volts
const double AO1maxAFR = 22.39;    //grams air to grams fuel at five Volts
const double AO1slope = (AO1maxAFR - AO1minAFR) / (5 - 0);

// Analog output 2 factory default settings for voltage ranges
const double AO2minAFR = 14;    //grams air to grams fuel at 0.1 Volts
const double AO2maxAFR = 15;    //grams air to grams fuel at 1.1 Volts
const double AO2slope = (AO2maxAFR - AO2minAFR) / (1.1 - 0.1);

// IF O2 SENSOR IS ERRORING OR NOT READY, THE ANALOG OUTPUT IS SET TO BE EQUAL
// TO ZERO VOLTS. THEREFORE, I HAVE IMPOSED A 0.05 Volt LIMITATION ON VOLTAGES READ
// FROM THE O2 SENSOR. IF THE VOLTAGE READ IS LESS THAN 0.05 Volts, then the AFR
// FEEDBACK LOOP WILL DO NOTHING! 

// Returns the current measured AFR.
double Controller::getAFR () {
  // Gets Reading from O2 Sensor.
  
  // Calculate initial AFR reading.
  AFRVolts->addData(voltConv * sensorVals[OIN1_CHAN]);
  AFR = AFRVolts->getData() * AO1slope + AO1minAFR;
  
  // If AFR is close to stoich, use narrow band output with greater precision.
//  if (AFR <= 15 && AFR >= 14) {
//      AFR = voltageConversion * analogRead(OIN2_Pin) * AO2slope + AO2minAFR;
//  }
  
  return AFR;
}

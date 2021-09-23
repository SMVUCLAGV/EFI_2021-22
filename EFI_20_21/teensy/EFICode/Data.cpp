#include "Controller.h"
#include "Arduino.h"
#include "Constants.h"
#include "SD.h"
#include "SPI.h"

void Controller::sendCurrentData() { // THIS MUST TAKE LESS THAN 1 ms (to guaruntee micros doesn't miss an overflow)
// TODO:
// -last row and column used in tables ( maybe send back actual values used)
// -whether we are still on startup cycles
// -engine on? (or just use RPM = 0)
  char toSend [1000];
  sprintf(toSend, "%010u:%06i:%03.3f:%03.3f:%03.3f:%03.3f:%03.3f:%03.3f:%05i:%05i:%05i:%02.2f:%02.2f:%01.3f:%01i:%01i:%010u:%03.3f:%03.3f:%01i:%s:%01i:%03.3f\n", // about 97 bytes? (800-900 us)
  	micros(), 
	totalRevolutions, 
	ECT, 
	IAT, 
	MAP, 
	MAPAvg->getData(),
	TPS, 
	AFR, 
	RPM, 
  injectorPulseTime,
	lastPulse,
	scaledMAP, 
	scaledRPM,
	startupModifier,
	startingRevolutions <= numRevsForStart,
	haveInjected,
	MAPTrough,
  prevdMAP,
  MAPAvg->getGauss(),
  SDConnected,
  fileName,
  ECT > MAX_ALLOWABLE_ECT,
  AFR);

  if(SDConnected) { // open and write to file
    File logFile = SD.open(fileName, FILE_WRITE);
    logFile.write(toSend);
    logFile.close();
  }
  Serial.write(toSend);
}

void Controller::trySendingData() {
  if (currentlySendingData) {
      sendCurrentData();
      haveInjected = false;
    }
  }

// OLD CODE
/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


// OBSOLETE! KEPT FOR REFERENCE!
//void Controller::printEndingData() {
//  unsigned long sumPulse = 0;
//  int pulseUnder3000 = 0;
//  for (int i = 0; i <= 31; i++) {
//    sumPulse += totalPulse[i];
//    if (i < 16) {
//      pulseUnder3000 += totalPulse[i];
//    }
//
//    //TODO: Do this with string interpolation
//    Serial.print(String(i*RPMIncrement) + "-" + String((i+1)*RPMIncrement));
//    Serial.print(": ");
//    Serial.println(totalPulse[i]);
//  }
//  Serial.println("Total     : " + String(sumPulse));
//  Serial.println("Under 3000: " + String(pulseUnder3000));
//  Serial.end();
/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


/*
  //Sends data on each of our sensors to Serial output
  struct values {
      unsigned long frontPad = 0x80000001;
      unsigned long time;
      unsigned long totalRevs;
      float ECT;
      float IAT;
      float MAP;
      float TPS;
      float AFR;
      float totalPulseTime;
      long RPM;
      unsigned long backPad = 0x80000000;
  } values;
  //TODO: Convert to micros
  //time: %10i
  values.time = micros();
  //totalRevs: %6i
  values.totalRevs = totalRevolutions;
  //%3i and ((ect - int(ect))1000)%3i
  values.ECT = ECT;
  //%3i and ((ect - int(ect))1000)%3i
  values.IAT = IAT;
  //%3i and ((` - int(ect))1000)%3i
  values.MAP = MAP;
  values.TPS = TPS;
  values.AFR = AFR;
  values.RPM = (long) RPM;
  values.totalPulseTime = totalPulseTime;
  Serial.write((byte*)&values, 44);*/


//}

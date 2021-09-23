#include "Controller.h"
#include "Constants.h"
#include "TimerThree.h"
#include "TimerOne.h"
//#include "EEPROM.h"

Controller *c;

void setup() {
  // Construct Controller object.
  c = new Controller();

  // Update all sensor values to current values.
  c->updateRPM();
  c->readSensors();

  // Attach rpm detector to revolution counter interrupt.
  // For some reason, the internal interrupt flags can end up defaulting
  // to a triggered state before they are attached. This causes them
  // to trigger once right when they are attached. Our current workaround
  // is to attach the interrupt to a dummy function first that triggers
  // if the interrupt is already set. Then, it is safe to attach the normal interrupt.
  attachInterrupt(digitalPinToInterrupt(HES_Pin), dummy, FALLING);
  detachInterrupt(digitalPinToInterrupt(HES_Pin));
  attachInterrupt(digitalPinToInterrupt(HES_Pin), countRev, FALLING);

  // Initialize pulseOff timer.
  Timer3.initialize(1000000);

  // Attach the interrupt for INJ pulse modulation.
  // For some reason, the internal interrupt flags can end up defaulting
  // to a triggered state before they are attached. This causes them
  // to trigger once right when they are attached. Our current workaround
  // is to attach the interrupt to a dummy function first that triggers
  // if the interrupt is already set. Then, it is safe to attach the normal interrupt.
  Timer3.attachInterrupt(dummy);
  Timer3.detachInterrupt();
  Timer3.attachInterrupt(handle_pulseTimerTimeout);

  // Immediately stop the timer.
  Timer3.stop();

  // FOR CHANGING PARAMETERS WITH BUTTON PRESSES
  //attachInterrupt(digitalPinToInterrupt(2), lowerStartupMod, FALLING);
  //attachInterrupt(digitalPinToInterrupt(3), raiseStartupMod, FALLING);
  
  Timer1.attachInterrupt(dummy);
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(handle_sendData);
  
  Timer1.setPeriod(DATA_RATE_PERIOD);
  Timer1.start();
  
  pinMode(LED_1, OUTPUT);  
  digitalWrite(LED_1, LOW);
}

void loop() {
  //Update RPM if needed.
  c->updateRPM();

  // Update Controller with most recent sensor values.
  c->readSensors();
  //c->getAFR();

  // Look up injection time on each loop cycle
  c->lookupPulseTime();

  // Adjust injectorBasePulseTime[][] Values by using feedback loop with O2 sensor.
  //c->AFRFeedback();
  //c->idleRPMFeedback();
 
  // Checks the status of the engine. e.g., detects whether the engine is on or off.
  c->checkEngineState();

  // Check for commands from Serial port.
  //c->getCommand();
}

void countRev() {
  c->countRevolution();
}

void handle_pulseTimerTimeout() {
//toggle every time timer is stopped
  /*if(digitalRead(LED_1) == 0){ 
    digitalWrite(LED_1, HIGH);
  }else{
    digitalWrite(LED_1, LOW);
  }*/
  c->pulseOff();
}

void handle_sendData() {
  // Attempt to send sensor data to the DAQ system. Will only occur if the
  // currentlySendingData flag is set to true. This flag is set by sending 
  // the ID 1 signal to the controller.
  c->trySendingData();

  Timer1.start();
}

void lowerStartupMod() {
  c->lowerStartupModifier();
  Serial.println("lower");
}

void raiseStartupMod() {
  c->raiseStartupModifier();
  Serial.println("raise");
}

void dummy() {}

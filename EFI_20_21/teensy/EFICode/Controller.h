#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Constants.h"
#include "NoiseReduced.h"
#include "spi_adc.h"

class Controller {
public:
  // Constructor
  Controller();

  // Updates sensor values.
  bool readSensors();

  // Sends the current sensor values and requested parameter information.
  void sendCurrentData();

  // If the currentlySendingData flag is set and the minTimePerSampleReported
  // has passed since that last transmission, sends out a data sample.
  void trySendingData();

  // Possibly obsolete.
  void printEndingData();

  // Checks the serial read buffer for incoming bytes. If bytes are found, acts
  // according to the documentation specified in EFI Documentation.
  bool getCommand();

  // Increments the counted number of revolutions since the last RPM update.
  // Every 2nd revolution, switches the INJ_Pin to HIGH and sets a timer for
  // the amount of time equal to the most recent calculated pulse time.
  void countRevolution();

  // Updates the RPM reading by dividing the total number of revolutions since
  // the last update by the number of minutes that have passed.
  void updateRPM();

  // Performs 2D interpolation to lookup a pulse time for the given engine conditions.
  void lookupPulseTime();
  double computeThrottleAdjustment();

  // If singleVal is true, determines the pulse time for the specified cell [row][col]
  // of the AFR Table in units of microseconds times kelvin.
  // If singleVal is false, determines the pulse time for every single AFR Table value
  // in the AFR Table. In its current state, this will overwrite any adjustments that
  // the O2 sensor feedback loop has made to the base pulse times.
  void calculateBasePulseTime(bool singleVal, int row, int col);

  // Sets the currentlySendingData flag to true, allowing the controller to report
  // sampled data back to the DAQ system.
  bool startDataTransmission();

  // Sets the currentlySendingData flag to false, preventing the controller from
  // reporting sampled data back to the DAQ system.
  bool stopDataTransmission();

  // Returns true if the engine drops below the minimum RPM to consider the engine running.
  bool detectEngineOff();

  // Checks to see if the engine is on or off. If the engine switches state since the last
  // check, changes parameters accordingly.
  void checkEngineState();

  bool inStartingRevs();

  // Turns the injector on if it is not disabled.
  void pulseOn();

  // Turns the injector off.
  void pulseOff();

  // Attaches the interrupt timer for shutting the injector off and 
  // sets the INJisDisabled flag to false.
  void enableINJ();

  // Detaches the interrupt timer for shutting the injector off and
  // sets the INJisDisabled flag to true.
  void disableINJ();

  long getRPM (long int timePassed, int rev);
  double getTPS();
  double getIAT();
  double getECT();
  double getMAP();
  double getAFR();

  void initializeParameters();

  void AFRFeedback();
  void idleRPMFeedback();
  long interpolate2D(int blrow, int blcol, double x, double y);
  double doubleMap(double val, double minIn, double maxIn, double minOut, double maxOut);

  void setStartupModifier();
  void lowerStartupModifier();
  void raiseStartupModifier();
  
private:
  // Has a value of true if the timer3 interrupt is detached from the "pulseOff" function.
  // Also prevents the injector from pulsing on if true.
  SPI_ADC* adc;
  bool refreshAvailable;
  const int* sensorVals;

  bool INJisDisabled; //flag
  bool AFRFeedbackisEnabled;
  bool RPMFeedbackisEnabled;

  int revolutions; //misc
  unsigned long totalRevolutions; //misc
  unsigned long startingRevolutions; //misc
  unsigned long previousRev; //misc
  
  unsigned long totalPulseTime;//misc
  unsigned long lastPulse;
  long lastRPMCalcTime;//RPM stuff
  long injectorPulseTime;
  int delayCount;
  
  //Data Retrieval
  bool enableSendingData;
  bool currentlySendingData; // used to disable data transmission during injection
  bool haveInjected; // allows data retrieval to know when injections happened
  bool SDConnected;
  const char baseFileName[6] = "sdlog";
  char fileName[20] = "NOFILE";

  long int minTimePerSampleReported;
  long lastSerialOutputTime;
  double scaledMAP;
  double scaledRPM;
  int mapIndex;
  int rpmIndex;
  long prevDeltaRPM;

  double startupModifier;
  double throttleAdjustment;
  unsigned long lastThrottleMeasurementTime;

  int magnetsHit;
  double constModifier;
  
  long RPM;
  long desiredRPM;
  double TPS;
  double DTPS;
  double ECT;
  double IAT;
  double MAP;
  double prevdMAP;
  double prevMAP;
  unsigned long updateddMAP;
  unsigned long MAPPeak; // time of previous peak
  unsigned long MAPTrough; // time of previous trough
  const unsigned long minMAPdt = 4000; // in microseconds
  NoiseReduced* MAPAvg;
  double AFR;
  NoiseReduced* AFRVolts;
  
  //
  // For some undocumented reason they use this table to account for
  // Volumetric Efficiency so these values are more like AFR/VE
  //
  double fuelRatioTable[numTableRows][numTableCols] = 
    {
    {14.5,14.8,15.0,15.3,15.3,15.2,14.6,14.3,13.8,13.6},  // minimum pressure
    {14.5,14.8,15.0,15.3,15.3,15.2,14.6,14.3,13.8,13.6},
    {14.5,14.8,15.0,15.3,15.3,15.2,14.6,14.3,13.8,13.6},
    {14.5,14.8,15.5,15.3,16.0,16.0,15.7,14.3,13.8,13.6},
    {14.5,16.0,20.0,20.0,16.0,16.0,15.7,14.3,13.8,13.6},
    {14.5,19.0,20.0,20.0,16.0,16.0,15.7,14.3,13.8,13.6},
    {14.5,19.0,20.0,20.0,15.0,/**/15.2,14.6,14.3,13.8,13.6},//
    {14.5,14.8,20.0,20.0,15.0,/**/15.2,14.6,14.3,13.8,13.6},//
    {14.5,14.8,20.0,20.0,15.3,15.2,14.6,14.3,13.8,13.6},
    {14.5,14.8,15.0,15.3,15.3,15.2,14.6,14.3,13.8,13.6},
    {14.5,14.8,15.0,15.3,15.3,15.2,14.6,14.3,13.8,13.6}   // maximum pressure
    };
  long injectorBasePulseTimes[numTableRows][numTableCols];

  //double startupModifierTable[numPoints];
};

#endif

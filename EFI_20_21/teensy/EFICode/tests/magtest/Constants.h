#ifndef CONST_H
#define CONST_H

//Auxiliary Functions
void countRev();
void handle_pulseTimerTimeout();
void enableINJ();
void disableINJ();
void dummy();
void lowerStartupMod();

// Assign MCU Pins to GPIO Pins
#define GPIO_0  8
#define GPIO_1  7
#define GPIO_2  33
#define GPIO_3  34 // WON'T WORK ON conn board v1 *********************
#define GPIO_4  37 // WON'T WORK ON conn board v1 *********************
#define GPIO_5  38
#define GPIO_6  18
#define GPIO_7  19
#define GPIO_8  20
#define GPIO_9  21
#define GPIO_10 22
#define GPIO_11 23

// Assign Digital Peripherals
#define INJ_Pin   1 // MISLABELED ON cont board v1 Schematic (this is correct)
#define BUZZ_Pin  0 // MISLABELED ON cont board v1 Schematic (this is correct)
#define LED_1     31

#define HES_Pin // UPDATE *****************************
#define DIP_1 35
#define DIP_2 36
#define DIP_3 39
#define DIP_4 A21 // CHANGE THIS PIN IN THE FUTURE!
#define PBTN 30

// Assign Analog Sensors (from ADC Channels)
#define TPS_CHAN  0 // UPDATE ***********************
#define ECT_CHAN  4 // UPDATE ***********************
#define MAP_CHAN   // UPDATE ***********************
#define IAT_CHAN   // UPDATE ***********************
#define OIN1_CHAN  // UPDATE ***********************
#define OIN2_CHAN  // UPDATE ***********************

const double Vs_5   = 5.00; //Volts
const double Vref_5 = 4.98; // NEED TO PROPERLY MEASURE WITH FLUKE **************************
const double Vs_3v3 = 3.30; //Volts

// Multiple by this number to convert analog readings to voltages from Op amps
const double adcRef = Vref_5;
const double maxADC = 4095;
const double voltConv = adcRef / maxADC;
//const double opampVoltageDivider = 1000.0 / (1000 + 470);
//const double adcToOpampVin = adcRef / (maxADC * opampVoltageDivider);

// Constants for calculating estimated injection times.
const double engineDisplacement = 49.4E-6;    //meters^3
const double airSpecificGasConstant = 286.9;   //Joules / (kilograms * Kelvin) (from Ideal Gas / Molecular Mass of Air
const double injectorFuelRate   = 10E-3;    //kilograms per second
const double injectionConstant  = 
              engineDisplacement / (airSpecificGasConstant * injectorFuelRate);
              // meters^2 / (kilograms * microseconds * Kelvin) 
const int openTime = 1000;          // Estimated amount of time for injector to open in microseconds.

// Controls the total number of revolutions 
const int numRevsForStart = 25;

// Number of magnets the hall effect sensor must detect for one full revolution
const int numMagnets = 1;

// Define the range of values that an AFR table value can take.
const int MIN_AFR = 8;
const int MAX_AFR = 18;

// Define the range of values that the Intake air temperature can take.
const int MIN_IAT = 200;  // In Kelvin
const int MAX_IAT = 500;  // In Kelvin
const int MAX_ALLOWABLE_ECT = 400; // CHANGE********************************************************************

// Define the range of values that the Throttle Position value can take.
const int MIN_TPS = 0;
const int MAX_TPS = 1;

// Define the BAUD_RATE to communicate with.
const unsigned long BAUD_RATE = 921600; // In bits per second;
const int DATA_RATE_PERIOD = 5000; // send back data every 5 ms

// Define the range of values for RPM and Manifold Air Pressure
const int maxRPM = 8000;    // In revolutions / minute
const int minRPM = 120;     // In revolutions / minute
const unsigned long maxMAP = 120000;     // In Pa
const unsigned long minMAP = 20000;      // In Pa

const unsigned long minDelayPerRev = (1 / (8000 * (1/60))) * (1E6); // in units of microseconds
const unsigned int revsPerCalc = 5;

// Define the number of rows and number of columns for the AFR Table.
static const int numTableRows = 11;
static const int numTableCols = 10;


// Engine is considered off if it has RPM less than the minimum RPM.
const int SHUTOFF_RPM = 120;

// Minimum time that must pass per revolution before the engine can be considered off.
// Given in microseconds.
// (60 sec / min) * (10^6 microsecond / sec) * (SHUTOFF_RPM min / revolution) = (SHUTOFF_DELAY microseconds / revolution)
const unsigned long int SHUTOFF_DELAY = 1E6; // below 60 RPM is shutoff

#endif

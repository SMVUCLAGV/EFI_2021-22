#ifndef DP_H
#define DP_H

#include <stdint.h>

struct dp_s{
    //// Pre Calculation ////

    // Sensor Values (Synchronous)
    double tps;
    double ect;
    double iat;
    double map;
    
    // Sensor Values (Asynchronous)
    uint64_t revolutions;
    uint64_t lastRPMCalcTime;
    uint64_t totalRevolutions;
    uint64_t startingRevolutions;
    uint64_t previousRev;

    // Derived Sensor Values
    double mapavg;
    double dtps;



    // Flags
    uint32_t flag_eng_on : 1;// .... and so on

    // Misc

    //// Post-Calculation ////
    struct dp_calc_s;
        //unsigned long injectorPulseTime;
        //unsigned long totalPulseTime;
        //unsigned long lastPulse;
};

struct dp_calc_s{
};


struct dp_s dp_array[10];
struct dp_s * dp_itr;
int dp_counter;

// will set up interrupts for RPM and speedometer
void dp_init();

void dp_reset();
//resets iterator to first dp, for use after terminal has copied over all data to be sent

//dp_itr = dp_array[0];

void dp_tosend(const struct dp_s** ptrdp, uint32_t* numdp);
//a pointer to the first dp and the number of dps accumulated

//ptrdp* = dp_array[0];

void dp_adv();
// Advances iterator for dp location. turns the current data product into a 'blank slate' (for variables where this is relevant).

//dp_itr++;
//dp_itr->data = 0;

void dp_update();
//read sensor values and do any filtering/processing (e.g. MAP_AVG)

const struct dp_s* dp_curr();
//gives a pointer to the current data product. (so pvnrt can access theses values)

// return dp_itr;

void dp_store_pvnrt(const struct dp_calc_s*); // NEEDS PARAMS
//need a way to store pvnrt's (or any other data) into a single data product

void dp_store_misc();
//need a place to store stuff for miscellaneous data (such as last injection time, etc.)


#endif
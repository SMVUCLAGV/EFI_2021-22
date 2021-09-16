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


//maintaining two arrays that store dp structs. When one is requested by the serial monitor, it is sent and we initiate the
//other dp array at that instant to minimize the delay for the first dp to be copied and sent back before being able to
//collect data again. 
struct dp_s dp_arr1[10];
struct dp_s dp_arr2[10];

//keeping track of the current dp, value can be 1 for dp_arr1 or 2 for dp_arr2
uint32_t cur_dp;
//iterator that points to the current dp element in either of the dp arrays
struct dp_s * dp_itr;
// the amount of unsent dp to send
uint32_t dp_counter;

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
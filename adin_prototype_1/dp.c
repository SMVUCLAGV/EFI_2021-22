#include "dp.h"
#include "dig_in.h"

struct dp_s{
    //// Pre Calculation ////

    // Sensor Values (Synchronous)
    double tps;
    double ect;
    double iat;
    double map;
    
    // Sensor Values (Asynchronous)
    unsigned long revolutions;
    unsigned long lastRPMCalcTime;
    unsigned long totalRevolutions;
    unsigned long startingRevolutions;
    unsigned long previousRev;

    // Derived Sensor Values
    double mapavg;
    double dtps;



    // Flags

    // Misc

    //// Post-Calculation ////
    struct dp_calc_s;
        //unsigned long injectorPulseTime;
        //unsigned long totalPulseTime;
        //unsigned long lastPulse;
};

void dp_init(){
    
}

void dp_reset();

void dp_tosend(const struct dp_s* ptrdp, uint32_t* numdp);

void dp_adv();

void dp_update(){
    
}

const struct dp_s* dp_curr();

void dp_store_pvnrt();

void dp_store_misc();

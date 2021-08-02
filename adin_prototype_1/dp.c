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

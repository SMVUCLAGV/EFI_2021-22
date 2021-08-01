#ifndef DP_H
#define DP_H

#include <stdint.h>

struct dp_s;

void dp_init();

void dp_reset();
//resets iterator to first dp, for use after terminal has copied over all data to be sent

void dp_tosend(const struct dp_s* ptrdp, uint32_t* numdp);
//a pointer to the first dp and the number of dps accumulated

void dp_adv();
//turns the current data product into a 'blank slate' (for variables where this is relevant). Advances iterator for dp location

void dp_update();
//read sensor values and do any filtering/processing (e.g. MAP_AVG)

const struct dp_s* dp_curr();
//gives a pointer to the current data product

void dp_store_pvnrt();
//need a way to store pvnrt's (or any other data) into a single data product

void dp_store_misc();
//need a place to store stuff for miscellaneous data (such as last injection time, etc.)


#endif
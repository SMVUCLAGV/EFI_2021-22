#include "dp.h"
#include "dig_in.h"

//dp initialization
void dp_init(){
    dp_counter = 0;
    cur_dp = 1;
}

// resets dp array to an unwritten state. To minimize delays, instantly switch to the other dp and write there
void dp_reset(){
    if (cur_dp == 1){
        dp_itr = dp_arr2;
        cur_dp = 2;
    }
    else if (cur_dp == 2){
        dp_itr = dp_arr1;
        cur_dp = 1;
    }
    dp_counter = 0;
}

// extracts unprocessed dps by returning the current dp array and the number of dps in that array
void dp_tosend(const struct dp_s** ptrdp, uint32_t* numdp){
    if (cur_dp == 1)
        *ptrdp = dp_arr1;
    else if (cur_dp == 2)
        *ptrdp = dp_arr2;

    numdp = &dp_counter;
}

//advance dp iterator in order to be able to write data in a new dp after filling the previous one
void dp_adv(){
    dp_itr++;
    dp_counter++;
}

void dp_update(){

}

const struct dp_s* dp_curr(){
    return dp_itr;
}

void dp_store_pvnrt();

void dp_store_misc();
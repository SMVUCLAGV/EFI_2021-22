#include "dp.h"
#include "dig_in.h"

void dp_init(){
    dp_counter = 0;
}

void dp_reset(){
    dp_itr = dp_array;
    dp_counter = 0;
}

void dp_tosend(const struct dp_s** ptrdp, uint32_t* numdp){
    ptrdp = dp_array;
    numdp = dp_counter;
}

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
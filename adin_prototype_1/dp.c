#include "dp.h"
#include "dig_in.h"

struct dp_s{
    uint32_t* m_data;
};

void dp_init(){
    //mempool allocate for struct?
}

void dp_reset();

void dp_tosend(const struct dp_s* ptrdp, uint32_t* numdp);

void dp_adv();

void dp_update(){
    
}

const struct dp_s* dp_curr();

void dp_store_pvnrt();

void dp_store_misc();

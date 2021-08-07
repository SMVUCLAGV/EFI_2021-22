#include "alg_pvnrt.h"

void alg_pvnrt_init();
void alg_pvnrt_loop(); //how does loop work?

double alg_pvnrt_doubleMap(double val, double minIn, double maxIn, double minOut, double maxOut){
    return ((val - minIn) / (maxIn - minIn)) * (maxOut - minOut) + minOut;
}

double alg_pvnrt_pulseTime(){
    
}

uint32_t alg_pvnrt_tbl();
uint32_t alg_pvnrt_savetbl();
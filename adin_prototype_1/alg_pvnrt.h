#ifndef ALG_PVNRT_H
#define ALG_PVNRT_H

#include <stdint.h>

void alg_pvnrt_init();
void alg_pvnrt_loop();

double alg_pvnrt_doubleMap(double val, double minIn, double maxIn, double minOut, double maxOut);
double alg_pvnrt_pulseTime();

uint32_t alg_pvnrt_tbl();
uint32_t alg_pvnrt_savetbl();


#endif
#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>
void filter_init();
int filter_addData(double input);

int filter_noWeight();

double filter_getData();
double filter_getGauss();

#endif
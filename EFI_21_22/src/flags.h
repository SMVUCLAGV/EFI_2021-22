#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
extern struct flags f;

struct flags {
    uint64_t HID    : 1;
    uint64_t CALC   : 1;
    uint64_t CURRINJ   : 1;
    uint64_t CALCDONE   : 1;
    // dig_in.h
    uint64_t DIG_IN_VALID   : 1;
    // anlg_in.h
    uint64_t ANLG_IN_READY   : 1;
    // ser.c
    uint64_t SER_SENDING   : 1;
    // alg_pvnrt.c
    uint64_t ENG_ON   : 1;
    uint64_t DP_COMPLETE   : 1;
};

void flags_init();

#endif // FLAGS_H

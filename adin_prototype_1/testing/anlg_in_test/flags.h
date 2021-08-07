#ifndef FLAGS_H
#define FLAG_H

#include <stdint.h>

struct flags {
    uint64_t HID    : 1;
    uint64_t CALC   : 1;
    uint64_t CURRINJ   : 1;
    uint64_t CALCDONE   : 1;
    // dig_in.h
    uint64_t DIG_IN_VALID   : 1;
    // anlg_in.h
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
    uint64_t CALC   : 1;
} f;


// dig_in.h
#define FLAG_DIG_IN_VALID 3

// angl_in.h
#define FLAG_ANLG_IN_READY 4

// ser.c
#define FLAG_SER_SENDING 6

// alg_pvnrt.c
#define FLAG_ENG_ON 7

#define FLAG_DP_COMPLETE

#endif // FLAG_H

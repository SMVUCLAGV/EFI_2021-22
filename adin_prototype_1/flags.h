#ifndef FLAGS_H
#define FLAG_H

#include <stdint.h>

#define FLAG_HID 0
#define FLAG_CALC 1
#define FLAG_CURRINJ 2 // just an example of a flag we can add. might not be necessary
#define FLAG_CALC_DONE 5

// dig_in.h
#define FLAG_DIG_IN_VALID 3

// angl_in.h
#define FLAG_ANLG_IN_VALID 4

// ser.c
#define FLAG_SER_SENDING 6

volatile uint32_t flag_v = 0; // flag vector

#define FLAG_DRF(FLAG) ((flag_v >> FLAG) & 1)
#define FLAG_SET(FLAG) (flag_v |= (1 << FLAG))
#define FLAG_CLR(FLAG) (flag_v = ~(~flag_v | (1 << FLAG)))

#endif // FLAG_H
#include "flags.h"

struct flags f;

void flags_init(){
    f.ANLG_IN_READY = 0;
    f.CALC = 0;
    f.CALCDONE = 0;
    f.CURRINJ = 0;
    f.DIG_IN_VALID = 0;
    f.DP_COMPLETE = 0;
    f.ENG_ON = 0;
    f.HID = 0;
    f.SER_SENDING = 0;
}
#include "anlg_in.h"

double value;
uint32_t timestamp;

void setup () {
    anlg_in_init();
    Serial.begin(115200);
}

void loop () {
    anlg_in_meas();
    delay(1000)
    anlg_in_read(0, &value, &timestamp);
    Serial.println(value);
    Serial.println(timestamp);
}

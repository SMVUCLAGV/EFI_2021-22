#include "src/dig_in.h"

uint32_t value;
uint32_t timestamp;

void setup () {
    dig_in_init();
    Serial.begin(115200);
    while (!Serial);
    Serial.println("begin tests");
}

void loop () {
    dig_in_meas();
    delay(50);
    dig_in_read(0, &value, &timestamp);
    Serial.print("INO: Value is: ");
    Serial.print(value);
    Serial.print(" at timestamp: ");
    Serial.println(timestamp);

    //can we test dig_in_attachint?
}

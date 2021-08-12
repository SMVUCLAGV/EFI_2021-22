#include "src/anlg_in.h"

double value;
uint32_t timestamp;

void setup () {
    anlg_in_init();
    Serial.begin(115200);
    while (!Serial);
    Serial.println("begin tests");
   
}

void loop () {
    anlg_in_meas();
    delay(50);
    anlg_in_read(0, &value, &timestamp);
    Serial.print("INO: Value is: ");
    Serial.print(value);
    Serial.print(" at timestamp: ");
    Serial.println(timestamp);
}

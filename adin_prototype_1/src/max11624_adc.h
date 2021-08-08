#include <stdint.h>
// MAX11624 Register Values:
const uint8_t MAX11624_CONV_REG  = (0b1<<7)|(0b1111<<3)|(0b00<<0);  
                                // (CONV_REG)|(CHAN N = 16)|(SCAN THROUGH CHAN N)
const uint8_t MAX11624_SETUP_REG = (0b01<<6)|(0b00<<4)|(0b01<<2)|(0b00<<0);  
                                // (SETUP_REG)|(CLOCK MODE 00)|(EXT REF)|(D.C)
const uint8_t MAX11624_AVG_REG   = (0b001<<5)|(0b1<<4)|(0b00<<2)|(0b00<<0);  
                                // (AVG_REG)|(ENABLE AVG)|(AVG 4X)|(D.C)
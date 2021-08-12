#include <stdint.h>

#include "dig_in.h"
#include "flags.h"
#include "sensors.h"
#include "pins.h"
#include "timer.h" 

#include <Arduino.h>


static uint32_t dig_pin_st_v; // bit vector of pin states. Access using sensors.h macros
static uint64_t convTime;

void dig_in_init(){
    //Inintial setup, define all digital input pins
    pinMode(M_PIN_DIG_IN_DM_SW, INPUT);
    pinMode(M_PIN_DIG_IN_HALL1, INPUT);
    pinMode(M_PIN_DIG_IN_HALL2, INPUT);
    pinMode(M_PIN_DIG_IN_MOM_SW, INPUT);
    pinMode(M_PIN_DIG_IN_TGL_SW, INPUT);

    //Perform measurement once upon startup
    dig_in_meas();
    f.DIG_IN_VALID = 1;
}

void dig_in_meas(){
    //poll each sensor for new values
    dig_pin_st_v = 0;
    dig_pin_st_v |= (digitalRead(M_PIN_DIG_IN_DM_SW)  << M_DIG_IN_DM_SW);
    dig_pin_st_v |= (digitalRead(M_PIN_DIG_IN_HALL1)  << M_DIG_IN_HALL1);
    dig_pin_st_v |= (digitalRead(M_PIN_DIG_IN_HALL2)  << M_DIG_IN_HALL2);
    dig_pin_st_v |= (digitalRead(M_PIN_DIG_IN_MOM_SW) << M_DIG_IN_MOM_SW);
    dig_pin_st_v |= (digitalRead(M_PIN_DIG_IN_TGL_SW) << M_DIG_IN_TGL_SW);
    //log time stamp
    convTime = timer_systime();
}

void dig_in_read(uint32_t m_dig_in_sensor, uint32_t* value, uint32_t* timestamp){
    //need to do timestamp too
    *value = DIG_IN_DEREF(dig_pin_st_v, m_dig_in_sensor);
    *timestamp = convTime;
}

// m_int_type has to be turned into an arduino RISING, FALLING, BOTH keyword
// m_dig_in_sensor needs to be converted to m_pin_...
void dig_in_attachint(uint32_t m_dig_in_sensor, void (*func)(), uint32_t m_int_type){
    uint32_t m_ard_int_type = 0;
    switch(m_int_type) {
        case M_INT_RISING:
            m_ard_int_type = RISING;
            break;
        case M_INT_FALLING:
            m_ard_int_type = FALLING;
            break;
        case M_INT_BOTH:
            m_ard_int_type = CHANGE;
            break;
    }
    attachInterrupt(m_dig_in_sensor,func,m_ard_int_type);
}
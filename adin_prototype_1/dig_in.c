#include <stdint.h>

#include "dig_in.h"
#include "sensors.h"
#include "pins.h"
//#include "timer.h" for timestamp?

static uint32_t dig_in_v; 
  // vector of pin states. Access using sensors.h macros

void dig_in_init(){
    pinMode(M_PIN_DIG_IN_DM_SW, INPUT);
    pinMode(M_PIN_DIG_IN_HALL1, INPUT);
    pinMode(M_PIN_DIG_IN_HALL2, INPUT);
    pinMode(M_PIN_DIG_IN_MOM_SW, INPUT);
    pinMode(M_PIN_DIG_IN_TGL_SW, INPUT);

    dig_in_meas();
}

void dig_in_meas(){
    //poll each sensor for new values
    dig_in_v = 0;
    dig_in_v |= (digitalRead(M_PIN_DIG_IN_DM_SW)  << M_DIG_IN_DM_SW);
    dig_in_v |= (digitalRead(M_PIN_DIG_IN_HALL1)  << M_DIG_IN_HALL1);
    dig_in_v |= (digitalRead(M_PIN_DIG_IN_HALL2)  << M_DIG_IN_HALL_2);
    dig_in_v |= (digitalRead(M_PIN_DIG_IN_MOM_SW) << M_DIG_IN_MOM_SW);
    dig_in_v |= (digitalRead(M_PIN_DIG_IN_TGL_SW) << M_DIG_IN_TGL_SW);
    //TODO: log time stamp too
}

void dig_in_read(uint32_t m_dig_in_sensor, uint32_t* value, uint32_t* timestamp){
    //need to do timestamp too
    *value = DIG_IN_DEREF(dig_in_v, m_dig_in_sensor);
}

void dig_in_readall(uint32_t* value, uint32_t* timestamp){
    //need to do timestamp too
    *value = dig_in_v;
}

void dig_in_attachint(uint32_t m_dig_in_sensor, void (*f)(), uint32_t m_int_type){
    attachInterrupt(m_dig_in_sensor,f,m_int_type);
}

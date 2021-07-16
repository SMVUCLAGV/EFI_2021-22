#include "dig_in.h"
#include "sensors.h"
#include "pins.h"
//#include "timer.h" for timestamp?

static uint32_t state_dm_sw;
static uint32_t state_hall1;
static uint32_t state_hall2;
static uint32_t state_mom_sw;
static uint32_t state_tgl_sw;

void dig_in_init(){
    pinMode(MP_DIG_IN_DM_SW, INPUT);
    pinMode(MP_DIG_IN_HALL1, INPUT);
    pinMode(MP_DIG_IN_HALL2, INPUT);
    pinMode(MP_DIG_IN_MOM_SW, INPUT);
    pinMode(MP_DIG_IN_TGL_SW, INPUT);
}

void dig_in_meas(){
    //poll each sensor for new values
    state_dm_sw = digitalRead(MP_DIG_IN_DM_SW);
    state_hall1 = digitalRead(MP_DIG_IN_HALL1);
    state_hall2 = digitalRead(MP_DIG_IN_HALL2);
    state_mom_sw = digitalRead(MP_DIG_IN_MOM_SW);
    state_tgl_sw = digitalRead(MP_DIG_IN_TGL_SW);
    //TODO: log time stamp too
}

void dig_in_read(uint32_t m_dig_in_sensor, uint32_t* value, uint32_t* timestamp){
    //need to do timestamp too
    switch(m_dig_in_sensor){
        case 0:
            *value = digitalRead(MP_DIG_IN_HALL1);
            break;
        case 1:
            *value = digitalRead(MP_DIG_IN_HALL2);
            break;
        case 2:
            *value = digitalRead(MP_DIG_IN_TGL_SW);
            break;
        case 3:
            *value = digitalRead(MP_DIG_IN_MOM_SW);
            break;
        case 4:
            *value = digitalRead(MP_DIG_IN_DM_SW);
            break;
    }
}

void dig_in_readall(uint32_t* value, uint32_t* timestamp){
    //need to do timestamp too
    uint32_t bitvec;
    bitvec = digitalRead(MP_DIG_IN_HALL1);
    bitvec += 2 * digitalRead(MP_DIG_IN_HALL2);
    bitvec += 4 * digitalRead(MP_DIG_IN_TGL_SW);
    bitvec += 8 * digitalRead(MP_DIG_IN_MOM_SW);
    bitvec += 16 * digitalRead(MP_DIG_IN_DM_SW);
    *value = bitvec;
}

void dig_in_attachint(uint32_t m_dig_in_sensor, void (*f)(), uint32_t m_int_type){
    attachInterrupt(m_dig_in_sensor,f,m_int_type);
}

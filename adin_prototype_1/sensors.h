#ifndef SENSORS_H
#define SENSORS_H

#define M_DIG_IN_HALL1 0
#define M_DIG_IN_HALL2 1
#define M_DIG_IN_TGL_SW 2
#define M_DIG_IN_MOM_SW 3
#define M_DIG_IN_DM_SW 4

#define DIG_IN_DEREF(U_32_BIT_VEC, M_DIG_IN_SENSOR) ((U_32_BIT_VEC >> M_DIG_IN_SENSOR) | 1)

#define M_DIG_OUT_INJ 0
#define M_DIG_OUT_LED 1
#define M_DIG_OUT_BUZZER 2
#define M_DIG_OUT_ELEC_THROT 3

#define M_ANLG_IN_ECT 0
#define M_ANLG_IN_IAT 1
#define M_ANLG_IN_MAP 2
#define M_ANLG_IN_O2 3
#define M_ANLG_IN_TPS 4

#endif

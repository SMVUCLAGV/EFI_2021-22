#include <stdint.h>

void dig_in_init();
void dig_in_meas();
void dig_in_read(uint32_t m_dig_in_sensor, uint32_t* value, uint32_t* timestamp);
void dig_in_readall(uint32_t* value, uint32_t* timestamp);
void dig_in_attachint(uint32_t m_dig_in_sensor, void (*f)(), uint32_t m_int_type);
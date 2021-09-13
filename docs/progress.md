# Code Progress
- key :
  - ✓ - code completed
  - ✓✓ - testing completed
___
## alg_pvnrt
`void alg_pvnrt_init();`  
`void alg_pvnrt_loop();`  
`double alg_pvnrt_doubleMap(double val, double minIn, double maxIn, double minOut, double maxOut);`  
`double alg_pvnrt_pulseTime();`  
`uint32_t alg_pvnrt_tbl();`  
`uint32_t alg_pvnrt_savetbl();`  


## ✓✓ anlg_in
✓✓ `void anlg_in_init();`  
✓✓ `void anlg_in_meas(); `  
✓✓ `void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp);`  
✓✓ `void anlg_in_dummy();`  
✓✓ `void anlg_in_eoc();`
  
## ✓ dig_in
✓ `void dig_in_init();`  
✓ `void dig_in_meas();`  
✓ `void dig_in_read(uint32_t m_dig_in_sensor, uint32_t* value, uint32_t* timestamp);`  
✓ `void dig_in_attachint(uint32_t m_dig_in_sensor, void (*f)(), uint32_t m_int_type);`  

## ✓ dig_out
✓ `void dig_out_init();`  
✓ `void dig_out_write(uint32_t m_dig_out_sensor, uint32_t m_dig_out_state);`  
✓ `void dig_out_read(uint32_t m_dig_out_sensor, uint32_t* value, uint32_t* timestamp);`  
✓ `void dig_out_writepwm(uint32_t m_dig_out_sensor, double dutyCycle);`  

## dp
✓ `void dp_init();`  
✓ `void dp_reset();`  
✓ `void dp_tosend(const struct dp_s** ptrdp, uint32_t* numdp);`  
✓ `void dp_adv();`  
`void dp_update();`  
✓ `const struct dp_s* dp_curr();`  
`void dp_store_pvnrt(const struct dp_calc_s*); `  
`void dp_store_misc();`  
  
## interrupt
`void interrupt_off();`  
`void interrupt_on();`  

## ser
`void ser_init();`  
`uint32_t ser_write(uint8_t* towrite, uint32_t numbytes);`  
`uint32_t ser_send();`  
`void ser_sendreset();`  
`void ser_read(uint8_t** toread, uint32_t* numbytes);`  
`void ser_readreset();`  
`void ser_readreset(uint32_t numbytes);`  

## ✓✓ spi
**!- implemented currently using Arduino functions**

✓✓ `void comm_spi_init();`  
✓✓ `void comm_spi_begin();`  
✓✓ `void comm_spi_write(uint8_t sendbyte);`  
✓✓ `uint8_t comm_spi_read();`  
✓✓ `void comm_spi_end();`  

## ✓ filter
✓ `void filter_init();`  
✓ `int filter_addData(double input);`   
✓ `int filter_noWeight();`   
✓ `double filter_getData();`   
✓ `double filter_getGauss();`  

## timer
`void timers_init();`  
✓ `uint64_t timer_systime();`  
`void timer_inj_attachint(void (*f)());`  
`void timer_inj_setperiod(uint32_t period);`  
`void timer_inj_start();`  
`void timer_calc_attachint(void (*f)());`  
`void timer_calc_setperiod(uint32_t period);`  
`void timer_calc_start();`  
`void timer_hid_attachint(void (*f)());`  
`void timer_hid_setperiod(uint32_t period);`  
`void timer_hid_start();`  

### flags.h
### max11624_adc.h
### pins.h
### sensors.h

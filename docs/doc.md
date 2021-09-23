# ECU Documentation - GV Electrical

___
## alg_pvnrt
- Responsible for calculating when fuel should be injected into the engine based on sensor readings to achieve maximum fuel efficiency.
___
## anlg_in
- Responsible for extracting analog data from external sensors through an ADC (Analog to Digital Converter).
- `void anlg_in_init();`  
    - Initialzes the analog reading functionality
    - Sets up SPI communication: (see datasheet)
    - pull pins (nEOC, nCNVST, nCS) high/low accordingly 
    - write to conversion, setup, avg registers
- `void anlg_in_meas(); `  
    - Tell the ADC to start taking values

- `void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp);`  
    - bruh
- `void anlg_in_dummy();`  
- `void anlg_in_eoc();`

___
## dig_in
- Responsible for extracting digital (HIGH/LOW) data from external sensors.
___
## dig_out
- Responsible for producing digital outputs from the ECU
___
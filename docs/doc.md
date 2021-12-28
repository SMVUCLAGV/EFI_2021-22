# ECU Documentation - GV Electrical

___
## alg_pvnrt
- Responsible for calculating when fuel should be injected into the engine based on sensor readings to achieve maximum fuel efficiency.
___
## anlg_in
- Responsible for extracting analog data from external sensors through an ADC (Analog to Digital Converter).
### flags
- fetchVals
    - whether the values are available to be fetched from the sensors
- validVals
    - whether the values read from the sensor is valid (refreshed)
### functions
- `void anlg_in_init();`  
    - Initialzes the analog reading functionality
    - Sets up SPI communication: (see datasheet)
    - Pulls pins (nEOC, nCNVST, nCS) high/low accordingly 
    - Writes to conversion, setup, avg registers
- `void anlg_in_meas(); `  
    - Tells the ADC to start taking values

- `void anlg_in_read(uint32_t m_anlg_in_sensor, double* value, uint32_t* timestamp);`  
    - Reads value for the specified sensor, return its value and timestamp for when the transaction took place
    - if fetchVals and validVals are both true, signalling that new data is valid and available, proceed to read values from all 16 channels
    
- `void anlg_in_dummy();`
    - Dummy function that does nothing
    - Included because attaching an interrupt triggers it automatically, result in undefined behavior. A dummy function is used to prevent the interrupt from triggering the actual function
- `void anlg_in_eoc();`
    - End of conversion, reset flags validVals and fetchVals to original state so another sensor reading can be processed

___
## dig_in
- Responsible for extracting digital (HIGH/LOW) data from external sensors.
___
## dig_out
- Responsible for producing digital outputs from the ECU
___
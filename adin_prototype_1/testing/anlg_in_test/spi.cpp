#include "spi.h"
#include <SPI.h>

static SPISettings SPI_PARAMS(10000000, MSBFIRST, SPI_MODE0); // 1 MHz, MODE0

void comm_spi_init(){
    SPI.begin();
}

void comm_spi_begin(){
    SPI.beginTransaction(SPI_PARAMS);
}


void comm_spi_write(uint8_t sendbyte){
    SPI.transfer(sendbyte);
}

uint8_t comm_spi_read(){
    return SPI.transfer(0);
}

void comm_spi_end(){
    SPI.endTransaction();
}

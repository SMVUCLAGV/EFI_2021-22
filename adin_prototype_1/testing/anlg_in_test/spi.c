#include "spi.h"

struct comm_spi_s;

void comm_spi_init(struct comm_spi_s* s){
    SPI.begin();
}
	// analogous to arduino SPI.begin()

void comm_spi_begin(struct comm_spi_s* s){
    SPI.beginTransaction();
}
	// analogous to arduino SPI.beginTransaction()

void comm_spi_write(struct comm_spi_s* s, uint8_t sendbyte){
    SPI.transfer(sendbyte, sizeof(sendbyte));
}

uint8_t comm_spi_read(struct comm_spi_s* s){
    return SPI.transfer();
}

void comm_spi_end(struct comm_spi_s* s){
    SPI.endTransaction();
}
	// analogous to 

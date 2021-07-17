#include "spi.h"

struct comm_spi_s;

void comm_spi_init(struct comm_spi_s*){
    SPI.begin();
}
	// analogous to arduino SPI.begin()

void comm_spi_begin(struct comm_spi_s*){
    SPI.beginTransaction();
}
	// analogous to arduino SPI.beginTransaction()

void comm_spi_write(struct comm_spi_s*, char sendbyte){
    SPI.transfer(sendbyte, sizeof(sendbyte));
}

char comm_spi_read(struct comm_spi_s*){
    return SPI.transfer();
}

void comm_spi_end(struct comm_spi_s*){
    SPI.endTransaction();
}
	// analogous to 

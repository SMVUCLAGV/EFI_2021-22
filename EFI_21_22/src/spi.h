#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void comm_spi_init();
	// analogous to arduino SPI.begin()

void comm_spi_begin();
	// analogous to arduino SPI.beginTransaction()

void comm_spi_write(uint8_t sendbyte);

uint8_t comm_spi_read();

void comm_spi_end();
	// analogous to 	

#endif // SPI_H

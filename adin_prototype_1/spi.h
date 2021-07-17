#ifndef SPI_H
#define SPI_H

struct comm_spi_s;

void comm_spi_init(struct comm_spi_s*);
	// analogous to arduino SPI.begin()

void comm_spi_begin(struct comm_spi_s*);
	// analogous to arduino SPI.beginTransaction()

void comm_spi_write(struct comm_spi_s*, char sendbyte);

char comm_spi_read(struct comm_spi_s*);

void comm_spi_end(struct comm_spi_s*);
	// analogous to 

#endif // SPI_H
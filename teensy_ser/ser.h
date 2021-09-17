#ifndef SER_H 
#define SER_H

#include <stdint.h>

// Module will send/rec over serial port in a non blocking way. Usage will write
//  a series of bytes to a buffer and then will send these in a non-blocking way.
//  Bytes will also be recieved in a non-blocking way. The bytes will be written to
//  a buffer and accessed via a pointer.

#define BAUDRATE 115200
#define SER_BUFFER_BYTE_SIZE 64

void ser_init();

    // Writes to buffer that is to be sent
    //  returns 0 on buffer overflow. returns 1 else
uint32_t ser_write(uint8_t* towrite, uint32_t numbytes);

    // toread will be a pointer to buffer and numbytes will return how
    //  many bytes have been recieved since the last reset.
    //   returns 0 if buffer overflowed, else returns 1
uint32_t ser_read(const uint8_t** toread, uint32_t* numbytes);

struct ser_flags {
  // General Status (i.e. high level, relevant to client)
  uint32_t writeinprogress : 1; // write in progress      set: ser_write() clr: uart int
  uint32_t writeskipped  : 1; // write skipped          set: ser_write() clr: next ser_write()
  uint32_t overflowedreadbuffer : 1; // overflowed read buffer set: uart int    clr: never

  // UART module status (i.e. low level, relevant for debugging)
  uint32_t txidle : 1; // transmitter idle          Updated: uart int
  //uint32_t OR : 1; // recieve buffer overrun    set: uart int clr: ser_write()
  //uint32_t NF : 1; // noise found on line       set: uart int clr: ser_write()
  //uint32_t PE : 1; // parity error              set: uart int clr: ser_write()
};

// Retrieve current ser flags. 
void ser_status(volatile const struct ser_flags** f);

uint32_t ser_test();

#endif // SER_H

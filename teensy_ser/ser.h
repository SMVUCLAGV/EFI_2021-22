#ifndef SER_H 
#define SER_H

#include <stdint.h>

// Module will send/rec over serial port in a non blocking way. Usage will write
//  a series of bytes to a buffer and then will send these in a non-blocking way.
//  Bytes will also be recieved in a non-blocking way. The bytes will be written to
//  a buffer and accessed via a pointer.

#define SER_BUFFER_BYTE_SIZE 500

void ser_init();

uint32_t ser_write(uint8_t* towrite, uint32_t numbytes);
    // Writes to buffer that is to be sent
    //  returns 0 on buffer overflow. returns 1 else
uint32_t ser_send();
    // returns 0 on send failed, try again
    // returns 1 on successful send
void ser_sendreset();
    // resets send buffer

void ser_read(uint8_t** toread, uint32_t* numbytes);
    // toread will be a pointer to buffer and numbytes will return how
    //  many bytes have been recieved since the last reset.

void ser_readreset();
    // completely flush rcvbuffer
void ser_readreset(uint32_t numbytes);
    // flush rcvbuffer by numbytes


#endif // SER_H

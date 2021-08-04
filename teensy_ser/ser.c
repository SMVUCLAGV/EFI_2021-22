#include "ser.h"
#include <stdint.h>

// Module will send/rec over serial port in a non blocking way. Usage will write
//  a series of bytes to a buffer and then will send these in a non-blocking way.
//  Bytes will also be recieved in a non-blocking way. The bytes will be written to
//  a buffer and accessed via a pointer.

static uint8_t sendbuffer[SER_BUFFER_BYTE_SIZE];
static uint8_t rcvbuffer[SER_BUFFER_BYTE_SIZE];

static uint32_t sendbuffer_numbytes, rcvbuffer_numbytes;

void ser_init() {
  // Setup interupts for getting data
  
  // Setup interrupt for done sending data

  // Start uart
}

    // Writes to buffer that is to be sent
    //  returns 0 on buffer overflow. returns 1 else
uint32_t ser_write(uint8_t* towrite, uint32_t numbytes) {
    
    // Check flags to see if data is being sent
    //  if so fail

}

    // returns 0 on send failed, try again
    // returns 1 on successful send
uint32_t ser_send() {

    // set flag for sending data to be high
}

    // resets send buffer
void ser_sendreset() {
}

    // toread will be a pointer to buffer and numbytes will return how
    //  many bytes have been recieved since the last reset.
void ser_read(uint8_t** toread, uint32_t* numbytes) {
}

    // flush rcvbuffer by numbytes
void ser_readreset(uint32_t numbytes) {
}


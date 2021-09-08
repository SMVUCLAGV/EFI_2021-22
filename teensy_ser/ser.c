#include "ser.h"
#include "teensy_uart.h"
#include <stdint.h>

// Module will send/rec over serial port in a non blocking way. Usage will write
//  a series of bytes to a buffer and then will send these in a non-blocking way.
//  Bytes will also be recieved in a non-blocking way. The bytes will be written to
//  a buffer and accessed via a pointer.

#define BAUDRATE 115200

//************ Private Declarations ************ 
static volatile struct ser_flags ser_f;

// tx variabls
static volatile uint

// read buffer related
static volatile uint8_t readbuffer[2][SER_BUFFER_BYTE_SIZE];
static volatile uint32_t readbuffer_len;
static volatile uint32_t readbuffer_curr; // the buffer currently written to

// Functions
static void ser_handleuart();
static uint8_t* ser_txfifoload(uint8_t* str, uint32_t num); // returns pointer 
                                                            // to after num chars
static uint32_t ser_txfifolevel();
static uint32_t ser_rxfifolevel();

//************ Public Definitions ************ 
void ser_init() {
  // init local variables
  ser_f.WIP = 0;
  ser_f.WS = 0;
  ser_f.ORB = 0;
  ser_f.TC = 1;

  readbuffer_len = 0;
  readbuffer_curr = 0;

  // **** UART SETUP ****

  // Set up FIFOs and waterlevel
  _RB_CLR(REG_C2, TE);  // enable transmitter
  _RB_CLR(REG_C2, RE);  // enable receiver
  _RB_SET(REG_PFIFO, TXFIFO);
  _RB_SET(REG_PFIFO, RXFIFO);

  _RW_SET(REG_TWFIFO, 0, 7, 0);
  _RW_SET(REG_RWFIFO, 0, 7, RX_FIFO_SIZE);

  // Set baudrate
  _RW_SET(REG_BDH, SBR_MSB, BAUDRATE >> 8);    
          /// NOTE DID A LITTLE RABBLETYROOK HERE! SBR_MSB -> 7, 0
  _RW_SET(REG_BDL, SBR_LSB, BAUDRATE | 0x00FF);
          /// NOTE DID A LITTLE RABBLETYROOK HERE! SBR_LSB -> 7, 0
  // Setup C2 
  _RB_SET(REG_C2, TIE); // enable interrupt for transmitter at water level
  _RB_SET(REG_C2, RIE); // enable interrupt for reciever at water level
  _RB_SET(REG_C2, TE);  // enable transmitter
  _RB_SET(REG_C2, RE);  // enable receiver

  // Attach interrupts
  // use uart0_status_isr() 
  // use uart0_error_isr()
  //  -> both from teensy files
  
  // Start uart
}

// Write given string to uart tx in non-blocking fashion. Input string
// musn't change while this happens. If a string is already being sent,
// that transmission will stop in favor of new one.
uint32_t ser_write(const uint8_t* towrite, uint32_t numbytes) {
  ser_f.WS = 0;

  // Check if string is currently being written. If so, cancel old write.
  if (ser_f.WIP) {
    // Clear TXFIFO
    _RB_CLR(REG_C2, TE);  // turn off transmitter
    _RB_SET(REG_CFIFO, TXFLUSH); // flush tx fifo
    _RB_CLR(REG_CFIFO, TXFLUSH); 
    _RB_SET(REG_C2, TE);  // enable transmitter

    // Set Write Skipped Flag
    ser_f.WS = 1;
  }

  // Kick off writting
  ser_f.WIP = 1;
}


// toread will be a pointer to buffer and numbytes will return how
//  many bytes have been recieved since the last reset.
void ser_read(uint8_t** toread, uint32_t* numbytes) {
  // have to 2 read buffers. When one readbuffer is given out here,
  // the other is automatically "given up" and can be written to by
  // uart.
}

void ser_status((const struct ser_flags*)* fptrptr) {
  *fptrptr = &ser_f;
}

// Private Definitions
void uart0_status_irs(void) {
  ser_handleuart();
}

static uint8_t* ser_txfifoload(uint8_t* str, uint32_t num) {
  for (int i = 0; i < num; i++)
    _RW_SET(REG_D, 7, 0, str[i]);

  return str[num];
}

static void ser_handleuart() {
  // Check status reg
  //
  // Set flags appropriately
  //
  // TX Operations
  //  If still transmitting, send more bytes
  //
  // RX Operations
  //  If read buffer isn't empty, empty it to new location
}

static uint32_t ser_txfifolevel() {
  return _RW_GET(REG_TWFIFO, 7, 0);
}

static uint32_t ser_rxfifolevel() {
  return _RW_GET(REG_RWFIFO, 7, 0);
}


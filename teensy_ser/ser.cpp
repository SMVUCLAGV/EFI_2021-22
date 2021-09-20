#include "ser.h"
#include "reg.h"
#include "teensy_uart.h"
#include "kinetis.h"
#include "Arduino.h"
#include <stdint.h>
#include <stdlib.h>

// Module will send/rec over serial port in a non blocking way. Usage will write
//  a series of bytes to a buffer and then will send these in a non-blocking way.
//  Bytes will also be recieved in a non-blocking way. The bytes will be written to
//  a buffer and accessed via a pointer.


//************ Private Declarations ************ 
static volatile struct ser_flags ser_f;

// tx variabls
static volatile const uint8_t* txbuffer;
static volatile uint32_t txbuffer_len;

// read buffer related
static volatile uint8_t rxbuffer[2][SER_BUFFER_BYTE_SIZE];
static volatile uint32_t rxbuffer_len;
static volatile uint32_t rxbuffer_curr; // the buffer currently written to

// Functions
static void ser_handleuart();
static volatile const uint8_t* ser_txfifoload(volatile const uint8_t* str, uint32_t num); // returns pointer 
                                                            // to after num chars
static uint32_t ser_txfifolevel();
static uint32_t ser_rxfifolevel();

//************ Public Definitions ************ 
uint32_t ser_init() {
  // init local variables
  ser_f.writeinprogress = 0;
  ser_f.writeskipped = 0;
  ser_f.overflowedreadbuffer = 0;

  rxbuffer_len = 0;
  rxbuffer_curr = 0;

  // **** UART SETUP ****

  // Start UART4 clock
  _RB_SET(REG_SIM_SCGC1, SIM_SCGC_UART4);

  // Set MUX correctly
  _RB_SET(REG_PORTE_PCR24, DSE); // high drive strength on uart4tx
  _RB_SET(REG_PORTE_PCR24, SRE);
  _RW_SET(REG_PORTE_PCR24, MUX_MSB, MUX_LSB, MUX_UART4);
  _RB_SET(REG_PORTE_PCR25, PE); // pull up on uart4rx
  _RB_SET(REG_PORTE_PCR25, PFE);
  _RB_SET(REG_PORTE_PCR25, PS);
  _RW_SET(REG_PORTE_PCR25, MUX_MSB, MUX_LSB, MUX_UART4);

  // Set baudrate
  uint32_t divisor = UART4_CLOCKRATE / (BAUDRATE  * 16);
  _RW_SET(REG_BDH, SBR_MSB_MSB, SBR_MSB_LSB, (uint8_t) ((divisor >> 8) & 0x1F));    //jfc this is bad
  _RW_SET(REG_BDL, SBR_LSB_MSB, SBR_LSB_LSB, (uint8_t) ((divisor) & 0xFF));

  // Set up FIFOs and waterlevel
  _RW_SET(REG_TWFIFO, 7, 0, 0);
  _RW_SET(REG_RWFIFO, 7, 0, RXFIFO_SIZE);
  _RB_SET(REG_PFIFO, TXFE);
  _RB_SET(REG_PFIFO, RXFE);

  _RB_SET(REG_CFIFO, TXFLUSH); // flush tx fifo
  _RB_CLR(REG_CFIFO, TXFLUSH); 

  // Setup C2 
  _RB_SET(REG_C2, TIE); // enable interrupt for transmitter at water level
  _RB_SET(REG_C2, RIE); // enable interrupt for reciever at water level

  _RB_SET(REG_C2, TE);  // enable transmitter
  _RB_SET(REG_C2, RE);  // enable receiver

  // Attach interrupts
  // use uart4_status_isr() 
  // use uart4_error_isr()
  //  -> both from teensy files
  
  // Start uart


  // Problems:
  //  - digital pins have the right settings
  //  - 
  return _RW_GET(REG_BDL, 7, 0);
}

// Write given string to uart tx in non-blocking fashion. Input string
// musn't change while this happens. If a string is already being sent,
// that transmission will stop in favor of new one.
// return 0 if a write was skipped, else return 1
uint32_t ser_write(const uint8_t* towrite, uint32_t numbytes) {
  // numbytes = 0 case?
  txbuffer = towrite;
  txbuffer_len = numbytes;

  ser_f.writeskipped = 0;

  // Check if string is currently being written. If so, cancel old write.
  if (ser_f.writeinprogress) {
    // Clear TXFIFO
    _RB_CLR(REG_C2, TE);  // disable transmitter
    _RB_SET(REG_CFIFO, TXFLUSH); // flush tx fifo
    _RB_CLR(REG_CFIFO, TXFLUSH); 
    _RB_SET(REG_C2, TE);  // enable transmitter

    // Set Write Skipped Flag
    ser_f.writeskipped = 1;
  }

  // Kick off writing
  ser_f.writeinprogress = 1;
  uint32_t temp = min(txbuffer_len, TXFIFO_SIZE);
  txbuffer = ser_txfifoload(txbuffer, temp);
  txbuffer_len -= temp;

  return ser_f.writeskipped;
}


// toread will be a pointer to buffer and numbytes will return how
//  many bytes have been recieved since the last reset.
uint32_t ser_read(const uint8_t** toread, uint32_t* numbytes) {
  // have to 2 read buffers. When one readbuffer is given out here,
  // the other is automatically "given up" and can be written to by
  // uart.
  return 0;
}

void ser_status(volatile const struct ser_flags** fptrptr) {
  *fptrptr = &ser_f;
}

uint32_t ser_test() {
  return ser_txfifolevel();
}

// Private Definitions
void uart4_status_irs(void) {
  ser_handleuart();
}

static volatile const uint8_t* ser_txfifoload(volatile const uint8_t* str, uint32_t num) {
  for (uint32_t i = 0; i < num; i++)
    *REG_D = str[i];

  return &str[num];
}

static void ser_handleuart() {
  // Check status reg
  uint8_t stat_reg = _RW_GET(REG_S1, 7, 0);
  uint8_t tdre = 0x01 & (stat_reg >> TDRE); // tx data reg empty
  uint8_t rdrf = 0x01 & (stat_reg >> RDRF); // rx data reg full

  // TX Operations
  // If no more bytes, turn off transmitter
  if(tdre && (txbuffer_len == 0)) { 
    ser_f.writeinprogress = 0;
  }
  
  //  If still transmitting, send more bytes
  if(tdre && ser_f.writeinprogress) {
    uint32_t temp = min(txbuffer_len, TXFIFO_SIZE);
    txbuffer = ser_txfifoload(txbuffer, temp);
    txbuffer_len -= temp;
  }
  
  // RX Operations
  //  If read buffer isn't empty, empty it to new location
}

static uint32_t ser_txfifolevel() {
  return _RW_GET(REG_TCFIFO, 7, 0);
}

static uint32_t ser_rxfifolevel() {
  return _RW_GET(REG_RCFIFO, 7, 0);
}


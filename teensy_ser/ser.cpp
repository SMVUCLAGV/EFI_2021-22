#include "ser.h"
#include "reg.h"
#include "teensy_uart.h"
#include "kinetis.h"
#include "Arduino.h"
#include <stdint.h>

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
void ser_init() {
  // init local variables
  ser_f.writeinprogress = 0;
  ser_f.writeskipped = 0;
  ser_f.overflowedreadbuffer = 0;
  ser_f.txidle = 1;

  rxbuffer_len = 0;
  rxbuffer_curr = 0;

  // **** UART SETUP ****

  // Start UART1 clock
  _RB_SET(REG_SIM_SCGC4, SIM_SCGC_UART1);

  // Set baudrate
  _RW_SET(REG_BDH, SBR_MSB_MSB, SBR_MSB_LSB, (uint8_t) (BAUDRATE >> 8));    //jfc this is bad
  digitalWrite(31, 0);
  _RW_SET(REG_BDL, SBR_LSB_MSB, SBR_LSB_LSB, (uint8_t) (BAUDRATE | 0x000000FF));

  // Set up FIFOs and waterlevel
  // Setup C2 
  _RB_SET(REG_C2, TIE); // enable interrupt for transmitter at water level
  _RB_SET(REG_C2, RIE); // enable interrupt for reciever at water level
  //_RB_SET(REG_C2, TE);  // enable transmitter
  _RB_SET(REG_C2, RE);  // enable receiver
  //for(;;);
  //volatile uint32_t temp1 = ~(1 << TE);
  //volatile uint32_t temp2 = *REG_C2; // WHERE HANG IS
  //*REG_C2 = temp1 & temp2;
  //READ_NO_OP(REG_C2);

  _RW_SET(REG_TWFIFO, 0, 7, 0);
  _RW_SET(REG_RWFIFO, 0, 7, RXFIFO_SIZE);
  _RB_SET(REG_PFIFO, TXFE);
  _RB_SET(REG_PFIFO, RXFE);



  // Attach interrupts
  // use uart0_status_isr() 
  // use uart0_error_isr()
  //  -> both from teensy files
  
  // Start uart
}

// Write given string to uart tx in non-blocking fashion. Input string
// musn't change while this happens. If a string is already being sent,
// that transmission will stop in favor of new one.
// return 0 if a write was skipped, else return 1
uint32_t ser_write(const uint8_t* towrite, uint32_t numbytes) {
  txbuffer = towrite;
  txbuffer_len = numbytes;

  ser_f.writeskipped = 0;

  // Check if string is currently being written. If so, cancel old write.
  if (ser_f.writeinprogress) {
    // Clear TXFIFO
    _RB_CLR(REG_C2, TE);  // turn off transmitter
    _RB_SET(REG_CFIFO, TXFLUSH); // flush tx fifo
    _RB_CLR(REG_CFIFO, TXFLUSH); 

    // Set Write Skipped Flag
    ser_f.writeskipped = 1;
  }

  // Kick off writing
  ser_f.writeinprogress = 1;
  _RB_SET(REG_C2, TE); // enable transmitter
  uint32_t temp = (txbuffer_len < TXFIFO_SIZE ? txbuffer_len : TXFIFO_SIZE);
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
void uart1_status_irs(void) {
  ser_handleuart();
}

static volatile const uint8_t* ser_txfifoload(volatile const uint8_t* str, uint32_t num) {
  for (uint32_t i = 0; i < num; i++)
    _RW_SET(REG_D, 7, 0, str[i]);

  return &str[num];
}

static void ser_handleuart() {
  // Check status reg
  
 
  // Set flags appropriately
  
  // TX Operations
  //  If still transmitting, send more bytes
  
  // RX Operations
  //  If read buffer isn't empty, empty it to new location
}

static uint32_t ser_txfifolevel() {
  return _RW_GET(REG_TWFIFO, 7, 0);
}

static uint32_t ser_rxfifolevel() {
  return _RW_GET(REG_RWFIFO, 7, 0);
}


#ifndef TEENSY_UART_H
#define TEENSY_UART_H

#include <stdint.h>
#include "kinetis.h" // for getting interrupt defines
#include "reg.h"


// TEENSY UART MODULE DEFINES
#define TEENSY_UART_BASE_ADDR (0x400EA000) // UART4

#define TXFIFO_SIZE 1u // SPECIFIC TO UART4!
#define RXFIFO_SIZE 1u

#define UART4_CLOCKRATE F_BUS

// Registers
//#define REG_SIM_SCGC4   ((volatile uint32_t *) (0x40048034))
//#define SIM_SCGC_UART1 11

#define REG_SIM_SCGC1   ((volatile uint32_t *) (0x40048028))
#define SIM_SCGC_UART4 10 // NOTE: UART4 -> TX5 and RX5 in teensy schematic

#define REG_PORTE_PCR24   ((volatile uint32_t *) (0x4004D060))
#define REG_PORTE_PCR25   ((volatile uint32_t *) (0x4004D064))
#define MUX_UART4 0b011
#define MUX_MSB 10
#define MUX_LSB 8
#define DSE 6
#define ODE 5
#define PFE 4
#define SRE 2
#define PE 1
#define PS 0

#define REG_BDH         ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x00))
#define SBR_MSB_MSB 4
#define SBR_MSB_LSB 0 

#define REG_BDL         ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x01))
#define SBR_LSB_MSB 7 
#define SBR_LSB_LSB 0

#define REG_C1          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x02))
#define REG_C2          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x03))
#define TIE   7 // Transmitter Interrupt Enable
#define TCIE  6 // Transmission Complete Interrupt Enable
#define RIE   5 // Receiver Full interrupt or DMA Transfer Enable
#define ILIE  4 // Idle Line Interrupt Enable
#define TE    3 // Transmitter Enable
#define RE    2 // Receiver Enable
#define RWU   1 // Receiver Wakeup Control
#define SBK   0 // Send Break

#define REG_S1          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x04))
// NOTE: to clear flags in status registers, read from S reg then
// read or write to D reg. IF YOU READ AN EMPTY D REGISTER TO CLEAR
// A FLAG, THE FIFO WILL GET MESSED UP!!!
#define TDRE 7  // 0: data in tx buffer > waterlevel
                // 1: data in tx buffer <= waterlevel
#define TC   6  // 0: transmitter Sending
                // 1: transmiter idle
#define RDRF 5  // 0: data in rx buffer < waterlevel
                // 1: data in rx buffer >= waterlevel
#define OR   3  // 0: no overrun has occurred in rx buffer from last clear
                // 1: overrun has occurred or flag not cleared from last overrun
#define NF   2  // 0: no noise detected since last clear
                // 1: atleast one word in reciever has noise
//#define PE   0  // 0: no parity error detected since last clear
                // 1: at leat one word had parity error since last clear

#define REG_S2          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x05))
#define REG_C3          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x06))
#define REG_D           ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x07))
#define REG_MA1         ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x08))
#define REG_MA2         ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x09))
#define REG_C4          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x0a))
#define REG_C5          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x0b))
#define REG_ED          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x0c))
#define REG_MODEM       ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x0d))
#define REG_IR          ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x0e))

#define REG_PFIFO       ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x10))
#define TXFE 7 // enable tx fifo
#define RXFE 3 // enable rx fifo
#define TXFIFOSIZE_LSB 4
#define TXFIFOSIZE_MSB 6
#define RXFIFOSIZE_LSB 0
#define RXFIFOSIZE_MSB 2

#define REG_CFIFO       ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x11))
#define TXFLUSH 7 // flush tx buffer
#define RXFLUSH 6 // flush rx buffer

#define REG_SFIFO       ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x12))
#define REG_TWFIFO      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x13))
  // ^ TX water level
#define REG_TCFIFO      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x14))
#define REG_RWFIFO      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x15))
#define REG_RCFIFO      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x16))
#define REG_C7816       ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x18))
#define REG_IE7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x19))
#define REG_IS7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x1a))
#define REG_WP7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x1b))
#define REG_WN7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x1c))
#define REG_WF7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x1d))
#define REG_ET7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x1e))
#define REG_TL7816      ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x1f))
#define REG_AP7816A_T0  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3a))
#define REG_AP7816B_T0  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3b))
#define REG_WP7816A_T0  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3c))
#define REG_WP7816A_T1  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3c))
#define REG_WP7816B_T0  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3d))
#define REG_WP7816B_T1  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3d))
#define REG_WGP7816_T1  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3e))
#define REG_WP7816C_T1  ((volatile uint8_t *) (TEENSY_UART_BASE_ADDR + 0x3f))

#endif // TEENSY_UART_H

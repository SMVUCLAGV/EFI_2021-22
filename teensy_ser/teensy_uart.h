#ifndef TEENSY_UART_H
#define TEENSY_UART_H

#include <stdint.h>

#define _RB_SET(REG_PTR, BIT) (REG_PTR* |= (1 << BIT))   // register bit set
#define _RB_CLR(REG_PTR, BIT) (REG_PTR* &= ~(1 << BIT))  // register bit clear

#define _RW_SET(REG_PTR, WORD, MSB, LSB) (REG_PTR* =                      \
                                            (REG_PTR* &                   \
                                             ~((0xfffffffe << MSB) ^      \
                                                (0xffffffff << LSB)) |    \
                                                (WORD << LSB))) //register word set


#define TEENSY_UART_2_BASE_ADDR 0x4006a000
#define TEENSY_UART_BASE_ADDR  TEENSY_UART_2_BASE_ADDR

// Registers
#define TEENSY_UART_BDH         ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x00))
#define TEENSY_UART_BDL         ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x01))
#define TEENSY_UART_C1          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x02))
#define TEENSY_UART_C2          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x03))
#define TEENSY_UART_S1          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x04))
#define TEENSY_UART_S2          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x05))
#define TEENSY_UART_C3          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x06))
#define TEENSY_UART_D           ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x07))
#define TEENSY_UART_MA1         ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x08))
#define TEENSY_UART_MA2         ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x09))
#define TEENSY_UART_C4          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x0a))
#define TEENSY_UART_C5          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x0b))
#define TEENSY_UART_ED          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x0c))
#define TEENSY_UART_MODEM       ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x0d))
#define TEENSY_UART_IR          ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x0e))
#define TEENSY_UART_PFIFO       ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x10))
#define TEENSY_UART_CFIFO       ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x11))
#define TEENSY_UART_SFIFO       ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x12))
#define TEENSY_UART_TWFIFO      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x13))
#define TEENSY_UART_TCFIFO      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x14))
#define TEENSY_UART_RWFIFO      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x15))
#define TEENSY_UART_RCFIFO      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x16))
#define TEENSY_UART_C7816       ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x18))
#define TEENSY_UART_IE7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x19))
#define TEENSY_UART_IS7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x1a))
#define TEENSY_UART_WP7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x1b))
#define TEENSY_UART_WN7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x1c))
#define TEENSY_UART_WF7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x1d))
#define TEENSY_UART_ET7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x1e))
#define TEENSY_UART_TL7816      ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x1f))
#define TEENSY_UART_AP7816A_T0  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3a))
#define TEENSY_UART_AP7816B_T0  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3b))
#define TEENSY_UART_WP7816A_T0  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3c))
#define TEENSY_UART_WP7816A_T1  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3c))
#define TEENSY_UART_WP7816B_T0  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3d))
#define TEENSY_UART_WP7816B_T1  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3d))
#define TEENSY_UART_WGP7816_T1  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3e))
#define TEENSY_UART_WP7816C_T1  ((volatile uint32_t *) (TEENSY_UART_BASE_ADDR + 0x3f))

#endif // TEENSY_UART_H

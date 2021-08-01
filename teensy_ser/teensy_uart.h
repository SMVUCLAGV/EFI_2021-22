#ifndef TEENSY_UART_H
#define TEENSY_UART_H

#define _RBS(REG_PTR, BIT) (REG_PTR* |= (1 << BIT))   // register bit set
#define _RBC(REG_PTR, BIT) (REG_PTR* &= ~(1 << BIT))  // register bit clear

#define _RWS(REG_PTR, WORD, MSB, LSB) (REG_PTR* =                   \
                                        (REG_PTR* &                 \
                                         ~((0xfffffffe << MSB) ^    \
                                           (0xffffffff << LSB))) |  \
                                        (WORD << LSB)) //register word set


#define TEENSY_UART_2_BASE_ADDR 0x4006a000
#define TEENSY_UART_BASE_ADDR   TEENSY_UART_2_BASE_ADDR

// Registers
const uint32_t* TEENSY_UART_BDH         = (TEENSY_UART_BASE_ADDR + 0x00);
const uint32_t* TEENSY_UART_BDL         = (TEENSY_UART_BASE_ADDR + 0x01);
const uint32_t* TEENSY_UART_C1          = (TEENSY_UART_BASE_ADDR + 0x02);
const uint32_t* TEENSY_UART_C2          = (TEENSY_UART_BASE_ADDR + 0x03);
const uint32_t* TEENSY_UART_S1          = (TEENSY_UART_BASE_ADDR + 0x04);
const uint32_t* TEENSY_UART_S2          = (TEENSY_UART_BASE_ADDR + 0x05);
const uint32_t* TEENSY_UART_C3          = (TEENSY_UART_BASE_ADDR + 0x06);
const uint32_t* TEENSY_UART_D           = (TEENSY_UART_BASE_ADDR + 0x07);
const uint32_t* TEENSY_UART_MA1         = (TEENSY_UART_BASE_ADDR + 0x08);
const uint32_t* TEENSY_UART_MA2         = (TEENSY_UART_BASE_ADDR + 0x09);
const uint32_t* TEENSY_UART_C4          = (TEENSY_UART_BASE_ADDR + 0x0a);
const uint32_t* TEENSY_UART_C5          = (TEENSY_UART_BASE_ADDR + 0x0b);
const uint32_t* TEENSY_UART_ED          = (TEENSY_UART_BASE_ADDR + 0x0c);
const uint32_t* TEENSY_UART_MODEM       = (TEENSY_UART_BASE_ADDR + 0x0d);
const uint32_t* TEENSY_UART_IR          = (TEENSY_UART_BASE_ADDR + 0x0e);
const uint32_t* TEENSY_UART_PFIFO       = (TEENSY_UART_BASE_ADDR + 0x10);
const uint32_t* TEENSY_UART_CFIFO       = (TEENSY_UART_BASE_ADDR + 0x11);
const uint32_t* TEENSY_UART_SFIFO       = (TEENSY_UART_BASE_ADDR + 0x12);
const uint32_t* TEENSY_UART_TWFIFO      = (TEENSY_UART_BASE_ADDR + 0x13);
const uint32_t* TEENSY_UART_TCFIFO      = (TEENSY_UART_BASE_ADDR + 0x14);
const uint32_t* TEENSY_UART_RWFIFO      = (TEENSY_UART_BASE_ADDR + 0x15);
const uint32_t* TEENSY_UART_RCFIFO      = (TEENSY_UART_BASE_ADDR + 0x16);
const uint32_t* TEENSY_UART_C7816       = (TEENSY_UART_BASE_ADDR + 0x18);
const uint32_t* TEENSY_UART_IE7816      = (TEENSY_UART_BASE_ADDR + 0x19);
const uint32_t* TEENSY_UART_IS7816      = (TEENSY_UART_BASE_ADDR + 0x1a);
const uint32_t* TEENSY_UART_WP7816      = (TEENSY_UART_BASE_ADDR + 0x1b);
const uint32_t* TEENSY_UART_WN7816      = (TEENSY_UART_BASE_ADDR + 0x1c);
const uint32_t* TEENSY_UART_WF7816      = (TEENSY_UART_BASE_ADDR + 0x1d);
const uint32_t* TEENSY_UART_ET7816      = (TEENSY_UART_BASE_ADDR + 0x1e);
const uint32_t* TEENSY_UART_TL7816      = (TEENSY_UART_BASE_ADDR + 0x1f);
const uint32_t* TEENSY_UART_AP7816A_T0  = (TEENSY_UART_BASE_ADDR + 0x3a);
const uint32_t* TEENSY_UART_AP7816B_T0  = (TEENSY_UART_BASE_ADDR + 0x3b);
const uint32_t* TEENSY_UART_WP7816A_T0  = (TEENSY_UART_BASE_ADDR + 0x3c);
const uint32_t* TEENSY_UART_WP7816A_T1  = (TEENSY_UART_BASE_ADDR + 0x3c);
const uint32_t* TEENSY_UART_WP7816B_T0  = (TEENSY_UART_BASE_ADDR + 0x3d);
const uint32_t* TEENSY_UART_WP7816B_T1  = (TEENSY_UART_BASE_ADDR + 0x3d);
const uint32_t* TEENSY_UART_WGP7816_T1  = (TEENSY_UART_BASE_ADDR + 0x3e);
const uint32_t* TEENSY_UART_WP7816C_T1  = (TEENSY_UART_BASE_ADDR + 0x3f);

#endif // TEENSY_UART_H

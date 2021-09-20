#ifndef REG_H
#define REG_H

#define READ_NO_OP(REG_PTR)  asm volatile(              \
                                "ldrb r3, [%[value]]"    \
                                : /* no output */       \
                                : [value] "r" (REG_PTR) \
                                : "r3") // Reads from REG_PTR (required to complete reg writes)

#define _RB_GET(REG_PTR, BIT) (((*REG_PTR) >> BIT) & 0x01)                        // register bit clear
#define _RB_SET(REG_PTR, BIT) (*REG_PTR |= (1 << BIT));     READ_NO_OP(REG_PTR)   // register bit set
#define _RB_CLR(REG_PTR, BIT) (*REG_PTR &= ~(1 << BIT));    READ_NO_OP(REG_PTR)   // register bit clear

#define _RW_SET(REG_PTR, MSB, LSB, WORD) (*REG_PTR =                                                      \
                                            (((0xfffffffe << MSB) | ~(0xffffffff << LSB)) & (*REG_PTR)) | \
                                            (~(0xfffffffe << MSB) & ((WORD) << LSB)));                    \
                                          READ_NO_OP(REG_PTR)                     //register word set
#define _RW_GET(REG_PTR, MSB, LSB) (((*REG_PTR) & (~(0xfffffffe << MSB))) >> LSB)

#endif // REG_H

#ifndef REG_H
#define REG_H

#define _RB_GET(REG_PTR, BIT) (((REG_PTR*) >> BIT) & 0x01)  // register bit clear
#define _RB_SET(REG_PTR, BIT) (REG_PTR* |= (1 << BIT))   // register bit set
#define _RB_CLR(REG_PTR, BIT) (REG_PTR* &= ~(1 << BIT))  // register bit clear

#define _RW_SET(REG_PTR, MSB, LSB, WORD) (REG_PTR* &=                     \
                                             ~((0xfffffffe << MSB) ^      \
                                                (0xffffffff << LSB)) |    \
                                                ((WORD) << LSB)) //register word set
#define _RW_GET(REG_PTR, MSB, LSB) (((REG_PTR*) & ~(0xfffffffe << MSB)) >> LSB)

#endif // REG_H

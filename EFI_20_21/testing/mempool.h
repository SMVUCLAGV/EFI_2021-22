#include <stdint.h>
#ifndef MEMPOOL
#define MEMPOOL

void mempool_init();
void* mempool_alloc(uint32_t size);

#endif

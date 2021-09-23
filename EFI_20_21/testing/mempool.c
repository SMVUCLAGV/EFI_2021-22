#include "mempool.h"
#include <stdint.h>
#define BTOUINT32(size) ((size / 4) + ((size % 4) + 3) / 4)

static uint32_t pool [10000];
static uint32_t *curr;

void mempool_init() {
  curr = pool;
}

void* mempool_alloc(uint32_t size) {
  uint32_t *o = curr;
  curr += BTOUINT32(size); 
  if(curr - pool >= 10000)
    return 0;

  return o;
}

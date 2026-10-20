#include "common.h"

extern void find_unused_pool_slot(void *used_addrs, s32 pool_index, s32 slot_count);

/* Calls find_unused_pool_slot with D_8001029C and fixed parameters 0 and 20. */
void find_unused_default_pool_slot(void) {
    find_unused_pool_slot((void *)0x8001029C, 0, 20);
}

#include "common.h"
#include "town/shop.h"

/* Calls find_unused_pool_slot with (void *)0x8001029C, 0, 20. */
void find_unused_default_pool_slot(void) {
    find_unused_pool_slot((void *)0x8001029C, 0, 20);
}

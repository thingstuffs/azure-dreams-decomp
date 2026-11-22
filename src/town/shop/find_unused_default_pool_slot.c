#include "common.h"
#include "town/shop.h"

/* Look up a free slot in the twenty-entry carried item pool. */
void find_unused_default_pool_slot(void) {
    find_unused_pool_slot((DungeonItemEntry **)0x8001029C, 0, 20);
}

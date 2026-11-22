#include "common.h"
#include "sdk/libc.h"
#include "town/shop.h"

extern DungeonItemEntry *D_800D1648[];

/* Returns the first unused four-byte slot address in the selected pool. */
DungeonItemEntry *find_unused_pool_slot(DungeonItemEntry **used_addrs, s32 pool_index, s32 slot_count) {
    u8 used[256];
    DungeonItemEntry *base;
    s32 slot;

    bzero(used, slot_count);
    base = D_800D1648[pool_index];

    while (*used_addrs != 0) {
        used[((unsigned long)*used_addrs++ - (unsigned long)base) / sizeof(*base)] = 1;
    }

    slot = 0;
    if (used[0] != 0) {
        do {
            slot++;
        } while (used[slot] != 0);
    }

    return base + slot;
}

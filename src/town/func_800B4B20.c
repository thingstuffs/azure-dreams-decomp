#include "common.h"

extern void bzero(void *dst, s32 size);
extern s32 D_800D1648[];

/* Returns the first unused four-byte slot address in the selected pool. */
u32 func_800B2280(s32 *used_addrs, s32 pool_index, s32 slot_count) {
    u8 used[256];
    s32 base;
    s32 slot;

    bzero(used, slot_count);
    base = D_800D1648[pool_index];

    while (*used_addrs != 0) {
        used[(u32)(*used_addrs++ - base) >> 2] = 1;
    }

    slot = 0;
    if (used[0] != 0) {
        do {
            slot++;
        } while (used[slot] != 0);
    }

    return base + (slot * 4);
}

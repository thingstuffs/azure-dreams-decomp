#include "common.h"

typedef struct S_800799BC {
    u32 flags;
    u32 size;
} S_800799BC;

extern S_800799BC *D_800799BC[3];

/* Returns whether a non-skipped block contains the address or starts at or beyond it. */
s32 func_8005D95C(u32 address) {
    S_800799BC *entry;
    u32 block_start;
    u32 skip_mask;
    u32 end_mask;
    u32 start_mask;

    if (D_800799BC[0] == 0) {
        return 0;
    }
    skip_mask = 0x80000000;
    end_mask = 0x40000000;
    start_mask = 0x0FFFFFFF;
    entry = D_800799BC[0];
    do {
        block_start = entry->flags;
        if (block_start & skip_mask) {
            entry++;
            continue;
        }
        if (block_start & end_mask) {
            break;
        }
        block_start = block_start & start_mask;
        if (block_start >= address) {
            return 1;
        }
        if (address < block_start + entry->size) {
            return 1;
        }
        entry++;
    } while (1);
    return 0;
}

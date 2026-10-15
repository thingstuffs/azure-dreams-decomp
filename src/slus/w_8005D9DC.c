#include "slus/sound_range_records.h"

/* Returns whether the shifted value precedes or lies within an active list entry range. */
s32 func_8005D9DC(u32 value)
{
    S_800799BC *list;
    S_800799BC *entry;
    u32 skip_mask, stop_mask, base_mask;

    value = value << D_80079980;

    list = D_800799BC;
    if (list == 0) {
        return 0;
    }

    skip_mask = 0x80000000;
    stop_mask = 0x40000000;
    base_mask = 0x0FFFFFFF;

    entry = list;
    while (1) {
        u32 flags = entry->flags;

        if (!(flags & skip_mask)) {
            u32 base;

            if (flags & stop_mask) {
                break;
            }

            base = flags & base_mask;
            if (base >= value) {
                return 1;
            }
            if (value < base + entry->size) {
                return 1;
            }
        }

        entry++;
    }
    return 0;
}

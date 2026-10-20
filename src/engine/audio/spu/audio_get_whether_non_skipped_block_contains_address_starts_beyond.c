#include "engine/audio/spu/sound_range_records.h"



/* Initializes and publishes the record-list head for a positive count, returning the count or zero. */
s32 func_8005D838(s32 count, S_800799BC *record) {
    s32 result = count;
    if (result > 0) {
        s32 shift = D_80079980;
        record->flags = 0x40001010;
        D_800799BC = record;
        D_800799B8 = 0;
        D_800799B4 = result;
        record->size = (0x10000 << shift) - 0x1010;
        return result;
    } else {
        result = 0;
        return result;
    }
}

/* Returns whether a non-skipped block contains the address or starts at or beyond it. */
s32 audio_get_whether_non_skipped_block_contains_address_starts_beyond(u32 address) {
    S_800799BC *entry;
    u32 block_start;
    u32 skip_mask;
    u32 end_mask;
    u32 start_mask;

    if (D_800799BC == 0) {
        return 0;
    }
    skip_mask = 0x80000000;
    end_mask = 0x40000000;
    start_mask = 0x0FFFFFFF;
    entry = D_800799BC;
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

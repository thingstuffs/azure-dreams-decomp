#include "slus/sound_range_records.h"

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

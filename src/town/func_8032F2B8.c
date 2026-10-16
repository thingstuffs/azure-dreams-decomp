#include "common.h"

s32 townFindEntryIndexByGridBytes(s32, s32);                                /* extern */

/* Return whether townFindEntryIndexByGridBytes produces a result other than -1. */
s32 townHasMatchingEntryResult(s32 first_value, s32 second_value) {
    return ~townFindEntryIndexByGridBytes(first_value, second_value) != 0;
}

#include "common.h"
#include "shared/tile_object.h"

extern s32 D_80100E2C;

/* Stores the supplied value and returns D_80082E88 minus 12 with its sign bit cleared. */
s32 store_value_and_get_masked_offset(s32 unused_0, s32 unused_1, s32 unused_2, s32 stored_value) {
    D_80100E2C = stored_value;
    return (D_80082E80.unk_008 - 0xC) & 0x7FFFFFFF;
}

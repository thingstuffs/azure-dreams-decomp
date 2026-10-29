#include "common.h"
#include "shared/tile_object.h"
#include "town/player.h"

extern s32 D_80100E2C;

/*
 * Stores the supplied word in D_80100E2C and returns the sprite-source offset minus 12 with its
 * sign bit cleared.
 */
s32 store_value_and_get_masked_offset(s32 unused_0, s32 unused_1, s32 unused_2, s32 stored_value) {
    D_80100E2C = stored_value;
    return (reference_tile_object.sprite_source - 0xC) & 0x7FFFFFFF;
}

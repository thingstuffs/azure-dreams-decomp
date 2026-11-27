#include "common.h"
#include "shared/tile_object.h"
#include "town/player.h"
#include "shared/sprite_frame_state.h"

extern s32 pending_record_value[3];

/*
 * Stores the supplied word in D_80100E2C and returns the sprite-source offset minus 12 with its
 * sign bit cleared.
 */
s32 store_pending_value_and_get_source(s32 unused_0, s32 unused_1, SpriteFrameState *unused_2, s32 stored_value) {
    pending_record_value[0] = stored_value;
    return (reference_tile_object.sprite_source - 0xC) & 0x7FFFFFFF;
}

#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/level.h"

s16 find_flagged_tile_entry();    /* extern */

/* Call find_flagged_tile_entry with a temporary tile-based value in unk_88. */
s16 check_tile_entry_at_adjusted_height(s32 context, s32 data, SpriteFrameState *tile, EntityRec *state) {
    s16 result;
    u16 saved_value;

    saved_value = ((u16)state->unk_88);
    state->unk_88 = sample_terrain_surface_height((tile->tile_x << 6) | 0x20, (tile->tile_y << 6) | 0x20, (s16) (saved_value - 0x20));
    result = find_flagged_tile_entry(context, data, tile, state);
    state->unk_88 = saved_value;
    return result;
}

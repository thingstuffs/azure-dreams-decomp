#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/beldo_large.h"

typedef struct S_8016EC04_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8016EC04_1;   /* state in relocate_multi_form_actor */


#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

/* Reposition the current entity relative to the origin using the selected offset. */
void relocate_multi_form_actor(s32 offset_index)
{
    s16 delta[2] = { 0, -12 };
    ObjectNodeHeader *object;
    S_8016EC04_1 *state;
    SpriteFrameState *sprite;
    void *motion;
    u8 *step;
    TileObject *origin;

    object = beldo_actor_nodes;
    state = NODE_BODY(object);
    sprite = object->sprite;
    motion = object->position;

    sprite->flags &= 0xFF7F;

    update_map_cell_flags_with_item_limit(sprite->tile_x, sprite->tile_y,
                  (state->unk_1C & 0x2000) ? 0x300 : 0x3000);

    origin = &reference_tile_object;
    step = (u8 *)&delta[offset_index * 2];
    sprite->tile_x = origin->tile_position.parts.tile_x + step[0];
    sprite->tile_y = origin->tile_position.parts.tile_y + step[2];

    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);

    cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                  (state->unk_1C & 0x2000) ? 0x300 : 0x3000);
}

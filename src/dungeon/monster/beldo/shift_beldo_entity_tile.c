#include "common.h"
#include "dungeon/level.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/monster/beldo/command_ticks_data.h"
#include "dungeon/player/object.h"

#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

/* Repositions the current entity relative to the origin and updates its motion. */
void shift_beldo_entity_tile(s32 offset_index)
{
    s16 offsets[2] = { 1, -1 };
    ObjectNodeHeader *object;
    ActorRecord *state;
    SpriteFrameState *entity;
    void *motion;
    u8 *offset_bytes;
    TileObject *origin;

    object = beldo_active_entity;
    state = NODE_BODY(object);
    entity = object->sprite;
    motion = object->position;

    entity->flags &= 0xFF7F;

    update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y,
                  (state->flags1C & 0x2000) ? 0x300 : 0x3000);

    origin = &reference_tile_object;
    offset_bytes = (u8 *)&offsets[offset_index * 2];
    entity->tile_x = origin->tile_position.parts.tile_x + offset_bytes[0];
    entity->tile_y = origin->tile_position.parts.tile_y + offset_bytes[2];

    set_record_integer_tile_center(motion, entity->tile_x, entity->tile_y);

    cycle_map_cell_flags(entity->tile_x, entity->tile_y,
                  (state->flags1C & 0x2000) ? 0x300 : 0x3000);
}

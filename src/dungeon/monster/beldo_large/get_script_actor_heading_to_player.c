#include "common.h"
#include "dungeon/monster/beldo_large_data.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo_large.h"


/* Returns the signed coordinate calculation result scaled down by nine bits. */
s32 get_script_actor_heading_to_player(void) {
    u16 value;
    SpriteFrameState *sprite;

    sprite = beldo_actor_nodes->sprite;
    return (get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                          reference_tile_object.tile_position.parts.tile_y, &value) << 0x10) >> 0x19;
}

#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo_large.h"

extern u8 *beldo_actor_nodes;

/* Returns the signed coordinate calculation result scaled down by nine bits. */
s32 get_script_actor_heading_to_player(void) {
    u16 value;
    u8 *state;

    state = *(u8 * *)&((ObjectNodeHeader *)beldo_actor_nodes)->sprite;
    return (get_rounded_facing_and_rounding_flag(state[0x24], state[0x25], reference_tile_object.tile_position.parts.tile_x,
                          reference_tile_object.tile_position.parts.tile_y, &value) << 0x10) >> 0x19;
}

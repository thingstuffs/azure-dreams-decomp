#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/effect.h"
#include "dungeon/monster/ghosh.h"

/* Invokes the placement helper at the tile center using the current entity value. */
void place_spawn_at_reference_tile_center(void) {
    setup_object_within_planar_range(
        ((&g_dungeon_status.monster_spawn_table)),
        (reference_tile_object.tile_position.parts.tile_x << 6) | 0x20,
        (reference_tile_object.tile_position.parts.tile_y << 6) | 0x20,
        dungeon_actor_ring_anchor->ground_height,
        1,
        0x400
        );
}

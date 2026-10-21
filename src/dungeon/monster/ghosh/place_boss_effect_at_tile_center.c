#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void setup_object_within_planar_range(void *, s32, s32, s32, s32, s32);

/* Invokes the placement helper at the tile center using the current entity value. */
void place_boss_effect_at_tile_center(void) {
    setup_object_within_planar_range(
        ((u8 *)(&g_dungeon_status.monster_spawn_table)),
        (reference_tile_object.tile_position.parts.tile_x << 6) | 0x20,
        (reference_tile_object.tile_position.parts.tile_y << 6) | 0x20,
        *(s16 *)((u8 *)dungeon_actor_ring_anchor + 0x88),
        1,
        0x400
        );
}

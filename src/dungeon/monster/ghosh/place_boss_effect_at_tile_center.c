#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void setup_object_within_planar_range(void *, s32, s32, s32, s32, s32);

/* Invokes the placement helper at the tile center using the current entity value. */
void place_boss_effect_at_tile_center(void) {
    setup_object_within_planar_range(
        ((u8 *)(&g_dungeon_status.unk_18)),
        (D_80082E80.tileX << 6) | 0x20,
        (D_80082E80.tileY << 6) | 0x20,
        *(s16 *)((u8 *)D_800E3D7C + 0x88),
        1,
        0x400
        );
}

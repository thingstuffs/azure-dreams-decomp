#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

void set_record_integer_tile_center();              /* extern */
s16 sample_terrain_surface_height();                   /* extern */

typedef struct S_800AC480_0 {
    u8 pad_00[0x92];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
} S_800AC480_0;   /* arg0 in interpolate_actor_to_terrain_tile */

   /* arg2 in interpolate_actor_to_terrain_tile */


typedef struct S_800AC480_3 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800AC480_3;   /* arg3 in interpolate_actor_to_terrain_tile */

typedef struct S_800AC480_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AC480_4;   /* global_base in interpolate_actor_to_terrain_tile */

/* Update movement toward the target tile and finalize position and height when the timer expires. */
s32 interpolate_actor_to_terrain_tile(S_800AC480_0 *move_state, EntityRec *motion, MovingTile *target_tile, S_800AC480_3 *height_state) {
    s32 delta;
    s32 coord;
    s32 x_step;
    s16 ticks_left;
    s16 next_ticks;
    s16 target_height;

    ticks_left = move_state->unk_96;
    if (ticks_left != 0) {
        delta = target_tile->unk_24 << 6;
        coord = motion->x.w.i;
        coord -= 0x20;
        delta -= coord;
        x_step = (delta << 0x10) / ticks_left;
        coord = motion->y.w.i;
        motion->unk_0C = x_step;
        delta = target_tile->unk_25 << 6;
        coord -= 0x20;
        delta -= coord;
        motion->unk_10 = (delta << 0x10) / (s16) move_state->unk_96;
    }
    next_ticks = (u16) move_state->unk_96 - 1;
    move_state->unk_96 = next_ticks;
    if ((next_ticks << 0x10) <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, target_tile->unk_24, target_tile->unk_25);
        target_height = sample_terrain_surface_height((target_tile->unk_24 << 6) | 0x20, (target_tile->unk_25 << 6) | 0x20,
            (s16) (height_state->unk_88 - 0x20));
        if (target_height < 0x200) {
            move_state->unk_92 = (u16) (move_state->unk_92 + (height_state->unk_88 - target_height));
            height_state->unk_88 = (u16) target_height;
        }
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) - 1);
        return 1;
    }
    return 0;
}

/* MECHANISM: Explicit s32 delta/coord/x_step lifetimes preserve each coord-0x20
   subtraction and hoist the second lh into the first division's load-delay gap.
   Direct 0/1 returns plus a kept absolute D_80083460 base produce the retail
   v0 delay-slot value and a0-based lhu/sh tail without changing the 0x20 frame. */

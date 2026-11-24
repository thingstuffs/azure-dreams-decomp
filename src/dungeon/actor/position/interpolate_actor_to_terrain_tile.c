#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"

/* Update movement toward the target tile and finalize position and height when the timer expires. */
s32 interpolate_actor_to_terrain_tile(ActorRecord *move_state, ObjectPosition *motion, MovingTile *target_tile, ActorRecord *height_state) {
    s32 delta;
    s32 coord;
    s32 x_step;
    s16 ticks_left;
    s16 next_ticks;
    s16 target_height;

    ticks_left = move_state->action_timer;
    if (ticks_left != 0) {
        delta = target_tile->tile_x << 6;
        coord = motion->x.w.i;
        coord -= 0x20;
        delta -= coord;
        x_step = (delta << 0x10) / ticks_left;
        coord = motion->y.w.i;
        motion->velocity_x = x_step;
        delta = target_tile->tile_y << 6;
        coord -= 0x20;
        delta -= coord;
        motion->velocity_y = (delta << 0x10) / (s16) move_state->action_timer;
    }
    next_ticks = (u16) move_state->action_timer - 1;
    move_state->action_timer = next_ticks;
    if ((next_ticks << 0x10) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, target_tile->tile_x, target_tile->tile_y);
        target_height = sample_terrain_surface_height((target_tile->tile_x << 6) | 0x20, (target_tile->tile_y << 6) | 0x20,
            (s16) (height_state->ground_height - 0x20));
        if (target_height < 0x200) {
            move_state->unk_90.parts.high = (u16) (move_state->unk_90.parts.high + (height_state->ground_height - target_height));
            height_state->ground_height = (u16) target_height;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        return 1;
    }
    return 0;
}

#include "common.h"
#include "slus/imports.h"
#include "dungeon/monster/blume.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

   /* arg1 in update_damped_height_effect */

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

/* Applies damped motion and height limits, updates the object, and checks its lifetime. */
void update_damped_height_effect(DirectionalParticlesAndResetActorBody *state, ObjectPosition *position_arg, SpriteFrameState *object)
{
    ObjectPosition *position = position_arg;
    s32 height;
    u16 ticks_left;

    position->x.v += state->velocity_x;
    state->velocity_x = (state->velocity_x * 2) / 3;
    if ((s16)check_left_tile_and_center_height(position->x.unsigned_parts.integer,
                           position->y.unsigned_parts.integer,
                           position->z.w.i) != 0) {
        position->x.v -= state->velocity_x;
        state->velocity_x = 0;
    }

    position->y.v += state->velocity_y;
    state->velocity_y = (state->velocity_y * 2) / 3;
    if ((s16)check_left_tile_and_center_height(position->x.unsigned_parts.integer,
                           position->y.unsigned_parts.integer,
                           position->z.w.i) != 0) {
        position->y.v -= state->velocity_y;
        state->velocity_y = 0;
    }

    position->z.v += state->velocity_z;
    state->velocity_z += state->acceleration_z;

    height = position->z.w.i;
    if (sample_terrain_surface_height(position->x.unsigned_parts.integer,
                      position->y.unsigned_parts.integer,
                      (s16)(position->z.unsigned_parts.integer - 4)) - 0x10 < height) {
        state->velocity_z = 0;
        position->z.w.i = sample_terrain_surface_height(
            position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            (s16)(position->z.unsigned_parts.integer - 4)) - 0x11;
        position->z.w.frac = 0;
        if (state->hit_state == 0) {
            state->hit_state = 1;
            state->lifetime = 0;
        }
    }

    state->unk_9E++;
    advance_sprite_animation_and_textures(object);
    ticks_left = state->lifetime - 1;
    state->lifetime = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (object->flags & 0x8000) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

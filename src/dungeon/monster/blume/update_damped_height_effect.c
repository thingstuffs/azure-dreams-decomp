#include "common.h"
#include "slus/imports.h"
#include "dungeon/monster/blume.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80171040_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
        struct { u8 pad[0x2]; u16 v; } at02p;
    } unk_08;   /* overlapping accesses */
} S_80171040_0;   /* arg1 in update_damped_height_effect */

s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

/* Applies damped motion and height limits, updates the object, and checks its lifetime. */
void update_damped_height_effect(DirectionalParticlesAndResetActorBody *state, void *position_arg, SpriteFrameState *object)
{
    S_80171040_0 *position = position_arg;
    s32 height;
    u16 ticks_left;

    position->unk_00.at00.v += state->velocity_x;
    state->velocity_x = (state->velocity_x * 2) / 3;
    if ((s16)check_left_tile_and_center_height(position->unk_00.at02.v,
                           position->unk_04.at02.v,
                           position->unk_08.at02.v) != 0) {
        position->unk_00.at00.v -= state->velocity_x;
        state->velocity_x = 0;
    }

    position->unk_04.at00.v += state->velocity_y;
    state->velocity_y = (state->velocity_y * 2) / 3;
    if ((s16)check_left_tile_and_center_height(position->unk_00.at02.v,
                           position->unk_04.at02.v,
                           position->unk_08.at02.v) != 0) {
        position->unk_04.at00.v -= state->velocity_y;
        state->velocity_y = 0;
    }

    position->unk_08.at00.v += state->velocity_z;
    state->velocity_z += state->acceleration_z;

    height = position->unk_08.at02.v;
    if (sample_terrain_surface_height(position->unk_00.at02.v,
                      position->unk_04.at02.v,
                      (s16)(position->unk_08.at02u.v - 4)) - 0x10 < height) {
        state->velocity_z = 0;
        position->unk_08.at02.v = sample_terrain_surface_height(
            position->unk_00.at02.v, position->unk_04.at02.v,
            (s16)(position->unk_08.at02p.v - 4)) - 0x11;
        position->unk_08.at00u.v = 0;
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

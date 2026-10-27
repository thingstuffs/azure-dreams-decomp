#include "common.h"
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

typedef struct S_80171040_1 {
    u8 pad_00[0x96];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x4];
    u16 unk_9E;
    u8 pad_A0[0x4];
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
} S_80171040_1;   /* arg0 in update_damped_height_effect */

extern void advance_sprite_animation_and_textures(void *entity);
s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

/* Applies damped motion and height limits, updates the object, and checks its lifetime. */
void update_damped_height_effect(void *state, void *position, SpriteFrameState *object)
{
    s32 height;
    u16 ticks_left;

    ((S_80171040_0 *)position)->unk_00.at00.v += ((S_80171040_1 *)state)->unk_A4;
    ((S_80171040_1 *)state)->unk_A4 = (((S_80171040_1 *)state)->unk_A4 * 2) / 3;
    if ((s16)check_left_tile_and_center_height(((S_80171040_0 *)position)->unk_00.at02.v,
                           ((S_80171040_0 *)position)->unk_04.at02.v,
                           ((S_80171040_0 *)position)->unk_08.at02.v) != 0) {
        ((S_80171040_0 *)position)->unk_00.at00.v -= ((S_80171040_1 *)state)->unk_A4;
        ((S_80171040_1 *)state)->unk_A4 = 0;
    }

    ((S_80171040_0 *)position)->unk_04.at00.v += ((S_80171040_1 *)state)->unk_A8;
    ((S_80171040_1 *)state)->unk_A8 = (((S_80171040_1 *)state)->unk_A8 * 2) / 3;
    if ((s16)check_left_tile_and_center_height(((S_80171040_0 *)position)->unk_00.at02.v,
                           ((S_80171040_0 *)position)->unk_04.at02.v,
                           ((S_80171040_0 *)position)->unk_08.at02.v) != 0) {
        ((S_80171040_0 *)position)->unk_04.at00.v -= ((S_80171040_1 *)state)->unk_A8;
        ((S_80171040_1 *)state)->unk_A8 = 0;
    }

    ((S_80171040_0 *)position)->unk_08.at00.v += ((S_80171040_1 *)state)->unk_AC;
    ((S_80171040_1 *)state)->unk_AC += ((S_80171040_1 *)state)->unk_B0;

    height = ((S_80171040_0 *)position)->unk_08.at02.v;
    if (sample_terrain_surface_height(((S_80171040_0 *)position)->unk_00.at02.v,
                      ((S_80171040_0 *)position)->unk_04.at02.v,
                      (s16)(((S_80171040_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_80171040_1 *)state)->unk_AC = 0;
        ((S_80171040_0 *)position)->unk_08.at02.v = sample_terrain_surface_height(
            ((S_80171040_0 *)position)->unk_00.at02.v, ((S_80171040_0 *)position)->unk_04.at02.v,
            (s16)(((S_80171040_0 *)position)->unk_08.at02p.v - 4)) - 0x11;
        ((S_80171040_0 *)position)->unk_08.at00u.v = 0;
        if (((S_80171040_1 *)state)->unk_98 == 0) {
            ((S_80171040_1 *)state)->unk_98 = 1;
            ((S_80171040_1 *)state)->unk_96 = 0;
        }
    }

    ((S_80171040_1 *)state)->unk_9E++;
    advance_sprite_animation_and_textures(object);
    ticks_left = ((S_80171040_1 *)state)->unk_96 - 1;
    ((S_80171040_1 *)state)->unk_96 = ticks_left;
    if ((s16)ticks_left <= 0) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (object->flags & 0x8000) {
        (*(u16 *)((u8 *)state + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

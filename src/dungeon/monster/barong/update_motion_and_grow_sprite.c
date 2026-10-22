#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80170D58_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_80170D58_0;   /* arg1 in update_motion_and_grow_sprite */

typedef struct S_80170D58_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    u8 pad_1C[0xA];
    union { s16 s; u16 u; } unk_26;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0x2A];
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} S_80170D58_1;   /* arg0 in update_motion_and_grow_sprite */

extern void advance_sprite_animation_and_textures(void *entity);
extern s32 check_left_tile_and_center_height(u16 x, u16 y, s16 z);
extern s16 sample_terrain_surface_height(u16 x, u16 y, s16 min_height);

/* Update motion with collision checks, grow the sprite, and flag expired objects. */
void update_motion_and_grow_sprite(void *motion, void *position, void *sprite)
{
    s32 height;
    u16 frame_count;
    u16 scale_x;
    u16 scale_y;
    u16 life_ticks;

    ((S_80170D58_0 *)position)->unk_00.at00.v += ((S_80170D58_1 *)motion)->unk_54;
    ((S_80170D58_1 *)motion)->unk_54 += ((S_80170D58_1 *)motion)->unk_60;
    if ((sample_terrain_surface_height(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                       ((S_80170D58_0 *)position)->unk_08.at02.v) < 0x200) &&
        ((s16)check_left_tile_and_center_height(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                            ((S_80170D58_0 *)position)->unk_08.at02.v) != 0)) {
        ((S_80170D58_0 *)position)->unk_00.at00.v -= ((S_80170D58_1 *)motion)->unk_54;
        ((S_80170D58_1 *)motion)->unk_54 = 0;
        ((S_80170D58_1 *)motion)->unk_60 = 0;
    }

    ((S_80170D58_0 *)position)->unk_04.at00.v += ((S_80170D58_1 *)motion)->unk_58;
    ((S_80170D58_1 *)motion)->unk_58 += ((S_80170D58_1 *)motion)->unk_64;
    if ((sample_terrain_surface_height(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                       ((S_80170D58_0 *)position)->unk_08.at02.v) < 0x200) &&
        ((s16)check_left_tile_and_center_height(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                            ((S_80170D58_0 *)position)->unk_08.at02.v) != 0)) {
        ((S_80170D58_0 *)position)->unk_04.at00.v -= ((S_80170D58_1 *)motion)->unk_58;
        ((S_80170D58_1 *)motion)->unk_58 = 0;
        ((S_80170D58_1 *)motion)->unk_64 = 0;
    }

    ((S_80170D58_0 *)position)->unk_08.at00.v += ((S_80170D58_1 *)motion)->unk_5C;
    ((S_80170D58_1 *)motion)->unk_5C += ((S_80170D58_1 *)motion)->unk_68;
    height = ((S_80170D58_0 *)position)->unk_08.at02.v;
    if (sample_terrain_surface_height(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                      (s16)(((S_80170D58_0 *)position)->unk_08.at02u.v - 4)) - 0x10 < height) {
        ((S_80170D58_1 *)motion)->unk_5C = 0;
        ((S_80170D58_0 *)position)->unk_08.at02.v =
            sample_terrain_surface_height(((S_80170D58_0 *)position)->unk_00.at02.v, ((S_80170D58_0 *)position)->unk_04.at02.v,
                          (s16)(((S_80170D58_0 *)position)->unk_08.at02u.v - 4)) - 0x11;
        ((S_80170D58_0 *)position)->unk_08.at00u.v = 0;
        if (((S_80170D58_1 *)motion)->unk_1A == 0) {
            ((S_80170D58_1 *)motion)->unk_1A = 1;
            ((S_80170D58_1 *)motion)->unk_26.s = 0;
        }
    }

    frame_count = ((S_80170D58_1 *)motion)->unk_28 + 1;
    ((S_80170D58_1 *)motion)->unk_28 = frame_count;
    if ((frame_count & 3) == 0) {
        advance_sprite_animation_and_textures(sprite);
    }

    scale_x = ((SpriteFrameState *)sprite)->scale_x + 0x64;
    ((SpriteFrameState *)sprite)->scale_x = scale_x;
    if (scale_x > 0x1000) {
        ((SpriteFrameState *)sprite)->scale_x = 0x1000;
    }

    scale_y = ((SpriteFrameState *)sprite)->scale_y + 0x64;
    ((SpriteFrameState *)sprite)->scale_y = scale_y;
    if (scale_y > 0x1000) {
        ((SpriteFrameState *)sprite)->scale_y = 0x1000;
    }

    life_ticks = ((S_80170D58_1 *)motion)->unk_26.u - 1;
    ((S_80170D58_1 *)motion)->unk_26.u = life_ticks;
    if ((s16)life_ticks <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    if (((SpriteFrameState *)sprite)->flags & 0x8000) {
        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

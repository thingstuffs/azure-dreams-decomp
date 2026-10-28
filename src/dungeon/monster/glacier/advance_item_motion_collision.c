#include "common.h"
#include "shared/object_flags.h"
#include "slus.h"

typedef struct S_80174300_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
    u8 pad_20[0x30];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
} S_80174300_0;   /* arg0 in advance_item_motion_collision */

typedef struct S_80174300_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
} S_80174300_1;   /* arg1 in advance_item_motion_collision */


extern s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern s16 sample_terrain_surface_height();

/* Advance motion, resolve collisions, and flag expired movement. */
void advance_item_motion_collision(void *motion, void *position, void *update_arg) {
    s32 height;

    ((S_80174300_0 *)motion)->unk_1E = ((S_80174300_0 *)motion)->unk_1E - 1;
    advance_sprite_animation_and_textures(update_arg);
    ((S_80174300_1 *)position)->unk_00.at00.v += ((S_80174300_0 *)motion)->unk_50;
    ((S_80174300_0 *)motion)->unk_50 += ((S_80174300_0 *)motion)->unk_5C;
    if ((check_left_tile_and_center_height(((S_80174300_1 *)position)->unk_00.at02.v, ((S_80174300_1 *)position)->unk_04.at02.v,
        ((S_80174300_1 *)position)->unk_08.at02.v) << 16) != 0) {
        ((S_80174300_1 *)position)->unk_00.at00.v -= ((S_80174300_0 *)motion)->unk_50;
        ((S_80174300_0 *)motion)->unk_50 = 0;
        ((S_80174300_0 *)motion)->unk_5C = 0;
    }
    ((S_80174300_1 *)position)->unk_04.at00.v += ((S_80174300_0 *)motion)->unk_54;
    ((S_80174300_0 *)motion)->unk_54 += ((S_80174300_0 *)motion)->unk_60;
    if ((check_left_tile_and_center_height(((S_80174300_1 *)position)->unk_00.at02.v, ((S_80174300_1 *)position)->unk_04.at02.v,
        ((S_80174300_1 *)position)->unk_08.at02.v) << 16) != 0) {
        ((S_80174300_1 *)position)->unk_04.at00.v -= ((S_80174300_0 *)motion)->unk_54;
        ((S_80174300_0 *)motion)->unk_54 = 0;
        ((S_80174300_0 *)motion)->unk_60 = 0;
    }
    ((S_80174300_1 *)position)->unk_08.at00.v += ((S_80174300_0 *)motion)->unk_58;
    ((S_80174300_0 *)motion)->unk_58 += ((S_80174300_0 *)motion)->unk_64;
    height = ((S_80174300_1 *)position)->unk_08.at02.v;
    if ((sample_terrain_surface_height(((S_80174300_1 *)position)->unk_00.at02.v, ((S_80174300_1 *)position)->unk_04.at02.v,
                       (s16)((u16)((S_80174300_1 *)position)->unk_08.at02u.v - 4)) - 0x10) < height) {
        ((S_80174300_0 *)motion)->unk_58 = 0;
        ((S_80174300_0 *)motion)->unk_54 = 0;
        ((S_80174300_0 *)motion)->unk_50 = 0;
        ((S_80174300_1 *)position)->unk_08.at02.v = sample_terrain_surface_height(((S_80174300_1 *)position)->unk_00.at02.v,
            ((S_80174300_1 *)position)->unk_04.at02.v,
                                               (s16)((u16)((S_80174300_1 *)position)->unk_08.at02.v - 4)) - 0x11;
        ((S_80174300_1 *)position)->unk_08.at00u.v = 0;
        ((S_80174300_0 *)motion)->unk_1E = 0;
    }
    if ((s16)((S_80174300_0 *)motion)->unk_1E <= 0) {
        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

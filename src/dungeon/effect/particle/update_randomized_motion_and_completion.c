#include "common.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

typedef struct S_81814C48_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_81814C48_0;   /* arg1 in update_randomized_motion_and_completion */

typedef struct S_81814C48_1 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
} S_81814C48_1;   /* arg0 in update_randomized_motion_and_completion */

typedef struct S_81814C48_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81814C48_2;   /* arg2 in update_randomized_motion_and_completion */


extern s32 rand();
extern s16 sample_terrain_surface_height();
extern s16 D_80025338;

/* Updates a position with randomized motion, reduces speed, and flags completion. */
void update_randomized_motion_and_completion(void *state, void *position, void *linked_state)
{
    s16 speed;
    s32 x_step;
    s32 coord_value;
    s32 z_random;
    s32 x;
    s32 y;
    s32 z;
    s32 z_step;

    z = (*(u16 *)((u8 *)position + 0xA));
    x = ((S_81814C48_0 *)position)->unk_00.at02.v;
    y = ((S_81814C48_0 *)position)->unk_04.at02.v;
    D_80025338 = 1;
    if ((s16)((S_81814C48_0 *)position)->unk_08.at02.v <
        sample_terrain_surface_height(x, y, (s16)(z + 2))) {
        x_step = ((*(s16 *)(((s8 *)dir_step_x) + (((S_81814C48_1 *)state)->unk_14 * 2)) *
                   ((S_81814C48_1 *)state)->unk_32) << 9) +
                  (rand() & 0xFFFF);
        coord_value = ((S_81814C48_0 *)position)->unk_00.at00.v + x_step;
        ((S_81814C48_0 *)position)->unk_00.at00.v = coord_value;
        z_step = ((*(s16 *)(((s8 *)dir_step_y) + (((S_81814C48_1 *)state)->unk_14 * 2)) *
                   ((S_81814C48_1 *)state)->unk_32) << 9) +
                    (rand(x_step) & 0xFFFF);
        coord_value = ((S_81814C48_0 *)position)->unk_04.at00.v + z_step;
        ((S_81814C48_0 *)position)->unk_04.at00.v = coord_value;
        z_random = rand(z_step);
        z_step = 0xFFFE0000;
        coord_value = ((S_81814C48_0 *)position)->unk_08.at00.v + z_step;
        coord_value -= z_random & 0xFFF;
        ((S_81814C48_0 *)position)->unk_08.at00.v = coord_value;
    }
    speed = (u16)((S_81814C48_1 *)state)->unk_32 - 8;
    ((S_81814C48_1 *)state)->unk_32 = speed;
    if (((speed << 16) <= 0) || (((S_81814C48_2 *)linked_state)->unk_14 & 0x8000)) {
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

/* MECHANISM: Byte table bases with s16 loads plus explicit accumulator RMWs place each lw before mflo. */

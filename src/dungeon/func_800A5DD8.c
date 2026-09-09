#include "common.h"

typedef struct S_800AB538_0 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800AB538_0;   /* p0 in func_800AB538 */

typedef struct S_800AB538_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
    u16 unk_8A;
} S_800AB538_1;   /* p3 in func_800AB538 */

typedef struct S_800AB538_2 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_800AB538_2;   /* base in func_800AB538 */

typedef struct S_800AB538_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s32 unk_14;
} S_800AB538_3;   /* p1 in func_800AB538 */

typedef struct S_800AB538_4 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800AB538_4;   /* p2 in func_800AB538 */



extern s32 func_800644B8();

extern u16 D_80013714;
extern u8 D_80083780[];
extern s16 D_8008378A;

/* Move toward the target while shrinking, then mark the animation complete. */
s32 func_800AB538(void *animation_data, void *motion_data, void *scale_data, void *render_data)
{
    u8 *animation = animation_data;
    u8 *motion = motion_data;

    register u8 *scale ASM_REG("$19") = scale_data;
    register u8 *render ASM_REG("$18") = render_data;
    s32 move_frames;
    s16 frames_left;
    s32 height_offset;
    u16 scale_value;
    s32 state;
    s32 next_state;

    state = ((S_800AB538_0 *)animation)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    return 0;

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    return 0;

state_0:
    ((S_800AB538_0 *)animation)->unk_96.s = 0x10;
    ((S_800AB538_1 *)render)->unk_1C &= 0xFFFBFFFF;
    (*(u16 *)((u8 *)animation + 0x98)) |= 8;
    if (D_80013714 & 2) {
        ((S_800AB538_0 *)animation)->unk_9B = 2;
        goto return_zero;
    }
    ((S_800AB538_1 *)render)->unk_8A = 0x800 / ((S_800AB538_0 *)animation)->unk_96.s;
    next_state = ((S_800AB538_0 *)animation)->unk_9B + 1;
    goto increment_state;

state_1:
    move_frames = ((S_800AB538_0 *)animation)->unk_96.s - 2;
    if (move_frames > 0) {
        u8 *target = D_80083780;

        (*(s32 *)((u8 *)motion + 0xC)) =
            ((((S_800AB538_2 *)target)->unk_02.s - ((S_800AB538_3 *)motion)->unk_02) << 16) / move_frames;
        ((S_800AB538_3 *)motion)->unk_10 =
            ((((S_800AB538_2 *)target)->unk_06.s - ((S_800AB538_3 *)motion)->unk_06.s) << 16) /
            (((S_800AB538_0 *)animation)->unk_96.s - 2);
    } else {
        u8 *target = D_80083780;

        (*(s32 *)((u8 *)motion + 0x10)) = 0;
        (*(s32 *)((u8 *)motion + 0xC)) = 0;
        (*(u16 *)((u8 *)motion + 2)) = ((S_800AB538_2 *)target)->unk_02.u;
        ((S_800AB538_3 *)motion)->unk_06.u = ((S_800AB538_2 *)target)->unk_06.u;
    }

    frames_left = ((S_800AB538_0 *)animation)->unk_96.s;
    if (frames_left != 0) {
        height_offset = func_800644B8(frames_left << 6);
        {
            s16 *target_height = &D_8008378A;

            height_offset >>= 4;
            ((S_800AB538_3 *)motion)->unk_14 =
                ((*target_height - height_offset - ((S_800AB538_3 *)motion)->unk_0A.s) << 16) /
                ((S_800AB538_0 *)animation)->unk_96.s;
        }
    }

    scale_value = ((S_800AB538_4 *)scale)->unk_1C - ((S_800AB538_1 *)render)->unk_8A;
    ((S_800AB538_4 *)scale)->unk_1C = scale_value;
    ((S_800AB538_4 *)scale)->unk_1E = scale_value;

    frames_left = ((S_800AB538_0 *)animation)->unk_96.u - 1;
    ((S_800AB538_0 *)animation)->unk_96.s = frames_left;
    if (frames_left < 0) {
        (*(s32 *)((u8 *)motion + 0x14)) = 0;
        ((S_800AB538_1 *)render)->unk_88 = (u16)D_8008378A;
        ((S_800AB538_3 *)motion)->unk_0A.u = (u16)D_8008378A;
        ((S_800AB538_0 *)animation)->unk_92 = 0;
        next_state = ((S_800AB538_0 *)animation)->unk_9B + 1;
increment_state:
        ((S_800AB538_0 *)animation)->unk_9B = next_state;
        goto return_zero;
    }
    goto return_zero;

state_2:
    ((S_800AB538_4 *)scale)->unk_1E = 0;
    ((S_800AB538_4 *)scale)->unk_1C = 0;

    {
        s32 flags = ((S_800AB538_1 *)render)->unk_1C;

        flags |= 0x800000;
        ((S_800AB538_1 *)render)->unk_1C = flags;
    }
return_zero:
    return 0;
}

#include "common.h"

typedef struct S_800B80D8_0 {
    u8 pad_00[0xA2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u16 unk_A4;
    u8 pad_A6[0xA];
    s16 unk_B0;
    s16 unk_B2;
} S_800B80D8_0;   /* arg0 in func_800B80D8 */

typedef struct S_800B80D8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800B80D8_1;   /* arg2 in func_800B80D8 */

typedef struct S_800B80D8_2 {
    u8 pad_00[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B80D8_2;   /* arg1 in func_800B80D8 */



extern void func_800A7A7C(s32, s32, s32, void *, void *);
extern s32 D_8006E240;
extern s32 D_800814A0;

/* Animate object motion and scale, then signal completion. */
void func_800B80D8(void *object, void *motion, void *display)
{
    s16 state;
    s32 velocity;
    u16 frames_left;
    u16 scale;

    state = ((S_800B80D8_0 *)object)->unk_A2.s;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto exit;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto exit;

state_zero:
    if (!(((S_800B80D8_1 *)display)->unk_14 & 0x8000)) {
        goto zero_continue;
    }
    ((S_800B80D8_0 *)object)->unk_A2.u = 2;
    goto exit;

zero_continue:
    ((S_800B80D8_0 *)object)->unk_A4 = 12;
    ((S_800B80D8_0 *)object)->unk_A2.u++;
state_one:
    velocity = ((S_800B80D8_2 *)motion)->unk_14 + 0x30000;
    ((S_800B80D8_2 *)motion)->unk_14 = velocity;
    ((S_800B80D8_2 *)motion)->unk_08.at00.v += velocity;
    scale = ((S_800B80D8_1 *)display)->unk_1C;
    if (scale < 0x1000) {
        ((S_800B80D8_1 *)display)->unk_1C = scale + 0x50;
        ((S_800B80D8_1 *)display)->unk_1E += 0x50;
    }
    frames_left = ((S_800B80D8_0 *)object)->unk_A4 - 1;
    ((S_800B80D8_0 *)object)->unk_A4 = frames_left;
    if ((frames_left << 16) != 0) {
        goto exit;
    }
    ((S_800B80D8_2 *)motion)->unk_14 = 0;
    ((S_800B80D8_0 *)object)->unk_A2.u++;
    goto exit;

state_two:
    func_800A7A7C(((S_800B80D8_0 *)object)->unk_B0,
                  ((S_800B80D8_0 *)object)->unk_B2,
                  (s16)(((S_800B80D8_2 *)motion)->unk_08.at02.v - 0x20),
                  &D_8006E240,
                  (u8 *)object + 0x98);
    (*(u16 *)((u8 *)object + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

exit:
    return;
}

#include "common.h"

typedef struct S_80174978_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    s16 unk_A8;
    s16 unk_AA;
} S_80174978_0;   /* arg0 in func_80174978 */

typedef struct S_80174978_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80174978_1;   /* arg2 in func_80174978 */

typedef struct S_80174978_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_80174978_2;   /* arg1 in func_80174978 */



extern void func_800A7A7C(s16, s16, s16, s32, void *);
extern s32 D_800814A0;

/* Updates a timed movement animation and marks its completion. */
void func_80174978(void *actor, void *motion, void *visual) {
    s32 state;
    s32 z_step;
    s32 speed_or_z;
    register s32 next_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u16 timer;
    u16 next_scale;

    state = ((S_80174978_0 *)actor)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (((S_80174978_1 *)visual)->unk_14 & 0x8000) {
        ((S_80174978_0 *)actor)->unk_9B = 2;
        goto done;
    }
    ((S_80174978_0 *)actor)->unk_96 = 12;
    ((S_80174978_0 *)actor)->unk_9B = ((S_80174978_0 *)actor)->unk_9B + 1;

state_one: {
    s32 target_x;
    s32 current_x;

    target_x = ((S_80174978_0 *)actor)->unk_A8 << 6;
    current_x = ((S_80174978_2 *)motion)->unk_02 - 0x20;
    ((S_80174978_2 *)motion)->unk_02 = (u16)((S_80174978_2 *)motion)->unk_02 +
        ((target_x - current_x) >> 1);
}
    z_step = ((S_80174978_0 *)actor)->unk_AA;
    speed_or_z = ((S_80174978_2 *)motion)->unk_14 + 0x30000;
    next_height = ((S_80174978_2 *)motion)->unk_08.at00.v + speed_or_z;
    ((S_80174978_2 *)motion)->unk_14 = speed_or_z;
    speed_or_z = ((S_80174978_2 *)motion)->unk_06;
    z_step <<= 6;
    ((S_80174978_2 *)motion)->unk_08.at00.v = next_height;
    speed_or_z -= 0x20;
    z_step -= speed_or_z;
    z_step >>= 1;
    ((S_80174978_2 *)motion)->unk_06 = (u16)((S_80174978_2 *)motion)->unk_06 + z_step;
    if (((S_80174978_1 *)visual)->unk_1C < 0x1000U) {
        next_scale = ((S_80174978_1 *)visual)->unk_1E + 0x50;
        ((S_80174978_1 *)visual)->unk_1E = next_scale;
        ((S_80174978_1 *)visual)->unk_1C = next_scale;
    }
    timer = ((S_80174978_0 *)actor)->unk_96 - 1;
    ((S_80174978_0 *)actor)->unk_96 = timer;
    if ((timer << 16) != 0) {
        goto done;
    }
    ((S_80174978_2 *)motion)->unk_14 = 0;
    ((S_80174978_0 *)actor)->unk_9B = ((S_80174978_0 *)actor)->unk_9B + 1;
    goto done;

state_two:
    func_800A7A7C(((S_80174978_0 *)actor)->unk_A8,
                  ((S_80174978_0 *)actor)->unk_AA,
                  (s16)(((S_80174978_2 *)motion)->unk_08.at02.v - 0x20),
                  ((S_80174978_1 *)visual)->unk_08, actor + 0x48);
    (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

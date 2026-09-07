#include "common.h"

typedef struct S_80172C98_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x12];
    union { s16 s; u16 u; } unk_AE;   /* accessed as both */
} S_80172C98_0;   /* arg0 in func_80172C98 */

typedef struct S_80172C98_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172C98_1;   /* arg1 in func_80172C98 */

typedef struct S_80172C98_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172C98_2;   /* arg3 in func_80172C98 */

typedef struct S_80172C98_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172C98_3;   /* arg2 in func_80172C98 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_801752EC(void *, void *, void *);
extern void func_801755A8(void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80171094[];
extern u8 D_80176488[];

/* Updates a timed backward-then-forward movement sequence and handles animation completion. */
void func_80172C98(void *action, void *motion, void *animation, void *actor)
{
    u16 timer;
    s32 state;

    state = ((S_80172C98_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    return;

state_zero:
    ((S_80172C98_0 *)action)->unk_AE.s = 6;
    ((S_80172C98_1 *)motion)->unk_0C =
        -(((func_80064584(((S_80172C98_2 *)actor)->unk_2A) >> 4) << 13) /
          ((S_80172C98_0 *)action)->unk_AE.s);
    ((S_80172C98_1 *)motion)->unk_10 =
        -(((func_800644B8(((S_80172C98_2 *)actor)->unk_2A) >> 4) << 13) /
          ((S_80172C98_0 *)action)->unk_AE.s);
    ((S_80172C98_0 *)action)->unk_9B++;

state_one:
    if (((S_80172C98_3 *)animation)->unk_14 & 0x8000) {
        ((S_80172C98_0 *)action)->unk_9B = 3;
        ((S_80172C98_1 *)motion)->unk_0C =
            ((S_80172C98_1 *)motion)->unk_10 =
                ((S_80172C98_1 *)motion)->unk_14 = 0;
        ((S_80172C98_3 *)animation)->unk_14 |= 0x6000;
        func_8009C12C(actor, animation, ((S_80172C98_2 *)actor)->unk_2A, 1);
        return;
    }

    timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
    ((S_80172C98_0 *)action)->unk_AE.u = timer;
    if ((s16)timer < 0) {
        ((S_80172C98_1 *)motion)->unk_0C =
            ((S_80172C98_1 *)motion)->unk_10 =
                ((S_80172C98_1 *)motion)->unk_14 = 0;
    }

    if (((S_80172C98_3 *)animation)->unk_14 & 0x6000) {
        u8 *direction_anims = D_80176488;

        (*(u8 * *)((u8 *)animation + 0x2C)) = direction_anims;
        func_80047784(
            animation,
            direction_anims[((D_80083228 + ((S_80172C98_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172C98_0 *)action)->unk_AE.s = 6;
        ((S_80172C98_1 *)motion)->unk_0C =
            ((func_80064584(((S_80172C98_2 *)actor)->unk_2A) >> 4) << 14) /
            ((S_80172C98_0 *)action)->unk_AE.s;
        ((S_80172C98_1 *)motion)->unk_10 =
            ((func_800644B8(((S_80172C98_2 *)actor)->unk_2A) >> 4) << 14) /
            ((S_80172C98_0 *)action)->unk_AE.s;
        ((S_80172C98_0 *)action)->unk_AE.u--;
        func_801752EC(action, motion, animation);
        func_801755A8(action, motion, animation);
        func_800A56E0(0x80E);
        ((S_80172C98_0 *)action)->unk_9B++;
        ((S_80172C98_0 *)action)->unk_96 = 0;
    }
    return;

state_two:
    timer = ((S_80172C98_0 *)action)->unk_AE.u - 1;
    ((S_80172C98_0 *)action)->unk_AE.u = timer;
    if ((s16)timer < 0) {
        ((S_80172C98_1 *)motion)->unk_0C =
            ((S_80172C98_1 *)motion)->unk_10 =
                ((S_80172C98_1 *)motion)->unk_14 = 0;
    }

    timer = ((S_80172C98_0 *)action)->unk_96 + 1;
    ((S_80172C98_0 *)action)->unk_96 = timer;
    if (((s16)timer == 5) || (((S_80172C98_3 *)animation)->unk_14 & 0x8000)) {
        func_8009C12C(actor, animation, ((S_80172C98_2 *)actor)->unk_2A, 1);
        func_800A56E0(0x808);
    }

state_three:
    if (((S_80172C98_3 *)animation)->unk_14 & 0xE000) {
        func_800AD594(actor, 0x100);
        func_800A2B04(motion, ((S_80172C98_3 *)animation)->unk_24, ((S_80172C98_3 *)animation)->unk_25);
        ((S_80172C98_1 *)motion)->unk_0C =
            ((S_80172C98_1 *)motion)->unk_10 =
                ((S_80172C98_1 *)motion)->unk_14 = 0;
        ((S_80172C98_0 *)action)->unk_8C = D_80171094;
        D_8008346C = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        func_800A4ACC(actor);
    }
}

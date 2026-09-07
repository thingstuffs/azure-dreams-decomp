#include "common.h"

typedef struct S_801724E8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801724E8_0;   /* arg0 in func_801724E8 */

typedef struct S_801724E8_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801724E8_1;   /* arg2 in func_801724E8 */

typedef struct S_801724E8_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801724E8_2;   /* arg3 in func_801724E8 */

typedef struct S_801724E8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801724E8_3;   /* arg1 in func_801724E8 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80174520[];

void func_801724E8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s32 timer;
    s16 next_timer;
    u16 countdown;
    s32 state;
    s32 flags;
    s32 delta;
    s16 *global;
    u8 *map;

    state = ((S_801724E8_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto update_countdown;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }
    goto update_countdown;

state_zero:
    if (((((S_801724E8_1 *)arg2)->unk_04 == 2) &&
         (((S_801724E8_1 *)arg2)->unk_14 & 0x1000)) ||
        (((S_801724E8_1 *)arg2)->unk_14 & 0xE000)) {
        ((S_801724E8_0 *)arg0)->unk_98 |= 8;
        ((S_801724E8_2 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
        ((S_801724E8_0 *)arg0)->unk_9E.s = 5;
        ((S_801724E8_0 *)arg0)->unk_A0 = 0;
        ((S_801724E8_0 *)arg0)->unk_9B++;
        goto state_one;
    }
    goto update_countdown;

state_one:
    timer = ((S_801724E8_0 *)arg0)->unk_9E.s;
    ((S_801724E8_0 *)arg0)->unk_90 -= ((S_801724E8_0 *)arg0)->unk_A0;
    if (timer != 0) {
        ((S_801724E8_3 *)arg1)->unk_0C =
            (((((S_801724E8_1 *)arg2)->unk_24 << 6) - ({ ((S_801724E8_3 *)arg1)->unk_02 - 0x20; })) << 16) / timer;
        ((S_801724E8_3 *)arg1)->unk_10 =
            (((((S_801724E8_1 *)arg2)->unk_25 << 6) - (delta = ((S_801724E8_3 *)arg1)->unk_06 - 0x20)) << 16) /
            ((S_801724E8_0 *)arg0)->unk_9E.s;
        ((S_801724E8_0 *)arg0)->unk_A0 =
            (-func_800644B8(((S_801724E8_0 *)arg0)->unk_9E.s * 0x199)) << 9;
    }

    ((S_801724E8_0 *)arg0)->unk_90 += ((S_801724E8_0 *)arg0)->unk_A0;
    next_timer = ((S_801724E8_0 *)arg0)->unk_9E.u - 1;
    ((S_801724E8_0 *)arg0)->unk_9E.s = next_timer;
    if (next_timer < 0) {
        ((S_801724E8_0 *)arg0)->unk_90 = 0;
        ((S_801724E8_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801724E8_2 *)arg3)->unk_1C.s |= 0x08000000;
        ((S_801724E8_0 *)arg0)->unk_9B++;
    }

state_two:
    if (((S_801724E8_2 *)arg3)->unk_1C.s & 0x08000000) {
        ((S_801724E8_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801724E8_3 *)arg1)->unk_14 = 0;
        ((S_801724E8_3 *)arg1)->unk_10 = 0;
        ((S_801724E8_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801724E8_1 *)arg2)->unk_24, ((S_801724E8_1 *)arg2)->unk_25);
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174520;
        func_80047784(
            arg2,
            D_80174520[((D_80083228 + ((S_801724E8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801724E8_0 *)arg0)->unk_9B++;
    }

update_countdown:
    countdown = ((S_801724E8_0 *)arg0)->unk_96 - 1;
    ((S_801724E8_0 *)arg0)->unk_96 = countdown;
    if ((s16)countdown <= 0) {
        ((S_801724E8_3 *)arg1)->unk_14 = 0;
        ((S_801724E8_3 *)arg1)->unk_10 = 0;
        ((S_801724E8_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801724E8_1 *)arg2)->unk_24, ((S_801724E8_1 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        global = (s16 *)&D_80083460;
        if (global[4] != 0) {
            global[4]--;
        }

        flags = ((S_801724E8_2 *)arg3)->unk_1C.u;
        if (flags & 0x2000) {
            if (((S_801724E8_2 *)arg3)->unk_46 & 0x8000) {
                ((S_801724E8_2 *)arg3)->unk_46 &= 0x7FFF;
            }
        } else {
            if (flags & 0x410) {
                goto check_collision;
            }
            if (!(flags & 0x20000)) {
                goto check_collision;
            }
            map = D_80082E80;
            ((S_801724E8_2 *)arg3)->unk_2A = func_800A0818(
                ((S_801724E8_1 *)arg2)->unk_24, ((S_801724E8_1 *)arg2)->unk_25,
                map[0x24], map[0x25], &scratch);
        }

check_collision:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_801724E8_0 *)arg0)->unk_8C = D_80170E5C;
            func_800A9A04(arg3);
        }
    }
}

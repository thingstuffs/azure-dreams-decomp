#include "common.h"

typedef struct S_80172AD8_0 {
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
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80172AD8_0;   /* arg0 in func_80172AD8 */

typedef struct S_80172AD8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80172AD8_1;   /* arg2 in func_80172AD8 */

typedef struct S_80172AD8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172AD8_2;   /* arg3 in func_80172AD8 */

typedef struct S_80172AD8_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172AD8_3;   /* arg1 in func_80172AD8 */

typedef struct S_80172AD8_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172AD8_4;   /* global_base in func_80172AD8 */

typedef struct S_80172AD8_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172AD8_5;   /* map_base in func_80172AD8 */



extern void func_80047784(void *, s16, s16);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801714B8;
extern u8 D_801760BC;
extern u8 D_801760C4;

void func_80172AD8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s32 state;
    s32 remaining;
    s32 tile;
    s32 current;
    s32 sum;
    s32 velocity;
    s32 counter;
    s32 timer;
    s32 flags;
    u8 *global_base;
    u8 *map_base;

    state = ((S_80172AD8_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
    if (!(((S_80172AD8_1 *)arg2)->unk_14 & 0x6000)) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = &D_801760BC;
    func_80047784(
        arg2,
        *(&D_801760BC +
          (((D_80083228 + ((S_80172AD8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7)),
        0);
    ((S_80172AD8_0 *)arg0)->unk_98 |= 8;
    ((S_80172AD8_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_80172AD8_0 *)arg0)->unk_9E.s = 5;
    ((S_80172AD8_0 *)arg0)->unk_A4 = 0;
    ((S_80172AD8_0 *)arg0)->unk_9B++;

state_one:
    ((S_80172AD8_0 *)arg0)->unk_90 -= ((S_80172AD8_0 *)arg0)->unk_A4;
    ((S_80172AD8_1 *)arg2)->unk_1C = 0xC00;
    ((S_80172AD8_1 *)arg2)->unk_1E = 0x1400;
    remaining = ((S_80172AD8_0 *)arg0)->unk_9E.s;
    if (remaining != 0) {
        tile = ((S_80172AD8_1 *)arg2)->unk_24;
        current = ((S_80172AD8_3 *)arg1)->unk_02;
        tile <<= 6;
        current -= 0x20;
        ((S_80172AD8_3 *)arg1)->unk_0C = ((tile - current) << 16) / remaining;

        current = ((S_80172AD8_3 *)arg1)->unk_06 - 0x20;
        ((S_80172AD8_3 *)arg1)->unk_10 =
            (((((S_80172AD8_1 *)arg2)->unk_25 << 6) - current) << 16) /
            ((S_80172AD8_0 *)arg0)->unk_9E.s;
        ((S_80172AD8_0 *)arg0)->unk_A4 =
            (-func_800644B8(((S_80172AD8_0 *)arg0)->unk_9E.s * 0x199)) << 9;
    }

    sum = ((S_80172AD8_0 *)arg0)->unk_90;
    velocity = ((S_80172AD8_0 *)arg0)->unk_A4;
    counter = ((S_80172AD8_0 *)arg0)->unk_9E.u;
    sum += velocity;
    counter -= 1;
    ((S_80172AD8_0 *)arg0)->unk_9E.u = counter;
    ((S_80172AD8_0 *)arg0)->unk_90 = sum;
    if ((counter << 16) >= 0) {
        goto state_two;
    }

    ((S_80172AD8_0 *)arg0)->unk_90 = 0;
    ((S_80172AD8_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_80172AD8_2 *)arg3)->unk_1C |= 0x08000000;
    ((S_80172AD8_0 *)arg0)->unk_9B++;

state_two:
    if (((S_80172AD8_2 *)arg3)->unk_1C & 0x08000000) {
        ((S_80172AD8_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172AD8_3 *)arg1)->unk_14 = 0;
        ((S_80172AD8_3 *)arg1)->unk_10 = 0;
        ((S_80172AD8_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80172AD8_1 *)arg2)->unk_24, ((S_80172AD8_1 *)arg2)->unk_25);
        ((S_80172AD8_1 *)arg2)->unk_1C = 0x1400;
        ((S_80172AD8_1 *)arg2)->unk_1E = 0xC00;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = &D_801760C4;
        func_80047784(
            arg2,
            *(&D_801760C4 +
              (((D_80083228 + ((S_80172AD8_2 *)arg3)->unk_2A + 0x100) >> 9) & 7)),
            0);
        ((S_80172AD8_0 *)arg0)->unk_9B++;
        goto decrement_timer;
    }
    goto decrement_timer;

state_three:
    ((S_80172AD8_1 *)arg2)->unk_1C = 0x1000;
    ((S_80172AD8_1 *)arg2)->unk_1E = 0x1000;

decrement_timer:
    timer = ((S_80172AD8_0 *)arg0)->unk_96 - 1;
    ((S_80172AD8_0 *)arg0)->unk_96 = timer;
    if ((timer << 16) > 0) {
        return;
    }

    ((S_80172AD8_3 *)arg1)->unk_14 = 0;
    ((S_80172AD8_3 *)arg1)->unk_10 = 0;
    ((S_80172AD8_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172AD8_1 *)arg2)->unk_24, ((S_80172AD8_1 *)arg2)->unk_25);
    ((S_80172AD8_1 *)arg2)->unk_1C = 0x1000;
    ((S_80172AD8_1 *)arg2)->unk_1E = 0x1000;
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global_base = (u8 *)&D_80083460;
    if (((S_80172AD8_4 *)global_base)->unk_08.s != 0) {
        ((S_80172AD8_4 *)global_base)->unk_08.u--;
    }

    flags = ((S_80172AD8_2 *)arg3)->unk_1C;
    if (flags & 0x2000) {
        if (((S_80172AD8_2 *)arg3)->unk_46 & 0x8000) {
            ((S_80172AD8_2 *)arg3)->unk_46 &= 0x7FFF;
        }
        goto collision_check;
    }
    if (flags & 0x410) {
        goto collision_check;
    }
    if (!(flags & 0x20000)) {
        goto collision_check;
    }
    map_base = D_80082E80;
    ((S_80172AD8_2 *)arg3)->unk_2A = func_800A0818(
        ((S_80172AD8_1 *)arg2)->unk_24, ((S_80172AD8_1 *)arg2)->unk_25,
        ((S_80172AD8_5 *)map_base)->unk_24, ((S_80172AD8_5 *)map_base)->unk_25, &sp18);

collision_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        ((S_80172AD8_0 *)arg0)->unk_8C = &D_801714B8;
        func_800A9A04(arg3);
    }
}

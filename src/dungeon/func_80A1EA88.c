#include "common.h"

typedef struct S_80172288_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172288_0;   /* arg0 in func_80172288 */

typedef struct S_80172288_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172288_1;   /* arg1 in func_80172288 */

typedef struct S_80172288_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172288_2;   /* arg3 in func_80172288 */

typedef struct S_80172288_3 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172288_3;   /* counter in func_80172288 */

typedef struct S_80172288_4 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80172288_4;   /* arg2 in func_80172288 */



typedef struct {
    u16 x;
    u16 y;
} PathPoint;

typedef struct {
    PathPoint point[8];
} PathTable;

extern void func_80047784(void *, u8, s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170838[16];
extern s32 D_80170E84;
extern u8 D_80174820[];

void func_80172288(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3)
{
    PathTable path;
    s32 result;
    s32 duration;
    s32 coordinate;
    s16 timer;
    s32 flags;
    s32 state;
    u8 counter_value;
    u8 *counter;

    path = *(PathTable *)D_80170838;
    state = ((S_80172288_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement;
    }
    if (state == 2) {
        goto state_two;
    }
    goto decrement;

state_zero:
    if (((S_80172288_0 *)arg0)->unk_96 < 8) {
        ((S_80172288_0 *)arg0)->unk_98 |= 8;
        ((S_80172288_1 *)arg1)->unk_14 = 0xFFEE0000;
        ((S_80172288_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
        counter_value = *(volatile u8 *)(arg0 + 0x9B);
        ((S_80172288_0 *)arg0)->unk_A0 = 0;
        goto increment_state;
    }
    goto decrement;

state_one:
    duration = ((S_80172288_0 *)arg0)->unk_96;
    ((S_80172288_0 *)arg0)->unk_90 -= ((S_80172288_0 *)arg0)->unk_A0;
    if (duration != 0) {
        {
            s32 pixel;
            s32 origin;

            pixel = arg2[0x24];
            origin = ((S_80172288_1 *)arg1)->unk_02;
            pixel <<= 6;
            origin -= 0x20;
            ((S_80172288_1 *)arg1)->unk_0C =
                ((pixel - origin) << 16) / duration;
        }
        coordinate = ((S_80172288_1 *)arg1)->unk_06 - 0x20;
        ((S_80172288_1 *)arg1)->unk_10 =
            (((arg2[0x25] << 6) - coordinate) << 16) /
            ((S_80172288_0 *)arg0)->unk_96;
        ((S_80172288_0 *)arg0)->unk_A0 += ((S_80172288_1 *)arg1)->unk_14;
        ((S_80172288_1 *)arg1)->unk_14 += 0x40000;
    }
    ((S_80172288_0 *)arg0)->unk_90 += ((S_80172288_0 *)arg0)->unk_A0;
    if (((S_80172288_0 *)arg0)->unk_96 < 3) {
        ((S_80172288_0 *)arg0)->unk_90 = 0;
        ((S_80172288_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172288_2 *)arg3)->unk_1C |= 0x08000000;
        ((S_80172288_0 *)arg0)->unk_9B++;
    }

state_two:
    if (((S_80172288_2 *)arg3)->unk_1C & 0x08000000) {
        ((S_80172288_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172288_1 *)arg1)->unk_14 = 0;
        ((S_80172288_1 *)arg1)->unk_10 = 0;
        ((S_80172288_1 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, arg2[0x24], arg2[0x25]);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174820;
        func_80047784(
            arg2,
            D_80174820[((D_80083228 + ((S_80172288_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        counter_value = ((S_80172288_0 *)arg0)->unk_9B;
increment_state:
        ((S_80172288_0 *)arg0)->unk_9B = counter_value + 1;
    }

decrement:
    timer = ((S_80172288_0 *)arg0)->unk_96 - 1;
    ((S_80172288_0 *)arg0)->unk_96 = timer;
    if ((timer << 16) <= 0) {
        ((S_80172288_1 *)arg1)->unk_14 = 0;
        ((S_80172288_1 *)arg1)->unk_10 = 0;
        ((S_80172288_1 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, arg2[0x24], arg2[0x25]);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        counter = (u8 *)&D_80083460;
        if (((S_80172288_3 *)counter)->unk_08.s != 0) {
            ((S_80172288_3 *)counter)->unk_08.u--;
        }

        flags = ((S_80172288_2 *)arg3)->unk_1C;
        if (flags & 0x2000) {
            if (((S_80172288_2 *)arg3)->unk_46 & 0x8000) {
                ((S_80172288_2 *)arg3)->unk_46 &= 0x7FFF;
                goto update_actor;
            }
            goto update_actor;
        }
        if (flags & 0x410) {
            goto update_actor;
        }
        if (!(flags & 0x20000)) {
            goto update_actor;
        }
        ((S_80172288_2 *)arg3)->unk_2A = func_800A0818(
            arg2[0x24], arg2[0x25], D_80082E80[0x24], D_80082E80[0x25],
            &result);

update_actor:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_80172288_0 *)arg0)->unk_8C = &D_80170E84;
            func_800A9A04(arg3);
            goto update_position;
        }
    } else {
update_position:
        ((S_80172288_4 *)arg2)->unk_1C = path.point[((S_80172288_0 *)arg0)->unk_96].x;
        ((S_80172288_4 *)arg2)->unk_1E = path.point[((S_80172288_0 *)arg0)->unk_96].y;
    }
}

/* MECHANISM: The 32-byte PathTable copy fixes the 0x58 frame and stack slots.
   Block-scoped pixel/origin ranges force retail's lbu/lh/sll/addiu order.
   A dedicated u8 counter merges both predecessors at the load-delay nop. */

#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80172290_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
} S_80172290_0;   /* arg0 in func_80172290 */

typedef struct S_80172290_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172290_1;   /* arg2 in func_80172290 */

typedef struct S_80172290_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172290_2;   /* arg3 in func_80172290 */

typedef struct S_80172290_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172290_3;   /* arg1 in func_80172290 */


M2C_UNK func_80047784();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
M2C_UNK func_800AD594();
s32 func_800AD9B4();
void func_801724D0(void) __attribute__((noreturn));
void func_801725A8() __attribute__((noreturn));

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E70;
extern u8 D_80175A6C[];
extern u8 D_80175A74[];

void func_80172290(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 sp18;
    s32 temp_a0;
    s16 temp_v0;
    s32 flags;
    s32 state;

    state = ((S_80172290_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_801724D0();
    }
    if (state == 2) {
        goto state_2;
    }
    func_801724D0();

state_0:
    if (((S_80172290_1 *)arg2)->unk_14 & 0x6000) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175A6C;
        func_80047784(
            arg2,
            D_80175A6C[((D_80083228 + ((S_80172290_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172290_0 *)arg0)->unk_98 |= 8;
        ((S_80172290_3 *)arg1)->unk_14 = 0xFFF00000;
        ((S_80172290_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
        ((S_80172290_0 *)arg0)->unk_A0 = 0;
        ((S_80172290_0 *)arg0)->unk_9B++;
        goto state_1;
    }
    goto tick;

state_1:
    temp_a0 = ((S_80172290_0 *)arg0)->unk_96.s;
    ((S_80172290_0 *)arg0)->unk_90 -= ((S_80172290_0 *)arg0)->unk_A0;
    if (temp_a0 != 0) {
        {
            s32 coord = ((S_80172290_1 *)arg2)->unk_24 << 6;
            s32 current = ((S_80172290_3 *)arg1)->unk_02 - 0x20;

            ((S_80172290_3 *)arg1)->unk_0C = ((coord - current) << 16) / temp_a0;
        }
        {
            s32 coord = ((S_80172290_1 *)arg2)->unk_25 << 6;
            s32 current = ((S_80172290_3 *)arg1)->unk_06 - 0x20;

            ((S_80172290_3 *)arg1)->unk_10 = ((coord - current) << 16) /
                ((S_80172290_0 *)arg0)->unk_96.s;
        }
        ((S_80172290_0 *)arg0)->unk_A0 += ((S_80172290_3 *)arg1)->unk_14;
        ((S_80172290_3 *)arg1)->unk_14 += 0x40000;
    }
    ((S_80172290_0 *)arg0)->unk_90 += ((S_80172290_0 *)arg0)->unk_A0;
    if (((S_80172290_0 *)arg0)->unk_96.s < 0) {
        ((S_80172290_0 *)arg0)->unk_90 = 0;
        ((S_80172290_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172290_2 *)arg3)->unk_1C |= 0x08000000;
        ((S_80172290_0 *)arg0)->unk_9B++;
    }

state_2:
    if (((S_80172290_2 *)arg3)->unk_1C & 0x08000000) {
        ((S_80172290_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_80172290_3 *)arg1)->unk_14 = 0;
        ((S_80172290_3 *)arg1)->unk_10 = 0;
        ((S_80172290_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80172290_1 *)arg2)->unk_24, ((S_80172290_1 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175A74;
        func_80047784(
            arg2,
            D_80175A74[((D_80083228 + ((S_80172290_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80172290_0 *)arg0)->unk_9B++;
    }

tick:
    temp_v0 = ((S_80172290_0 *)arg0)->unk_96.u - 1;
    ((S_80172290_0 *)arg0)->unk_96.s = temp_v0;
    if ((temp_v0 << 16) <= 0) {
        ((S_80172290_3 *)arg1)->unk_14 = 0;
        ((S_80172290_3 *)arg1)->unk_10 = 0;
        ((S_80172290_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80172290_1 *)arg2)->unk_24, ((S_80172290_1 *)arg2)->unk_25);
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        {
            u32 value;
            s16 *global;
            s32 test;

            global = (s16 *)&D_80083460;
            test = global[4];
            value = ((u16 *)global)[4];

            if (test != 0) {
                global[4] = value - 1;
            }
        }

        flags = ((S_80172290_2 *)arg3)->unk_1C;
        if (flags & 0x2000) {
            if (((S_80172290_2 *)arg3)->unk_46 & 0x8000) {
                ((S_80172290_2 *)arg3)->unk_46 &= 0x7FFF;
                func_801725A8(&D_80083460);
            }
        } else if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                u8 *origin = D_80082E80;

                ((S_80172290_2 *)arg3)->unk_2A = func_800A0818(
                    ((S_80172290_1 *)arg2)->unk_24, ((S_80172290_1 *)arg2)->unk_25,
                    origin[0x24], origin[0x25], &sp18);
            }
        }

finish:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            ((S_80172290_0 *)arg0)->unk_8C = &D_80170E70;
            func_800A9A04(arg3);
        }
    }
}

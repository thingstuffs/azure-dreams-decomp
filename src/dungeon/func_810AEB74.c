#include "common.h"

typedef struct S_80172374_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
} S_80172374_0;   /* arg0 in func_80172374 */

typedef struct S_80172374_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172374_1;   /* arg1 in func_80172374 */

typedef struct S_80172374_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172374_2;   /* arg3 in func_80172374 */

typedef struct S_80172374_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172374_3;   /* arg2 in func_80172374 */

typedef struct S_80172374_4 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80172374_4;   /* global in func_80172374 */

typedef struct S_80172374_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172374_5;   /* map in func_80172374 */



extern s16 func_800A0818();
extern void func_800A2B04();
extern void func_800A4ACC();
extern void func_800A9A04();
extern void func_800AD594();
extern s32 func_800AD9B4();

extern u8 D_80082E80[];
extern s32 D_80083460;
extern u8 D_80170E54;

void func_80172374(S_80172374_0 *arg0, S_80172374_1 *arg1, S_80172374_3 *arg2, S_80172374_2 *arg3) {
    s32 sp18;
    s32 state;
    s32 duration;
    s16 next_duration;
    s32 flags;
    u8 *global;

    state = arg0->unk_9B;
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto decrement;
    }
    if (state == 2) {
        goto state2;
    }
    goto decrement;

state0:
    if (arg0->unk_96 != 8) {
        goto decrement;
    }
    arg0->unk_98 |= 8;
    arg1->unk_14 = 0xFFEE0000;
    arg3->unk_1C &= 0xF7FFFFFF;
    arg0->unk_A4 = 0;
    arg0->unk_9B++;

state1:
    duration = arg0->unk_96;
    arg0->unk_90 -= arg0->unk_A4;
    if (duration != 0) {
        register s32 coord ASM_REG("$2");   /* MATCH pin: retail delay-slot fill depends on it */
        s32 origin;

        coord = arg2->unk_24 << 6;
        origin = arg1->unk_02 - 0x20;
        coord = ((coord - origin) << 16) / duration;
        origin = arg1->unk_06 - 0x20;
        arg1->unk_0C = coord;
        coord = arg2->unk_25 << 6;
        arg1->unk_10 = ((coord - origin) << 16) / arg0->unk_96;
        arg0->unk_A4 += arg1->unk_14;
        arg1->unk_14 += 0x40000;
    }
    arg0->unk_90 += arg0->unk_A4;
    if (arg0->unk_96 < 3) {
        arg0->unk_90 = 0;
        arg0->unk_98 &= 0xFFF7;
        arg3->unk_1C |= 0x08000000;
        arg0->unk_9B++;
    }

state2:
    if (arg3->unk_1C & 0x08000000) {
        arg0->unk_98 &= 0xFFF7;
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        arg0->unk_9B++;
    }

decrement:
    next_duration = (u16)arg0->unk_96 - 1;
    arg0->unk_96 = next_duration;
    if ((next_duration << 16) <= 0) {
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        func_800AD594(arg3, 5);
        func_800A4ACC(arg3);

        global = (u8 *)&D_80083460;
        if (((S_80172374_4 *)global)->unk_08 != 0) {
            ((S_80172374_4 *)global)->unk_08 = (u16)((S_80172374_4 *)global)->unk_08 - 1;
        }

        flags = arg3->unk_1C;
        if (flags & 0x2000) {
            if (arg3->unk_46 & 0x8000) {
                arg3->unk_46 &= 0x7FFF;
            }
            goto call_update;
        }
        if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                u8 *map = D_80082E80;

                arg3->unk_2A = func_800A0818(
                    arg2->unk_24, arg2->unk_25,
                    ((S_80172374_5 *)map)->unk_24, ((S_80172374_5 *)map)->unk_25, &sp18);
            }
        }

call_update:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            arg0->unk_8C = &D_80170E54;
            func_800A9A04(arg3);
        }
    }
}

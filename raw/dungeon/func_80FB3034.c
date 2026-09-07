#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef s32 M2C_UNK;

M2C_UNK func_80047784();
s16 func_800A0818();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A9A04();
M2C_UNK func_800AD594();
s32 func_800AD9B4();

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170F6C;
extern u8 D_80175278[];
extern u8 D_80175280[];

void func_80172834(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 sp18;
    s32 temp_a0;
    s16 temp_v0;
    s32 flags;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_2;
    }
    goto tick;

state_0:
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, u8 *, 0x2C) = D_80175278;
        func_80047784(
            arg2,
            D_80175278[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg1, s32, 0x14) = 0xFFEE0000;
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B)++;
        goto state_1;
    }
    goto tick;

state_1:
    temp_a0 = FIELD(arg0, s16, 0x96);
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
    if (temp_a0 != 0) {
        {
            s32 coord = FIELD(arg2, u8, 0x24) << 6;
            s32 current = FIELD(arg1, s16, 2) - 0x20;

            FIELD(arg1, s32, 0xC) = ((coord - current) << 16) / temp_a0;
        }
        {
            s32 coord = FIELD(arg2, u8, 0x25) << 6;
            s32 current = FIELD(arg1, s16, 6) - 0x20;

            FIELD(arg1, s32, 0x10) = ((coord - current) << 16) /
                FIELD(arg0, s16, 0x96);
        }
        FIELD(arg0, s32, 0xA0) += FIELD(arg1, s32, 0x14);
        FIELD(arg1, s32, 0x14) += 0x40000;
    }
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
    if (FIELD(arg0, s16, 0x96) < 2) {
        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

state_2:
    if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg2, u8 *, 0x2C) = D_80175280;
        func_80047784(
            arg2,
            D_80175280[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B)++;
    }

tick:
    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, s16, 0x96) = temp_v0;
    if ((temp_v0 << 16) <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        {
            void *global = &D_80083460;

            if (FIELD(global, s16, 8) != 0) {
                FIELD(global, s16, 8)--;
            }
        }

        flags = FIELD(arg3, u32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
        } else if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                u8 *global = D_80082E80;

                FIELD(arg3, s16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    global[0x24], global[0x25], &sp18);
            }
        }

finish:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, u8 *, 0x8C) = &D_80170F6C;
            func_800A9A04(arg3);
        }
    }
}

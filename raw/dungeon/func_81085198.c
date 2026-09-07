#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef s32 M2C_UNK;

extern s32 func_800644B8(s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern M2C_UNK D_80170E94;

void func_80172998(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s32 state;
    u32 flags;

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, s16, 0xA4) = 7;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B)++;

    case 1:
        FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
        if (FIELD(arg0, s16, 0xA4) != 0) {
            {
                s32 coord = FIELD(arg2, u8, 0x24) << 6;
                s32 current = FIELD(arg1, s16, 2) - 32;

                FIELD(arg1, s32, 0xC) =
                    ((coord - current) << 16) / FIELD(arg0, s16, 0xA4);
            }
            {
                s32 coord = FIELD(arg2, u8, 0x25) << 6;
                s32 current = FIELD(arg1, s16, 6) - 32;

                FIELD(arg1, s32, 0x10) =
                    ((coord - current) << 16) / FIELD(arg0, s16, 0xA4);
            }
            FIELD(arg0, s32, 0xA0) =
                (-func_800644B8(FIELD(arg0, s16, 0xA4) * 292)) << 9;
        }

        FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
        FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, s16, 0xA4)--;
        if (FIELD(arg0, s16, 0xA4) >= 0) {
            goto phase_two;
        }

        FIELD(arg0, s32, 0x90) = 0;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;

    case 2:
phase_two:
    if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg0, u8, 0x9B)++;
    }

    default:
        break;
    }

    FIELD(arg0, s16, 0x96)--;
    if (FIELD(arg0, s16, 0x96) > 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 5);
    func_800A4ACC(arg3);

    {
        s16 *counter = (s16 *)&D_80083460;

        if (counter[4] != 0) {
            ((u16 *)counter)[4]--;
        }
    }

    flags = FIELD(arg3, u32, 0x1C);
    if (flags & 0x2000) {
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
    } else {
        if (flags & 0x410) {
            goto actor_check;
        }
        if (!(flags & 0x20000)) {
            goto actor_check;
        }
        FIELD(arg3, s16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &scratch);
    }

actor_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        FIELD(arg0, M2C_UNK *, 0x8C) = &D_80170E94;
        func_800A9A04(arg3);
    }
}

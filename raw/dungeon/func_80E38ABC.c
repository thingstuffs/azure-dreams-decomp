#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, u8, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170EE4[];
extern u8 D_801765F0[];
extern u8 D_801765F8[];

void func_801722BC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 sp18;
    s16 count;
    u16 next;
    u8 state;
    s32 flags;
    s32 delta;
    s32 position;
    s32 *global;

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        next = FIELD(arg0, u16, 0x9E) - 1;
        FIELD(arg0, u16, 0x9E) = next;
        if ((s16)next > 0) {
            break;
        }

        FIELD(arg2, u8 *, 0x2C) = D_801765F0;
        func_80047784(
            arg2,
            D_801765F0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg3, s32, 0x1C) &= 0xF7FFFFFF;
        FIELD(arg0, u16, 0x9E) = 5;
        FIELD(arg0, s32, 0xA0) = 0;
        FIELD(arg0, u8, 0x9B)++;
        /* fallthrough */

    case 1:
        FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA0);
        count = FIELD(arg0, s16, 0x9E);
        if (count != 0) {
            delta = FIELD(arg2, u8, 0x24) << 6;
            position = FIELD(arg1, s16, 2);
            position -= 0x20;
            delta -= position;
            FIELD(arg1, s32, 0xC) = (delta << 16) / count;

            position = FIELD(arg1, s16, 6);
            delta = FIELD(arg2, u8, 0x25) << 6;
            position -= 0x20;
            delta -= position;
            FIELD(arg1, s32, 0x10) =
                (delta << 16) / FIELD(arg0, s16, 0x9E);
            FIELD(arg0, s32, 0xA0) =
                (-func_800644B8(FIELD(arg0, s16, 0x9E) * 0x199)) << 9;
        }

        FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA0);
        next = FIELD(arg0, u16, 0x9E) - 1;
        FIELD(arg0, u16, 0x9E) = next;
        if ((s16)next < 0) {
            FIELD(arg0, s32, 0x90) = 0;
            FIELD(arg0, u16, 0x98) &= 0xFFF7;
            FIELD(arg3, s32, 0x1C) |= 0x08000000;
            FIELD(arg0, u8, 0x9B)++;
        }
        /* fallthrough */

    case 2:
        if (FIELD(arg3, s32, 0x1C) & 0x08000000) {
            FIELD(arg0, u16, 0x98) &= 0xFFF7;
            FIELD(arg1, s32, 0x14) = 0;
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0xC) = 0;
            func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25));

            FIELD(arg2, u8 *, 0x2C) = D_801765F8;
            func_80047784(
                arg2,
                D_801765F8[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            FIELD(arg0, u8, 0x9B)++;
        }
        break;
    }

    next = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = next;
    if ((s16)next <= 0) {
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);

        global = &D_80083460;
        if (FIELD(global, s16, 8) != 0) {
            FIELD(global, u16, 8)--;
        }

        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
            }
        } else if (!(flags & 0x410)) {
            if (flags & 0x20000) {
                FIELD(arg3, s16, 0x2A) =
                    func_800A0818(FIELD(arg2, u8, 0x24),
                                   FIELD(arg2, u8, 0x25),
                                   D_80082E80[0x24], D_80082E80[0x25], &sp18);
            }
        }

        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, u8 *, 0x8C) = D_80170EE4;
            func_800A9A04(arg3);
        }
    }
}

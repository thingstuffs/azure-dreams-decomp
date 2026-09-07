#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, s32, s32);
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
extern u8 D_800E2348[];
extern u8 D_800E2368[];
extern u8 D_800E2370[];
extern s32 D_80171F1C;

void func_801733B4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s32 delta;
    u16 next;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto update_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto update_timer;

state_zero:
    next = FIELD(arg0, u16, 0xAA) + 1;
    FIELD(arg0, u16, 0xAA) = next;
    if ((s16)next < 2) {
        goto update_timer;
    }
    FIELD(arg2, u8 *, 0x2C) = D_800E2368;
    func_80047784(arg2,
        D_800E2368[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg3, u32, 0x1C) &= 0xF7FFFFFF;
    FIELD(arg0, u16, 0xAA) = 5;
    FIELD(arg0, s32, 0xA4) = 0;
    FIELD(arg0, u8, 0x9B)++;

state_one:
    FIELD(arg0, s32, 0x90) -= FIELD(arg0, s32, 0xA4);
    if (FIELD(arg0, s16, 0xAA) != 0) {
        FIELD(arg1, s32, 0xC) =
            (((FIELD(arg2, u8, 0x24) << 6) -
              ({ FIELD(arg1, s16, 2) - 0x20; })) << 16) /
            FIELD(arg0, s16, 0xAA);
        delta = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            (((FIELD(arg2, u8, 0x25) << 6) - delta) << 16) /
            FIELD(arg0, s16, 0xAA);
        FIELD(arg0, s32, 0xA4) =
            (-func_800644B8(FIELD(arg0, s16, 0xAA) * 0x199)) << 10;
    }
    FIELD(arg0, s32, 0x90) += FIELD(arg0, s32, 0xA4);
    next = FIELD(arg0, u16, 0xAA) - 1;
    FIELD(arg0, u16, 0xAA) = next;
    if ((s16)next < 0) {
        FIELD(arg0, s16, 0x92) = -0x10;
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg3, u32, 0x1C) |= 0x08000000;
        FIELD(arg0, u8, 0x9B)++;
    }

state_two:
    if (FIELD(arg3, u32, 0x1C) & 0x08000000) {
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        FIELD(arg2, u8 *, 0x2C) = D_800E2370;
        func_80047784(arg2,
            D_800E2370[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B)++;
        goto update_timer;
    }
    goto update_timer;

state_three:
    if (FIELD(arg2, u8 *, 0x2C) != D_800E2348) {
        FIELD(arg2, u8 *, 0x2C) = D_800E2348;
        func_80047784(arg2,
            D_800E2348[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, s16, 0x9E) = 0;
    }

update_timer:
    next = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = next;
    if (((s32)next << 16) <= 0) {
        s32 flags;
        s16 *counter;

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        func_800AD594(arg3, 4);
        func_800A4ACC(arg3);
        counter = (s16 *)&D_80083460;
        if (counter[4] != 0) {
            ((u16 *)counter)[4]--;
        }
        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x2000) {
            if (FIELD(arg3, u16, 0x46) & 0x8000) {
                FIELD(arg3, u16, 0x46) &= 0x7FFF;
                goto check_actor;
            }
        } else {
            if (flags & 0x410) {
                goto check_actor;
            }
            if (!(flags & 0x20000)) {
                goto check_actor;
            }
            FIELD(arg3, s16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                D_80082E80[0x24], D_80082E80[0x25], &scratch);
        }

check_actor:
        if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
            FIELD(arg0, s32 *, 0x8C) = &D_80171F1C;
            func_800A9A04(arg3);
        }
    }
}

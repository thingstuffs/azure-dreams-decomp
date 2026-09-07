#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80173AE4(void) __attribute__((noreturn));
extern void func_80173AE8(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2380[8];
extern u8 D_800E2388[8];
extern u8 D_80170838[16];
extern s32 D_80171F1C;

void func_801737F8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = FIELD(arg0, u8, 0x9B);
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 4;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        func_80173AE8();
    }
    if (FIELD(arg0, s16, 0x92) !=
        (s16)(func_800BCB04(FIELD(arg1, u16, 2),
                            FIELD(arg1, u16, 6),
                            (s16)(FIELD(arg3, u16, 0x88) - 0x20)) -
              FIELD(arg3, u16, 0x88))) {
        return;
    }
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, s16, 0x10) = 0x20;
    {
        u16 tail_flags;

        tail_flags = FIELD(arg2, u16, 0x14) | 0x000C;
        ASM_TAILSLOT_PIN(tail_flags);
        func_80173AE4();
    }

L1:
    FIELD(arg2, u8 *, 0x2C) = D_800E2380;
    func_80047784(arg2,
        D_800E2380[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    func_80173AE8();

L2:
    {
        s32 ten = 10;
        u16 timer = FIELD(arg0, u16, 0x96) + 1;

        FIELD(arg0, u16, 0x96) = timer;
        if ((s16)timer == ten || (FIELD(arg2, u16, 0x14) & 0x8000)) {
            func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
            FIELD(arg0, u16, 0x96) = ten;
            FIELD(arg0, u8, 0x9B)++;
            FIELD(arg2, u16, 0x14) |= 0x0800;
        }
        if (FIELD(arg0, s16, 0x96) == 9) {
            func_800A56E0(0x809);
            func_80173AE8();
        }
        return;
    }

L3:
    if (FIELD(arg0, s16, 0x96) > 0) {
        u16 timer = FIELD(arg0, u16, 0x96) - 1;

        FIELD(arg0, u16, 0x96) = timer;
        if ((timer << 16) != 0) {
            return;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, u16, 0x98) |= 8;
        FIELD(arg2, u8 *, 0x2C) = D_800E2388;
        func_80047784(arg2,
            D_800E2388[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        func_80173AE8();
    }

L4:
    if (FIELD(arg0, s16, 0x92) >= -0x1F) {
        FIELD(arg0, u16, 0x92) -= 4;
        func_80173AE8();
    }
    FIELD(arg0, u8, 0x9B)++;
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        return;
    }
    func_800AD594(arg3, 0x100);
    FIELD(arg0, s32 *, 0x8C) = &D_80171F1C;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    FIELD(arg3, u32, 0x1C) |= 0x40000;
    FIELD(arg0, u16, 0x98) |= 8;
    FIELD(arg2, u16, 0x14) &= 0xFFF3;
}

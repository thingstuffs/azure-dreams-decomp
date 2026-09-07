#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174520(void *, void *, void *, void *);
extern void func_80175060(void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171094[];
extern u8 D_80176470[];
extern u8 D_80176478[];

void func_80173DD4(void *arg0, void *in_arg1, void *in_arg2, void *arg3)
{
    register void *arg1 ASM_REG("$17");
    register void *arg2 ASM_REG("$18");
    s32 flags;
    u16 current_value;
    u16 old_value;
    u8 *global_base;
    s32 state;

    arg1 = in_arg1;
    arg2 = in_arg2;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto repeat_calls;
    }
    FIELD(arg2, void *, 0x2C) = D_80176470;
    func_80047784(arg2,
        D_80176470[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        FIELD(counter_base, u16, 0xA)--;
    }
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_one:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        global_base = (u8 *)&D_80083460;
        if (FIELD(global_base, u16, 2) & 0x1000) {
            goto done;
        }
        if (FIELD(arg3, s16, 0x64) != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, 0) != 0) {
                goto done;
            }
        }
        if (FIELD(arg3, u8, 0x25) == 0) {
            if (FIELD(global_base, u16, 2) & 0x2008) {
                goto done;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            goto done;
        }
        flags = FIELD(arg3, s32, 0x1C);
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto done;
        }
        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            current_value = FIELD(arg0, u16, 0x92);
            old_value = FIELD(arg0, u16, 0xA6);
            FIELD(arg0, u16, 0xA6) = 0;
            FIELD(arg0, s16, 0xAC) = 0;
            FIELD(arg0, u16, 0x92) = current_value - old_value;
            func_80174520(arg0, arg1, arg2, arg3);
            goto done;
        }
        if (FIELD(arg3, s8, 0x6D) == 0) {
            goto done;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(arg3,
                    (u8 *)FIELD(owner, void *, 0x58) + 0x20) << 16) != 0) {
                goto done;
            }
        }
        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *origin = D_80082E80;
            s8 tile = FIELD(arg2, s8, 0x26);

            if (((tile == FIELD(origin, s8, 0x26)) && (tile >= 0)) ||
                ((s16)func_8009FD40(origin, arg2) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(arg3, 1);
                }
            }
        }
        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto done;
        }
    }
    FIELD(arg2, void *, 0x2C) = D_80176478;
    func_80047784(arg2,
        D_80176478[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg3, u32, 0x1C) |= 0x40000;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        goto set_callback;
    }
    {
        u8 *counter_base = (u8 *)&D_80083460;

        FIELD(arg0, u8, 0x9B)++;
        FIELD(counter_base, u16, 0xA)++;
    }
    goto done;

state_two:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto repeat_calls;
    }
    {
        register u8 *counter_base ASM_REG("$2");

        counter_base = (u8 *)&D_80083460;
        FIELD(counter_base, u16, 0xA)--;
        ASM_KEEP(counter_base);
    }

set_callback:
    FIELD(arg0, void *, 0x8C) = D_80171094;
    goto done;

repeat_calls:
    func_80175060(arg0, arg1);
    func_80175060(arg0, arg1);
    func_80175060(arg0, arg1);
    func_80175060(arg0, arg1);

done:
    ASM_KEEP(arg1);
    ASM_KEEP(arg2);
    return;
}

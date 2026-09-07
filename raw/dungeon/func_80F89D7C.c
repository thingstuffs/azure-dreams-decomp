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
extern void func_80173D38(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174AFC[];
extern u8 D_80174B04[];

void func_8017357C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 flags;
    register s32 counter_value ASM_REG("$2");
    register u8 *counter_base ASM_REG("$3");
    u8 *global_base;
    s32 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
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
        goto done;
    }
    FIELD(arg2, void *, 0x2C) = D_80174AFC;
    func_80047784(arg2,
        D_80174AFC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    counter_base = (u8 *)&D_80083460;
    counter_value = FIELD(counter_base, u16, 0xA) - 1;
    goto store_counter;

state_one:
    if ((func_80042900(arg3, 1) << 16) == 0) {
        FIELD(arg2, void *, 0x2C) = D_80174B04;
        func_80047784(arg2,
            D_80174B04[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        flags = FIELD(arg3, s32, 0x1C) | 0x40000;
        FIELD(arg3, s32, 0x1C) = flags;
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg3, s32, 0x1C) = flags & ~0x200;
            goto set_callback;
        }
        goto increment_state;
    }
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
        FIELD(arg0, u16, 0xA0) = 0;
        func_80173D38(arg0, arg1, arg2, arg3);
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
    FIELD(arg2, void *, 0x2C) = D_80174B04;
    func_80047784(arg2,
        D_80174B04[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    flags = FIELD(arg3, s32, 0x1C) | 0x40000;
    FIELD(arg3, s32, 0x1C) = flags;
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg3, s32, 0x1C) = flags & ~0x200;
        goto set_callback;
    }

increment_state:
    counter_value = 3;
    ASM_KEEP(counter_value);
    counter_base = (u8 *)&D_80083460;
    FIELD(arg0, u16, 0x96) = counter_value;
    counter_value = FIELD(counter_base, u16, 0xA) + 1;

store_counter:
    FIELD(counter_base, u16, 0xA) = counter_value;
    ASM_KEEP(counter_base);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    FIELD(arg0, u16, 0x96)--;
    if (FIELD(arg0, s16, 0x96) <= 0) {
        FIELD(arg1, s32, 0x14) = 0xFFF00000;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, u16, 0xA0) = 0;
    FIELD(arg2, void *, 0x2C) = D_80174AD4;
    func_80047784(arg2,
        D_80174AD4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    {
        u8 *counter_base = (u8 *)&D_80083460;

        FIELD(counter_base, u16, 0xA)--;
    }
    FIELD(arg3, s32, 0x1C) &= ~0x200;

set_callback:
    FIELD(arg0, void *, 0x8C) = D_80171138;

done:
    return;
}

#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0;
extern s32 D_80083460;

void func_8009A028(void *);
void func_8009A3D0(s32, s32, s32);
void func_800A2FE0(void *);
void func_800A32A4(void *);
void func_800A56E0(s32);
void func_800ACF88(void *);

void func_80173450(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 flags;
    u16 count;
    s32 *global;
    s32 value;
    s32 x;
    s32 y;
    s32 mode;
    register s16 *page ASM_REG("$2");

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto process;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    page = (s16 *)0x80080000;
    if (state == 0) {
        goto state_zero;
    }
    goto end;

state_ge_2:
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto update;
    }
    goto end;

state_zero:
    ASM_KEEP(page);
    if (page[0x1A35] != 0) {
        goto end;
    }
    FIELD(arg0, u8, 0x9B) = 1;

process:
    flags = FIELD(arg3, s32, 0x14);
    if (flags & 0x4000) {
        if (!(flags & 0x20000000)) {
            func_800ACF88(arg3);
        }
    }
    func_800A56E0(0x805);
    FIELD(arg0, u16, 0x96) = 4;
    FIELD(arg0, u8, 0x9B)++;
    FIELD(arg2, u16, 0x12) -= 0x80;

update:
    FIELD(arg3, s32, 0x1C) |= 0x10000000;
    count = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = count;
    if ((s16)count <= 0) {
        if (FIELD(arg2, u8, 0xC) >= 0x10) {
            FIELD(arg2, s32, 0xC) += 0xFFEFEFF0;
        }
        FIELD(arg2, s16, 0x10) = 0x20;
        FIELD(arg2, u16, 0x14) |= 0xC;
    } else {
        FIELD(arg2, s32, 0xC) = 0x808080;
    }

    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        if (FIELD(arg2, u8, 0xC) >= 0x10) {
            goto end;
        }
    }

    global = &D_80083460;
    value = FIELD(global, s32, 0x10);
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        FIELD(global, s32, 0x10) = value & 0x7FFFFFFF;
    }
    func_800A2FE0(arg3);
    func_800A32A4(arg3);

    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(x, y, mode);
    func_8009A028(arg3);
    FIELD(arg3, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

end:
    return;
}

/* MECHANISM: Preserve unused $a1 so arg2/arg3 naturally hold in $s1/$s2, and
   encode the true-space local joins as goto-shaped CFG in retail block order.
   A guarded $v0 page hold plus seam fence restores the zero-state delay slots;
   exact-width fields and the direct D_800814A0 RMW close the remaining words. */

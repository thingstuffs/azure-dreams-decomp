#include "common.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170E68;
extern u8 D_80173894[];

void func_80172698(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 mode;
    s32 next_mode;
    u16 count;

    mode = U8(arg0, 0x9B);
    if (mode == 1) {
        goto mode_one;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto mode_zero;
        }
        goto done;
    }
    if (mode == 2) {
        goto mode_two;
    }
    goto done;

mode_zero:
    if (U16(arg2, 0x14) & 0x8000) {
        U8(arg0, 0x9B) = 2;
        U16(arg2, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, S16(arg3, 0x2A), 1);
        goto done;
    }

    S32(arg1, 0x14) = 0;
    S32(arg1, 0x10) = 0;
    S32(arg1, 0x0C) = 0;
    PTR(arg2, 0x2C) = D_80173894;
    func_80047784(arg2,
        D_80173894[((D_80083228 + S16(arg3, 0x2A) + 0x100) >> 9) & 7],
        0);
    next_mode = U8(arg0, 0x9B);
    U16(arg0, 0x96) = 0;
    goto increment_loaded;

mode_one:
    count = U16(arg0, 0x96) + 1;
    U16(arg0, 0x96) = count;
    if ((s16)count != 10) {
        goto done;
    }
    func_800A56E0(0x808);
    func_8009C12C(arg3, arg2, S16(arg3, 0x2A), 1);
    next_mode = U8(arg0, 0x9B);

increment_loaded:
    U8(arg0, 0x9B) = next_mode + 1;
    goto done;

mode_two:
    if (!(U16(arg2, 0x14) & 0xE000)) {
        goto done;
    }
    func_800A2B04(arg1, U8(arg2, 0x24), U8(arg2, 0x25));
    func_800AD594(arg3, 0x100);
    PTR(arg0, 0x8C) = &D_80170E68;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (S8(arg3, 0x6D) == 0) {
        U16(arg3, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}

/* MECHANISM: True-space calls were recovered as increment_loaded/done CFG joins, with
   retail block order and natural s2/s0/s1 argument holds. Byte-scaled table indexing
   preserves lbu/shift-nine; distinct mode and next_mode live ranges put reloads in v0. */

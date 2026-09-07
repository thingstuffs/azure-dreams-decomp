#include "common.h"

#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern s32 D_800814A0;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_8017588C[];

extern void func_80047784(void *, u8, s32);
extern void func_8009A028(void *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800A56E0(s32);
extern void func_800ACF88(void *);

void func_80173108(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 state;
    u8 *object;
    s32 inner;
    s32 outer;

    state = U8(arg0, 0x9B);
    object = 0;
    switch (state) {
    case 0:
        if (S16(&D_80083460, 0xA) != 0) {
            break;
        }
        U8(arg0, 0x9B) = 1;
        /* fallthrough */
    case 1: {
        s32 flags;
        s32 offset;
        u8 *outer_ptr;
        u32 white;
        u8 *call_ptr;

        flags = S32(arg3, 0x14);
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) {
                func_800ACF88(arg3);
            }
        }
        func_800A56E0(0x805);

        outer = 0;
        S16(arg2, 0x10) = 0x60;
        U16(arg2, 0x14) |= 0xC;
        U16(arg0, 0x98) &= 0xDFFF;
        if (S16(arg0, 0x9E) > 0) {
            white = 0xFFFFFF;
            outer_ptr = arg0;
            do {
                object = (u8 *)PTR(outer_ptr, 0xA4) + 0x20;
                inner = 0;
                if (S16(object, 2) > 0) {
                    offset = 8;
                    do {
                        call_ptr = object + offset;
                        U32(call_ptr, 0xC) = white;
                        func_80047784(call_ptr, 0x23, 0);
                        offset += 0x30;
                        inner++;
                    } while (inner < S16(object, 2));
                }
                outer_ptr += 4;
                outer++;
            } while (outer < S16(arg0, 0x9E));
        }
        U8(arg0, 0x9B) = U8(arg0, 0x9B) + 1;
        break;
    }

    case 2: {
        u8 *scan_ptr;
        u8 *entry;
        s32 delta;

        if ((s32)object < S16(arg0, 0x9E)) {
            outer = 0;
            delta = 0xFFEFEFF0;
            scan_ptr = arg0;
            do {
                object = (u8 *)PTR(scan_ptr, 0xA4) + 0x20;
                inner = 0;
                if (S16(object, 2) > 0) {
                    entry = object;
                    do {
                        (*(volatile u32 *)((u8 *)entry + 0x14)) += delta;
                        inner++;
                        entry += 0x30;
                    } while (inner < S16(object, 2));
                }
                scan_ptr += 4;
                outer++;
            } while (outer < S16(arg0, 0x9E));
        }
        if (U16(object, 0x1C) & 0x6000) {
            PTR(arg2, 0x2C) = D_8017588C;
            func_80047784(arg2,
                D_8017588C[((D_80083228 + S16(arg3, 0x2A) + 0x100) >> 9) & 7],
                0);
            U16(arg0, 0x96) = 0x80;
            U8(arg0, 0x9B) = U8(arg0, 0x9B) + 1;
        }
        break;
    }

    case 3: {
        u8 color;
        u8 arg0_value;
        u8 arg1_value;
        s32 effect;
        u8 *global_base;

        U32(arg3, 0x1C) |= 0x10000000;
        color = U8(arg0, 0x96);
        U8(arg2, 0xE) = color;
        U8(arg2, 0xD) = color;
        U8(arg2, 0xC) = color;
        U16(arg0, 0x96) -= 0x10;
        if (U8(arg2, 0xC) != 0) {
            break;
        }
        global_base = (u8 *)&D_80083460;
        if (U32(global_base, 0x10) == (u32)((u8 *)arg3 - 0x20)) {
            U32(global_base, 0x10) &= 0x7FFFFFFF;
        }
        func_800A2FE0(arg3);
        func_800A32A4(arg3);
        arg0_value = U8(arg2, 0x24);
        arg1_value = U8(arg2, 0x25);
        effect = 0x3000;
        if (U32(arg3, 0x1C) & 0x2000) {
            effect = 0x300;
        }
        func_8009A3D0(arg0_value, arg1_value, effect);
        func_8009A028(arg3);
        U16(arg3, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
    }
}

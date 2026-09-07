#include "common.h"

extern void func_80042710(void *, void *);
extern s32 func_80042900(void *, s32);
extern void func_80099FDC(void *);
extern u8 *func_800A17E8(s32, s32);
extern s32 func_800A1BD0(void *);
extern void func_800A2B04(s32, s32, s32);
extern void func_800ACB98(void *, s32, s32, void *);
extern void func_80173D40(void *, s32, void *, void *);

extern s32 D_80083460;
extern u8 *D_800E3D7C;

void func_8017398C(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3)
{
    u8 *object;
    u8 *state;
    u8 *source;
    u8 *entry;
    u8 *table;
    u8 *found;
    u8 *counterGlobal;
    u8 *activeGlobal;
    s32 value;
    u8 valid;
    u8 test;
    s32 kind;
    u8 kindByte;
    long address;

    object = *(u8 **)(arg0 + 0xA4);
    state = object + 0x20;
    source = *(u8 **)(object + 0xC);
    arg2[0x24] = source[0x24];
    arg2[0x25] = source[0x25];
    *(u16 *)(arg3 + 0x88) = *(u16 *)(state + 0x88);
    func_800A2B04(arg1, arg2[0x24], arg2[0x25]);

    object = *(u8 **)(arg0 + 0xA4);
    if (*(u16 *)(object + 0x1E) & 0x8000) {
        if ((state[0x13] == 0x1E) && (state[0x28] != 0)) {
            arg3[0x6D] = 1;
        }

        if (*(s32 *)(arg3 + 0x14) & 0x4000) {
            value = func_800A1BD0(state);
            table = D_800E3D7C;
            address = (s32)(s16)value * 4;
            address += (long)table;
            entry = (u8 *)address;
            *(u8 **)(entry + 0xAC) = arg3;
            *(s32 *)(entry + 0xE4) = 0;
            if (*(u8 **)(table + 0x60) == state) {
                *(u8 **)(table + 0x60) = arg3;
            }
        }

        if ((state[0x13] != 0x1E) && (state[0x28] == 0)) {
            counterGlobal = (u8 *)&D_80083460;
            (*(u16 *)(counterGlobal + 0xA))++;
        }

        *(s32 *)(arg3 + 0x14) = 0;
        *(s32 *)(arg3 + 0x1C) = 0;
        func_80042710(arg3, state);
        *(u32 *)(arg3 + 0x14) &= 0xDFFFFFFF;
        value = func_80042900(arg3, 1);
        if ((value << 16) != 0) {
            *(u32 *)(arg3 + 0x1C) |= 0x200;
        } else {
            *(u32 *)(arg3 + 0x1C) &= ~0x200;
        }

        arg3[0x13] = 0x1E;
        func_80099FDC(arg0 - 0x20);
        *(u32 *)(arg3 + 0x60) = *(u32 *)(state + 0x60);
        func_80173D40(arg0, arg1, arg2, arg3);
        *(u32 *)(arg0 + 0xA4) = 0;
        return;
    }

    if ((((s8)state[0x13] - 1) < 0) ||
        (state[0x13] == 0x1E) ||
        (arg0[0x9B] != 0)) {
        return;
    }

    kind = object[0x33];
    kindByte = kind;
    found = func_800A17E8(kindByte, 1);
    if (found == 0) {
        valid = 1;
    } else {
        valid = found[1] != kindByte;
    }
    test = valid;
    if (test == 0) {
        return;
    }

    found = func_800A17E8(kind, 3);
    if ((found != 0) && (found[1] == kind)) {
        valid = 0;
    }
    test = valid;
    if (test == 0) {
        return;
    }

    activeGlobal = (u8 *)&D_80083460;
    if (*(u8 **)(activeGlobal + 0xC) == state) {
        *(u8 **)(activeGlobal + 0xC) = 0;
    }
    func_800ACB98(state, *(s32 *)(state - 0x18),
                  *(s32 *)(state - 0x14), state);
    arg0[0x9B]++;
}

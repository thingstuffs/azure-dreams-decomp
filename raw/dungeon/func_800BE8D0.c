#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_8004A658(s32, s32);
extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099368(s32, s32);
extern s32 func_80099734(void *, s32);
extern s32 func_800999B0(s32);
extern void func_8009BF7C(s32, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern s8 func_800A6DA4(s32, s32);
extern s32 func_800AD6FC(void *, s32, s32);

extern s32 D_80082E80;
extern s32 D_80083460;
extern s32 D_80083780;
extern u8 D_800893DC[];
extern u16 D_800DDE84[];
extern u8 D_800E187C[];
extern u8 D_800E3548[];
extern u8 D_800E36C8[];
extern void *D_800E3D7C;

s32 func_800C4030(void *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    s32 value;
    s32 i;
    u8 *entry;
    u8 *slot;
    register u8 *state ASM_REG("$3");
    register s32 call_x ASM_REG("$4");
    register s32 call_y ASM_REG("$5");
    register s32 copy ASM_REG("$2");
    register s32 saved ASM_REG("$16");

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }

    if (arg0 == D_800E3D7C) {
        FIELD(arg0, s32, 0x110) = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        value = func_800990FC();
        call_x = arg1;
        call_y = value;
        ASM_KEEP(call_x);
        ASM_KEEP(call_y);
        saved = call_y;
        value = func_80099368(call_x, call_y);
        value = func_80099194(D_800E187C, value);
        value = func_80099734(arg0, value);
        value = func_80099194(D_800893DC, value);
        value = func_800999B0(value);
        func_80099290(value);
        ASM_KEEP(saved);
        func_800A5720(saved);

        call_x = (s32)arg0;
        ASM_KEEP(call_x);
        state = (u8 *)0x800E0000;
        ASM_KEEP(state);
        copy = FIELD(arg0, u8, 0x13);
        state -= 0x217C;
        call_y = ((u16 *)state)[copy];
        ASM_KEEP(state);
        if (func_800AD6FC((void *)call_x, call_y & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    } else {
        func_8009BF7C(1, 8);
        func_800A56E0(0x80F);
        i = 0;
        copy = 0x800E0000;
        ASM_KEEP(copy);
        entry = (u8 *)(copy + 0x36C8);
        copy = 0x800E0000;
        ASM_KEEP(copy);
        slot = (u8 *)(copy + 0x3548);
        do {
            if (slot[1] != 0) {
                call_x = 0xE;
                call_y = 3;
                ASM_KEEP(call_x);
                ASM_KEEP(call_y);
                copy = call_x;
                slot[1] = copy;
                copy = call_y;
                slot[0] = copy;
                *(s32 *)(entry + 8) = func_8004A658(call_x, call_y);
                slot[2] = func_800A6DA4(0x10, 0x18);
                copy = 1;
                slot[3] = copy;
                ASM_KEEP(copy);
            }
            entry += 0xC;
            i++;
            slot += 4;
        } while (i < 0x40);
    }

    state = (u8 *)0x80080000;
    ASM_KEEP(state);
    state += 0x3460;
    value = FIELD(state, u16, 0xA);
    call_x = arg1;
    value--;
    ASM_KEEP(state);
    FIELD(state, u16, 0xA) = value;
    func_80098B38(call_x);
    return 1;
}

/* MECHANISM: Exact callee arities plus guarded short-lived a0/a1, v0, and saved-s0 roles
   recover the retail frame and call triangles without false long-lived constants.
   A pinned v1 D_80083460 base splits the shared tail halfword RMW across both CFG paths. */

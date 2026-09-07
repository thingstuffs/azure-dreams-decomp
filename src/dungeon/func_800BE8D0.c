#include "common.h"

typedef struct S_800C4030_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800C4030_0;   /* arg0 in func_800C4030 */

typedef struct S_800C4030_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C4030_1;   /* state in func_800C4030 */



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

s32 func_800C4030(S_800C4030_0 *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    s32 value;
    s32 i;
    u8 *entry;
    u8 *slot;
    u8 *state;
    s32 call_x;
    register s32 call_y ASM_REG("$5");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 copy ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 saved;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }

    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        value = func_800990FC();
        call_x = arg1;
        call_y = value;
        ASM_KEEP(call_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
        saved = call_y;
        value = func_80099368(call_x, call_y);
        value = func_80099194(D_800E187C, value);
        value = func_80099734(arg0, value);
        value = func_80099194(D_800893DC, value);
        value = func_800999B0(value);
        func_80099290(value);
        func_800A5720(saved);

        call_x = (s32)arg0;
        ASM_KEEP(call_x);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        state = (u8 *)0x800E0000;
        ASM_KEEP(state);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        copy = arg0->unk_13;
        state -= 0x217C;
        call_y = ((u16 *)state)[copy];
        ASM_KEEP(state);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        if (func_800AD6FC((void *)call_x, call_y & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    } else {
        func_8009BF7C(1, 8);
        func_800A56E0(0x80F);
        i = 0;
        copy = 0x800E0000;
        ASM_KEEP(copy);   /* MATCH pin: load-bearing for the whole function shape */
        entry = (u8 *)(copy + 0x36C8);
        copy = 0x800E0000;
        ASM_KEEP(copy);   /* MATCH pin: load-bearing for the whole function shape */
        slot = (u8 *)(copy + 0x3548);
        do {
            if (slot[1] != 0) {
                call_x = 0xE;
                call_y = 3;
                ASM_KEEP(call_x);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                ASM_KEEP(call_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
                copy = call_x;
                slot[1] = copy;
                copy = call_y;
                slot[0] = copy;
                *(s32 *)(entry + 8) = func_8004A658(call_x, call_y);
                slot[2] = func_800A6DA4(0x10, 0x18);
                copy = 1;
                slot[3] = copy;
            }
            entry += 0xC;
            i++;
            slot += 4;
        } while (i < 0x40);
    }

    state = (u8 *)0x80080000;
    ASM_KEEP(state);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    state += 0x3460;
    value = ((S_800C4030_1 *)state)->unk_0A;
    call_x = arg1;
    value--;
    ((S_800C4030_1 *)state)->unk_0A = value;
    func_80098B38(call_x);
    return 1;
}

/* MECHANISM: Exact callee arities plus guarded short-lived a0/a1, v0, and saved-s0 roles
   recover the retail frame and call triangles without false long-lived constants.
   A pinned v1 D_80083460 base splits the shared tail halfword RMW across both CFG paths. */

#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_800990FC(s32, u8 *, void *);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern void func_800A5720(s32);
extern void __attribute__((noreturn)) func_8016AB64(void);
extern void __attribute__((noreturn)) func_8016ABB4(void);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern u8 D_80083460[];
extern u8 D_8016A808[];

void func_8016A9FC(void *arg0) {
    s32 state;
    register s32 state_arg ASM_REG("$4");
    register s32 call_arg ASM_REG("$5");
    u16 counter;
    u8 fade_a9;
    u8 fade_aa;
    u8 *base;
    u8 *counter_base;
    s32 value;
    register s32 first_value ASM_REG("$16");

    state = FIELD(arg0, s16, 0x12);
    state_arg = FIELD(arg0, u16, 0x12);
    base = D_80083160;

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    func_8016ABB4();

state_ge_2:
    ASM_KEEP(state);
    if (state == 2) {
        goto state_2;
    }
    func_8016ABB4();

state_0:
    if (base[0xA8] >= 0x65) {
        base[0xA8] -= 4;
        fade_a9 = base[0xA9] - 4;
        fade_aa = base[0xAA] - 4;
        ASM_KEEP(fade_a9);
        ASM_TAILSLOT_PIN(fade_aa);
        func_8016AB64();
    }
    FIELD(arg0, u16, 0x12) = state_arg + 1;
    FIELD(arg0, u16, 0x1A) = 0;
    value = func_800990FC(state_arg, base, arg0);
    state_arg = 0xA;
    ASM_KEEP_NV(value);
    call_arg = value;
    first_value = call_arg;
    value = func_8009929C(state_arg, call_arg);
    value = func_8009929C(0xA, value);
    value = func_80099194(D_8016A808, value);
    value = func_8009929C(0xA, value);
    value = func_8009929C(0xA, value);
    value = func_8009929C(0xA, value);
    value = func_8009929C(1, value);
    func_80099290(value);
    func_800A5720(first_value);
    func_8016ABB4();

state_1:
    counter = FIELD(arg0, u16, 0x1A);
    FIELD(arg0, u16, 0x1A) = counter + 1;
    if ((s16)counter < 0x3C) {
        goto finish;
    }
    FIELD(arg0, u16, 0x1A) = 0;
    FIELD(arg0, u16, 0x12)++;
    func_8016ABB4();

state_2:
    value = base[0xA8];
    ASM_KEEP_NV(value);
    if ((u32)(value & 0xFF) < 0x80) {
        base[0xA8] = value + 4;
        base[0xA9] += 4;
        base[0xAA] += 4;
        func_8016ABB4();
    }
    ASM_KEEP_NV(value);
    base[0xAA] = 0x80;
    base[0xA9] = 0x80;
    base[0xA8] = 0x80;
    counter_base = D_80083460;
    FIELD(counter_base, u16, 0xA)--;
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

finish:
    return;
}

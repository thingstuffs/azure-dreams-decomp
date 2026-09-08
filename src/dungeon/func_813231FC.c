#include "common.h"


extern s32 func_800990FC(s32, u8 *, void *);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern void func_800A5720(s32);
extern void __attribute__((noreturn)) func_8016AB64(void);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern u8 D_80083460[];
extern u8 D_8016A808[];


typedef struct S_8016A9FC_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x6];
    u16 unk_1A;
} S_8016A9FC_0;   /* arg0 in func_8016A9FC */

typedef struct S_8016A9FC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016A9FC_1;   /* counter_base in func_8016A9FC */

void func_8016A9FC(void *arg0) {
    s32 state;
    register s32 state_arg ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
    register s32 call_arg ASM_REG("$5");   /* MATCH pin: retail delay-slot fill depends on it */
    u16 counter;
    u8 fade_a9;
    u8 fade_aa;
    u8 *base;
    u8 *counter_base;
    s32 value;
    s32 first_value;

    state = ((S_8016A9FC_0 *)arg0)->unk_12.s;
    state_arg = ((S_8016A9FC_0 *)arg0)->unk_12.u;
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
    return;

state_ge_2:
    ASM_KEEP(state);   /* MATCH pin: retail delay-slot fill depends on it */
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
    if (base[0xA8] >= 0x65) {
        base[0xA8] -= 4;
        fade_a9 = base[0xA9] - 4;
        fade_aa = base[0xAA] - 4;
        ASM_KEEP(fade_a9);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_TAILSLOT_PIN(fade_aa);   /* MATCH pin: retail delay-slot fill depends on it */
        func_8016AB64();
    }
    ((S_8016A9FC_0 *)arg0)->unk_12.u = state_arg + 1;
    ((S_8016A9FC_0 *)arg0)->unk_1A = 0;
    value = func_800990FC(state_arg, base, arg0);
    state_arg = 0xA;
    ASM_KEEP_NV(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    return;

state_1:
    counter = ((S_8016A9FC_0 *)arg0)->unk_1A;
    ((S_8016A9FC_0 *)arg0)->unk_1A = counter + 1;
    if ((s16)counter < 0x3C) {
        goto finish;
    }
    ((S_8016A9FC_0 *)arg0)->unk_1A = 0;
    ((S_8016A9FC_0 *)arg0)->unk_12.u++;
    return;

state_2:
    value = base[0xA8];
    ASM_KEEP_NV(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if ((u32)(value & 0xFF) < 0x80) {
        base[0xA8] = value + 4;
        base[0xA9] += 4;
        base[0xAA] += 4;
        return;
    }
    ASM_KEEP_NV(value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    base[0xAA] = 0x80;
    base[0xA9] = 0x80;
    base[0xA8] = 0x80;
    counter_base = D_80083460;
    ((S_8016A9FC_1 *)counter_base)->unk_0A--;
    (*(u16 *)((u8 *)arg0 + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;

finish:
    return;
}

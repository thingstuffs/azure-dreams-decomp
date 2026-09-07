#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_80025BD8() __attribute__((noreturn));
extern void func_80025C78(void) __attribute__((noreturn));
extern void func_80025C7C() __attribute__((noreturn));
extern void func_800489F4(void *, u8, s8, s32);
extern void func_80048AC8(void *, s32);
extern s16 D_8002715A;
extern u16 D_8002715C;
extern u8 D_8006CCF8[];
extern u8 D_80082E80[];
extern u8 D_800DD008[];

void func_80025A14(void *arg0, void *arg1, void *arg2)
{
    register void *obj ASM_REG("$17") = arg2;
    register void *state ASM_REG("$6");
    register u16 counter ASM_REG("$3");
    register void *var_a0 ASM_REG("$4") = arg0;
    register void *buffer ASM_REG("$5") = arg1;
    register u16 tail_value ASM_REG("$2");
    u8 *template;
    s8 phase;
    u8 fade_in_value;
    u8 fade_out_value;
    u8 phase_value;
    s16 init_value;
    s16 index;
    void *p;

    ASM_KEEP_NV(obj);
    counter = D_8002715C;
    ASM_KEEP_NV(counter);
    state = arg0;
    ASM_KEEP(state);
    counter++;
    D_8002715C = counter;
    phase = FIELD(state, s8, 0x72);
    if (phase == 1) {
        goto fade_in;
    }
    if (phase < 2) {
        init_value = 0x1000;
        if (phase != 0) {
            func_80025C7C(var_a0);
        }
        goto init;
    }
    if (phase == 2) {
        goto check_stop;
    }
    if (phase == 3) {
        goto fade_out;
    }
    func_80025C7C(var_a0);

init:
    FIELD(buffer, s16, 2) = 0;
    FIELD(buffer, s16, 6) = 0;
    FIELD(buffer, s16, 0xA) = 0;
    FIELD(obj, s16, 0x1E) = init_value;
    FIELD(obj, s16, 0x1C) = init_value;
    FIELD(obj, u8, 0xE) = 0;
    FIELD(obj, u8, 0xD) = 0;
    FIELD(obj, u8, 0xC) = 0;
    template = D_80082E80;
    FIELD(obj, s32, 0x28) = FIELD(template, s32, 0x28);
    FIELD(obj, u16, 0x14) = FIELD(template, u16, 0x14) & 0xFFFC;
    FIELD(obj, void *, 0x2C) = D_800DD008;
    FIELD(obj, u16, 0x14) |= 0x200;
    FIELD(state, s8, 0x73) = 8;
    FIELD(state, s8, 0x72) = FIELD(state, u8, 0x72) + 1;

fade_in:
    var_a0 = (void *)(s32)FIELD(state, s8, 0x73);
    if (var_a0 != 0) {
        fade_in_value = FIELD(obj, u8, 0xE);
        fade_in_value += (0x40 - fade_in_value) / (s32)var_a0;
        FIELD(obj, u8, 0xE) = fade_in_value;
        FIELD(obj, u8, 0xD) = fade_in_value;
        FIELD(obj, u8, 0xC) = fade_in_value;
    }
    fade_in_value = FIELD(state, u8, 0x73) - 1;
    FIELD(state, u8, 0x73) = fade_in_value;
    if ((s8)fade_in_value > 0) {
        goto check_stop;
    }
    FIELD(obj, u8, 0xE) = 0x40;
    FIELD(obj, u8, 0xD) = 0x40;
    FIELD(obj, u8, 0xC) = 0x40;
    phase_value = FIELD(state, u8, 0x72);
    FIELD(state, u8, 0x73) = 0;
    FIELD(state, u8, 0x72) = phase_value + 1;

check_stop:
    if (D_8002715A != 0) {
        FIELD(state, u8, 0x73) = 8;
        FIELD(buffer, s16, 0x16) = 8;
        func_80025BD8(var_a0, buffer);
    }
    goto final_update;

fade_out:
    var_a0 = (void *)(s32)FIELD(state, s8, 0x73);
    if (var_a0 != 0) {
        fade_out_value = FIELD(obj, u8, 0xE);
        fade_out_value += (0 - fade_out_value) / (s32)var_a0;
        FIELD(obj, u8, 0xE) = fade_out_value;
        FIELD(obj, u8, 0xD) = fade_out_value;
        FIELD(obj, u8, 0xC) = fade_out_value;
    }
    fade_out_value = FIELD(state, u8, 0x73) - 1;
    FIELD(state, u8, 0x73) = fade_out_value;
    if ((s8)fade_out_value <= 0) {
        phase_value = FIELD(state, u8, 0x72);
        FIELD(state, u8, 0x72) = phase_value + 1;
    }

final_update:
    p = FIELD(state, void *, 0x58);
    p = FIELD(p, void *, -0x14);
    index = ((FIELD(p, u16, 0x1A) + 0x500) >> 9) & 7;
    if (FIELD(state, s16, 0x46) != index) {
        FIELD(state, s16, 0x46) = index;
        func_800489F4(obj, ((u8 *)FIELD(obj, void *, 0x2C))[index],
                       FIELD(obj, s8, 4), 2);
    }
    func_80048AC8(obj, 2);
    if (D_8006CCF8[index] != 0) {
        tail_value = FIELD(obj, u16, 0x14) | 1;
        ASM_TAILSLOT_PIN(tail_value);
        func_80025C78();
    }
    FIELD(obj, u16, 0x14) &= 0xFFFE;
}

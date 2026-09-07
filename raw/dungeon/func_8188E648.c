#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s32 value;
    u8 pad[8];
} Flags;

void func_80025EB8(void) __attribute__((noreturn));
void func_800260F0(void) __attribute__((noreturn));
void func_800260F4(void) __attribute__((noreturn));
void func_8002626C(void) __attribute__((noreturn));
void func_8002628C(void) __attribute__((noreturn));
s32 func_800644B8(s16);
s32 func_80064584(s16);
void func_800B835C(void *, s32 *, s32, s32);

extern Counter D_80026472;
extern u8 D_80026478[];
extern Flags D_800814A0;

void func_80025E48(void *arg0, void *arg1, void *arg2)
{
    s32 init[2];
    s16 state;
    register u16 counter ASM_REG("$2");

    {
        register s32 base_angle ASM_REG("$4");
        register s32 held_angle ASM_REG("$3");
        register s32 angle_offset ASM_REG("$2");
        register s16 angle ASM_REG("$16");

        counter = D_80026472.value;
        base_angle = FIELD(arg0, s16, 0x22);
        counter++;
        ASM_SCHED_BARRIER();
        base_angle <<= 8;
        D_80026472.value = counter;
        held_angle = base_angle;
        if (FIELD(arg0, s16, 0x24) != 0) {
            angle_offset = FIELD(arg0, s16, 0x18) * 0x10;
            angle = base_angle + angle_offset;
            ASM_TAILSLOT_PIN(angle);
            func_80025EB8();
            return;
        }

        angle_offset = FIELD(arg0, s16, 0x18) * 0x10;
        angle = held_angle - angle_offset;
        FIELD(arg1, s16, 2) = FIELD(arg0, u16, 0x5C) +
            ((FIELD(arg0, s16, 0x66) * func_80064584(angle)) >> 10);
        FIELD(arg1, s16, 6) = FIELD(arg0, u16, 0x5E) +
            ((FIELD(arg0, s16, 0x66) * func_800644B8(angle)) >> 10);
        FIELD(arg1, s16, 0xE) = FIELD(arg0, u16, 0x5C) +
            ((FIELD(arg0, s16, 0x66) * func_80064584(angle)) >> 10);
        FIELD(arg1, s16, 0x12) = FIELD(arg0, u16, 0x5E) +
            ((FIELD(arg0, s16, 0x66) * func_800644B8(angle)) >> 10);
    }

    state = FIELD(arg0, s16, 0xA);
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_8002628C();
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_8002628C();

state_0:
    {
        register s32 color0 ASM_REG("$4");
        register s32 target0 ASM_REG("$2");
        register s32 divisor0 ASM_REG("$3");
        register s32 reset0 ASM_REG("$3");
        register u16 dead_mode0 ASM_REG("$2");
        u16 timer0;

        if (FIELD(arg0, s16, 0x64) > FIELD(arg0, s16, 0x66)) {
            FIELD(arg0, u16, 0x66)++;
        }
        color0 = FIELD(arg2, u8, 0xD);
        target0 = FIELD(arg0, s16, 0x24);
        divisor0 = FIELD(arg0, s16, 0x1A);
        if (target0 != 0) {
            target0 = 0xF0;
        } else {
            target0 = 0x20;
        }
        target0 = (target0 - color0) / divisor0;
        target0 = color0 + target0;
        FIELD(arg2, u8, 0xD) = target0;
        timer0 = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, u16, 0x1A) = timer0;
        if ((timer0 << 16) > 0) {
            goto epilogue;
        }
        reset0 = 0x18;
        dead_mode0 = FIELD(arg0, u16, 0xA);
        ASM_KEEP(dead_mode0);
        FIELD(arg0, u16, 0x1A) = reset0;
        func_800260F4();
        return;
    }

state_1:
    {
        register u16 step1 ASM_REG("$2");
        register u16 timer1 ASM_REG("$3");
        register u16 dead_mode1 ASM_REG("$2");
        register s32 reset1 ASM_REG("$3");

        FIELD(arg1, s16, 0x16) +=
            (s32)(FIELD(arg0, u16, 0x26) << 16) >> 17;
        step1 = FIELD(arg0, u16, 0x26) + 1;
        timer1 = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, u16, 0x1A) = timer1;
        FIELD(arg0, u16, 0x26) = step1;
        if ((timer1 << 16) > 0) {
            goto epilogue;
        }
        dead_mode1 = FIELD(arg0, u16, 0xA);
        reset1 = 0x10;
        ASM_KEEP(dead_mode1);
        ASM_TAILSLOT_PIN(reset1);
        func_800260F0();
        return;
    }

state_2:
    {
        u8 *effect2;
        s32 color2;
        s32 target2;
        u16 timer2;

        if ((FIELD(arg0, s16, 0x24) == 0) &&
            (FIELD(arg0, s16, 0x22) == 0)) {
            effect2 = D_80026478;
            color2 = effect2[0xC];
            target2 = (0x14 - color2) / FIELD(arg0, s16, 0x1A);
            init[0] = 0x01000340;
            init[1] = 0x00200020;
            color2 += target2;
            effect2[0xC] = color2;
            effect2[0xD] = color2;
            func_800B835C(effect2, init, 1, 0);
        }
        timer2 = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, u16, 0x1A) = timer2;
        if ((timer2 << 16) > 0) {
            goto epilogue;
        }
        FIELD(arg0, u16, 0x1A) = 8;
        FIELD(arg0, u16, 0xA)++;
        func_8002628C();
        return;
    }

state_3:
    {
        u8 *effect3;
        s32 effect_color3;
        register s32 fade_color3 ASM_REG("$3");
        register s32 fade_quotient3 ASM_REG("$2");
        s32 target3;
        u16 step3;
        u16 timer3;

        FIELD(arg1, s16, 0xA) +=
            (FIELD(arg1, s16, 0x16) - FIELD(arg1, s16, 0xA)) /
            FIELD(arg0, s16, 0x1A);
        step3 = FIELD(arg0, u16, 0x1C);
        FIELD(arg0, u16, 0x1C) = step3 + 1;
        FIELD(arg0, u16, 0x18) += step3;
        FIELD(arg0, u16, 0x66) +=
            (((s32)(FIELD(arg0, u16, 0x64) << 16) >> 17) -
            FIELD(arg0, s16, 0x66)) / FIELD(arg0, s16, 0x1A);

        if ((FIELD(arg0, s16, 0x24) == 0) &&
            (FIELD(arg0, s16, 0x22) == 0)) {
            effect3 = D_80026478;
            effect_color3 = effect3[0xC];
            target3 = (0x10 - effect_color3) /
                FIELD(arg0, s16, 0x1A);
            init[0] = 0x01000340;
            init[1] = 0x00200020;
            effect_color3 += target3;
            effect3[0xC] = effect_color3;
            effect3[0xD] = effect_color3;
            func_800B835C(effect3, init, 1, 0);
        }
        if (FIELD(arg0, s16, 0x24) == 0) {
            goto fade_slow;
        }

fade_fast:
        fade_color3 = FIELD(arg2, u8, 0xD);
        fade_quotient3 = fade_color3 /
            (FIELD(arg0, s16, 0x1A) - 6);
        fade_color3 -= fade_quotient3;
        FIELD(arg2, u8, 0xD) = fade_color3;
        timer3 = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, u16, 0x1A) = timer3;
        if ((s16)timer3 < 7) {
            func_8002626C();
            return;
        }
        goto epilogue;

fade_slow:
        fade_color3 = FIELD(arg2, u8, 0xD);
        fade_quotient3 = fade_color3 /
            FIELD(arg0, s16, 0x1A);
        fade_color3 -= fade_quotient3;
        FIELD(arg2, u8, 0xD) = fade_color3;
        timer3 = FIELD(arg0, u16, 0x1A) - 1;
        FIELD(arg0, u16, 0x1A) = timer3;
        if ((timer3 << 16) > 0) {
            goto epilogue;
        }
        ASM_SCHED_BARRIER();
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

epilogue:
    return;
}

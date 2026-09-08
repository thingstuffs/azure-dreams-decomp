#include "common.h"


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
s32 func_800644B8(s16);
s32 func_80064584(s16);
void func_800B835C(void *, s32 *, s32, s32);

extern Counter D_80026472;
extern u8 D_80026478[];
extern Flags D_800814A0;


typedef struct S_80025E48_0_pre {
    u16 unk_00;
} S_80025E48_0_pre;   /* the 0x2 bytes before arg0 in func_80025E48, addressed as arg0[-1] */

typedef struct S_80025E48_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xC];
    union { s16 s; u16 u; } unk_18;   /* accessed as both */
    union { s16 s; u16 u; } unk_1A;   /* accessed as both */
    u16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
    s16 unk_24;
    u16 unk_26;
    u8 pad_28[0x34];
    u16 unk_5C;
    u16 unk_5E;
    u8 pad_60[0x4];
    union { s16 s; u16 u; } unk_64;   /* accessed as both */
    union { s16 s; u16 u; } unk_66;   /* accessed as both */
} S_80025E48_0;   /* arg0 in func_80025E48 */

typedef struct S_80025E48_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_80025E48_1;   /* arg1 in func_80025E48 */

typedef struct S_80025E48_2 {
    u8 pad_00[0xD];
    u8 unk_0D;
} S_80025E48_2;   /* arg2 in func_80025E48 */

void func_80025E48(void *arg0, S_80025E48_1 *arg1, S_80025E48_2 *arg2)
{
    s32 init[2];
    s16 state;
    register u16 counter ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    {
        register s32 base_angle ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 held_angle ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 angle_offset;
        register s16 angle ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        counter = D_80026472.value;
        base_angle = ((S_80025E48_0 *)arg0)->unk_22;
        counter++;
        base_angle <<= 8;
        D_80026472.value = counter;
        held_angle = base_angle;
        if (((S_80025E48_0 *)arg0)->unk_24 != 0) {
            angle_offset = ((S_80025E48_0 *)arg0)->unk_18.s * 0x10;
            angle = base_angle + angle_offset;
            ASM_TAILSLOT_PIN(angle);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_80025EB8();
            return;
        }

        angle_offset = ((S_80025E48_0 *)arg0)->unk_18.s * 0x10;
        angle = held_angle - angle_offset;
        arg1->unk_02 = ((S_80025E48_0 *)arg0)->unk_5C +
            ((((S_80025E48_0 *)arg0)->unk_66.s * func_80064584(angle)) >> 10);
        arg1->unk_06 = ((S_80025E48_0 *)arg0)->unk_5E +
            ((((S_80025E48_0 *)arg0)->unk_66.s * func_800644B8(angle)) >> 10);
        arg1->unk_0E = ((S_80025E48_0 *)arg0)->unk_5C +
            ((((S_80025E48_0 *)arg0)->unk_66.s * func_80064584(angle)) >> 10);
        arg1->unk_12 = ((S_80025E48_0 *)arg0)->unk_5E +
            ((((S_80025E48_0 *)arg0)->unk_66.s * func_800644B8(angle)) >> 10);
    }

    state = ((S_80025E48_0 *)arg0)->unk_0A.s;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return;

state_0:
    {
        register s32 color0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 target0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 divisor0;
        s32 reset0;
        u16 dead_mode0;
        u16 timer0;

        if (((S_80025E48_0 *)arg0)->unk_64.s > ((S_80025E48_0 *)arg0)->unk_66.s) {
            ((S_80025E48_0 *)arg0)->unk_66.u++;
        }
        color0 = arg2->unk_0D;
        target0 = ((S_80025E48_0 *)arg0)->unk_24;
        divisor0 = ((S_80025E48_0 *)arg0)->unk_1A.s;
        if (target0 != 0) {
            target0 = 0xF0;
        } else {
            target0 = 0x20;
        }
        target0 = (target0 - color0) / divisor0;
        target0 = color0 + target0;
        arg2->unk_0D = target0;
        timer0 = ((S_80025E48_0 *)arg0)->unk_1A.u - 1;
        ((S_80025E48_0 *)arg0)->unk_1A.u = timer0;
        if ((timer0 << 16) > 0) {
            goto epilogue;
        }
        reset0 = 0x18;
        dead_mode0 = ((S_80025E48_0 *)arg0)->unk_0A.u;
        ASM_KEEP(dead_mode0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        ((S_80025E48_0 *)arg0)->unk_1A.u = reset0;
        func_800260F4();
        return;
    }

state_1:
    {
        register u16 step1 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        u16 timer1;
        u16 dead_mode1;
        s32 reset1;

        arg1->unk_16 +=
            (s32)(((S_80025E48_0 *)arg0)->unk_26 << 16) >> 17;
        step1 = ((S_80025E48_0 *)arg0)->unk_26 + 1;
        timer1 = ((S_80025E48_0 *)arg0)->unk_1A.u - 1;
        ((S_80025E48_0 *)arg0)->unk_1A.u = timer1;
        ((S_80025E48_0 *)arg0)->unk_26 = step1;
        if ((timer1 << 16) > 0) {
            goto epilogue;
        }
        dead_mode1 = ((S_80025E48_0 *)arg0)->unk_0A.u;
        reset1 = 0x10;
        ASM_KEEP(dead_mode1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        ASM_TAILSLOT_PIN(reset1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800260F0();
        return;
    }

state_2:
    {
        u8 *effect2;
        s32 color2;
        s32 target2;
        u16 timer2;

        if ((((S_80025E48_0 *)arg0)->unk_24 == 0) &&
            (((S_80025E48_0 *)arg0)->unk_22 == 0)) {
            effect2 = D_80026478;
            color2 = effect2[0xC];
            target2 = (0x14 - color2) / ((S_80025E48_0 *)arg0)->unk_1A.s;
            init[0] = 0x01000340;
            init[1] = 0x00200020;
            color2 += target2;
            effect2[0xC] = color2;
            effect2[0xD] = color2;
            func_800B835C(effect2, init, 1, 0);
        }
        timer2 = ((S_80025E48_0 *)arg0)->unk_1A.u - 1;
        ((S_80025E48_0 *)arg0)->unk_1A.u = timer2;
        if ((timer2 << 16) > 0) {
            goto epilogue;
        }
        ((S_80025E48_0 *)arg0)->unk_1A.u = 8;
        ((S_80025E48_0 *)arg0)->unk_0A.u++;
        return;
    }

state_3:
    {
        u8 *effect3;
        s32 effect_color3;
        register s32 fade_color3 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 fade_quotient3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        s32 target3;
        u16 step3;
        u16 timer3;

        arg1->unk_0A +=
            (arg1->unk_16 - arg1->unk_0A) /
            ((S_80025E48_0 *)arg0)->unk_1A.s;
        step3 = ((S_80025E48_0 *)arg0)->unk_1C;
        ((S_80025E48_0 *)arg0)->unk_1C = step3 + 1;
        ((S_80025E48_0 *)arg0)->unk_18.u += step3;
        ((S_80025E48_0 *)arg0)->unk_66.u +=
            (((s32)(((S_80025E48_0 *)arg0)->unk_64.u << 16) >> 17) -
            ((S_80025E48_0 *)arg0)->unk_66.s) / ((S_80025E48_0 *)arg0)->unk_1A.s;

        if ((((S_80025E48_0 *)arg0)->unk_24 == 0) &&
            (((S_80025E48_0 *)arg0)->unk_22 == 0)) {
            effect3 = D_80026478;
            effect_color3 = effect3[0xC];
            target3 = (0x10 - effect_color3) /
                ((S_80025E48_0 *)arg0)->unk_1A.s;
            init[0] = 0x01000340;
            init[1] = 0x00200020;
            effect_color3 += target3;
            effect3[0xC] = effect_color3;
            effect3[0xD] = effect_color3;
            func_800B835C(effect3, init, 1, 0);
        }
        if (((S_80025E48_0 *)arg0)->unk_24 == 0) {
            goto fade_slow;
        }

fade_fast:
        fade_color3 = arg2->unk_0D;
        fade_quotient3 = fade_color3 /
            (((S_80025E48_0 *)arg0)->unk_1A.s - 6);
        fade_color3 -= fade_quotient3;
        arg2->unk_0D = fade_color3;
        timer3 = ((S_80025E48_0 *)arg0)->unk_1A.u - 1;
        ((S_80025E48_0 *)arg0)->unk_1A.u = timer3;
        if ((s16)timer3 < 7) {
            func_8002626C();
            return;
        }
        goto epilogue;

fade_slow:
        fade_color3 = arg2->unk_0D;
        fade_quotient3 = fade_color3 /
            ((S_80025E48_0 *)arg0)->unk_1A.s;
        fade_color3 -= fade_quotient3;
        arg2->unk_0D = fade_color3;
        timer3 = ((S_80025E48_0 *)arg0)->unk_1A.u - 1;
        ((S_80025E48_0 *)arg0)->unk_1A.u = timer3;
        if ((timer3 << 16) > 0) {
            goto epilogue;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        ((S_80025E48_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

epilogue:
    return;
}

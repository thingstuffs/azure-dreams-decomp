#include "common.h"
#include "m2c_compat.h"

typedef struct S_818C3448_0_pre {
    u16 unk_00;
} S_818C3448_0_pre;   /* the 0x2 bytes before arg0 in func_818C3448, addressed as arg0[-1] */

typedef struct S_818C3448_0 {
    void * unk_00;
    u8 pad_04[0xA];
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u16 unk_12;
    s16 unk_14;
} S_818C3448_0;   /* arg0 in func_818C3448 */

typedef struct S_818C3448_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_818C3448_1;   /* temp_v1 in func_818C3448 */

typedef struct S_818C3448_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C3448_2;   /* arg2 in func_818C3448 */


extern s32 D_800814A0[3];
M2C_UNK func_800247AC();
M2C_UNK func_80024AF4();
M2C_UNK func_80024E9C() __attribute__((noreturn));
void func_80024EEC(void) __attribute__((noreturn));
s32 func_80069EF8();

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} Func818C3448State;

/* Update the effect's color, rotation, growth, motion, and phase transitions. */
void func_818C3448(void *effect, void *motion, S_818C3448_2 *visual) {
    s16 scale;
    s32 color_bits;
    register s32 color_cycle ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    s16 angle;
    s16 next_tick;
    s16 phase;
    s16 elapsed;
    s16 duration;
    s32 color_bias;
    s32 half_color;
    s32 velocity_y;
    s32 velocity_z;
    register s32 full_scale ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
    s32 opposite_angle;
    s32 position_x;
    s32 random_value;
    s32 velocity_x;
    s32 opposite_bias;
    s32 random_bias;
    s32 still_growing;
    u16 burst_phase;
    u16 wait_phase;
    S_818C3448_1 *owner;

    owner = ((S_818C3448_0 *)effect)->unk_00;
    owner->unk_0C = (u16) (owner->unk_0C + 1);
    next_tick = (s16) (((S_818C3448_0 *)effect)->unk_12 + 1);
    color_cycle = next_tick;
    ((S_818C3448_0 *)effect)->unk_10.s = (u16) (((S_818C3448_0 *)effect)->unk_10.s + 1);
    ((S_818C3448_0 *)effect)->unk_12 = (u16) next_tick;
    color_cycle = (color_cycle % 7) + 1;
    func_800478B8(visual);
    color_bits = (s16) color_cycle;
    color_bias = color_bits;
    visual->unk_1A = (u16) (visual->unk_1A + 0x300);
    if (color_bits < 0) {
        color_bias = color_bits + 3;
    }
    half_color = color_bits / 2;
    visual->unk_0C = (s8) ((color_bias >> 2) << 7);
    visual->unk_0D = (s8) ((s32) (((s16) half_color - (((s32) ((s16) half_color + ((u32) (half_color << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    visual->unk_0E = (s8) ((s32) ((color_bits - (half_color * 2)) << 0x10) >> 9);
    phase = ((S_818C3448_0 *)effect)->unk_0E.s;
    wait_phase = (u16) ((S_818C3448_0 *)effect)->unk_0E.s;
    if (phase == 1) {
        goto case_1;
    }
    if (phase < 2) {
        if (phase == 0) {
            full_scale = 0x1400;
            goto case_0;
        }
        func_80024EEC();
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
    if (phase == 2) {
        goto case_2;
    }
    if (phase == 3) {
        goto case_3;
    }
    func_80024EEC();

case_0:
        scale = (full_scale / (s16) ((S_818C3448_0 *)effect)->unk_14) * (s16) ((S_818C3448_0 *)effect)->unk_10.s;
        visual->unk_1E = scale;
        visual->unk_1C = scale;
        position_x = ((Func818C3448State *)motion)->f0;
        velocity_x = ((Func818C3448State *)motion)->fC;
        velocity_y = ((Func818C3448State *)motion)->f10;
        velocity_z = ((Func818C3448State *)motion)->f14;
        ((Func818C3448State *)motion)->f0 = position_x + velocity_x;
        ((Func818C3448State *)motion)->f4 = (s32) (((Func818C3448State *)motion)->f4 + velocity_y);
        ((Func818C3448State *)motion)->f8 = (s32) (((Func818C3448State *)motion)->f8 + velocity_z);
        elapsed = ((S_818C3448_0 *)effect)->unk_10.u;
        duration = ((S_818C3448_0 *)effect)->unk_14;
        still_growing = elapsed < duration;
        ASM_TAILSLOT_PIN(still_growing);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_80024E9C(velocity_y, velocity_z);
        return;
case_1:
        if ((s16) ((S_818C3448_0 *)effect)->unk_10.s < 0xC) {
            return;
        }
        ((S_818C3448_0 *)effect)->unk_0E.s = (s16) (wait_phase + 1);
        ((S_818C3448_0 *)effect)->unk_10.u = 0;
        func_80024EEC();
        return;
case_2:
        func_80024AF4(effect, motion, visual);
        random_bias = func_80069EF8();
        random_value = random_bias;
        if (random_value < 0) {
            random_bias = random_value + 0xFFF;
        }
        angle = random_value - ((random_bias >> 0xC) << 0xC);
        func_800247AC(effect, motion, angle);
        opposite_angle = angle + 0x800;
        opposite_bias = opposite_angle;
        if (opposite_angle < 0) {
            opposite_bias = angle + 0x17FF;
        }
        func_800247AC(effect, motion, (s16) (opposite_angle - ((opposite_bias >> 0xC) << 0xC)));
        if ((s16) ((S_818C3448_0 *)effect)->unk_10.s < 0x21) {
            return;
        }
        burst_phase = ((S_818C3448_0 *)effect)->unk_0E.u;
        ((S_818C3448_0 *)effect)->unk_10.s = 0U;
        ((S_818C3448_0 *)effect)->unk_0E.u = (u16) (burst_phase + 1);
        func_80024EEC();
        return;
case_3:
        if (visual->unk_14 & 0x6000) {
            ((S_818C3448_0_pre *)effect)[-1].unk_00 = (u16) (((S_818C3448_0_pre *)effect)[-1].unk_00 | 0x8000);
            D_800814A0[0] |= 0x8000;
        }
        return;
}

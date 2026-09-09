#include "common.h"

typedef struct S_func_818BD74C_0 {
    void *unk_00;
    u8 pad_04[0xA];
    union { s16 s; u16 u; } unk_0E;
    union { s16 s; u16 u; } unk_10;
    u16 unk_12;
    s16 unk_14;
    union { s16 s; u16 u; } unk_16;
    void *unk_18;
} S_func_818BD74C_0;

typedef struct S_func_818BD74C_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_818BD74C_1;

typedef struct S_func_818BD74C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_func_818BD74C_2;

typedef struct S_func_818BD74C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_func_818BD74C_3;

typedef struct S_func_818BD74C_4 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_func_818BD74C_4;

extern s32 D_800814A0;
extern u8 D_800DDC40[];
extern void func_800247B0(void *, void *, s16);
extern void func_800249C4(void *, void *, s16, s32);
extern void func_80024D2C(void *, void *, s16, s16);
extern void func_80025328(void) __attribute__((noreturn));
extern s32 func_80069EF8(void);

/* Animate a moving effect through color cycling, shrinking, and radial emission. */
void func_818BD74C(void *effect_arg, void *motion_arg, void *sprite) {
    s16 color_step;
    s32 random_value;
    s16 state;
    s16 color_bits;
    s32 color_quarter_bias;
    s32 color_half;
    u32 color_shifted;
    s32 state_or_scale;
    s32 pos_x;
    s32 vel_x;
    s32 vel_y;
    s32 vel_z;
    s32 pos_y;
    s32 pos_z;
    u16 final_state;
    u16 state_ticks;
    u16 color_ticks;
    u16 angle;
    s32 scaled_magnitude;
    S_func_818BD74C_0 *effect;
    S_func_818BD74C_1 *motion;
    S_func_818BD74C_2 *owner;
    u8 *magnitude_table;

    effect = effect_arg;
    owner = effect->unk_00;
    owner->unk_14 = (s16)(owner->unk_14 + 1);
    motion = motion_arg;
    state_ticks = effect->unk_10.u;
    color_ticks = effect->unk_12;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    effect->unk_10.u = (u16)(state_ticks + 1);
    effect->unk_12 = (u16)(color_ticks + 1);
    angle = effect->unk_16.u;
    effect->unk_16.u = (u16)(angle + 0x140);
    if (effect->unk_0E.s != 0) {
        color_step = (s16)effect->unk_12;
        color_step = (s16)(color_step % 7);
        color_step += 1;
        color_shifted = (u32)(color_step << 0x10);
        color_bits = (s16)(color_shifted >> 0x10);
        color_quarter_bias = color_bits;
        if (color_bits < 0) {
            color_quarter_bias += 3;
        }
        color_half = (s32)(color_bits + (color_shifted >> 0x1F)) >> 1;
        ((S_func_818BD74C_3 *)sprite)->unk_0C = (s8)(((color_quarter_bias >> 2) << 7) + 0x40);
        ((S_func_818BD74C_3 *)sprite)->unk_0D = (s8)(((s32)(((s16)color_half - (((s32)((s16)color_half + ((u32)(color_half << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) + 0x40);
        ((S_func_818BD74C_3 *)sprite)->unk_0E = (s8)(((s32)((color_bits - (color_half * 2)) << 0x10) >> 9) + 0x40);
    }
    ((S_func_818BD74C_3 *)sprite)->unk_1A = (u16)(((S_func_818BD74C_3 *)sprite)->unk_1A + 0x300);
    state = effect->unk_0E.s;
    if (state == 1) {
        goto state1;
    }
    if (state >= 2) {
        goto state_ge2;
    }
    if (state == 0) {
        goto state0;
    }
    func_80025328();
    return;

state_ge2:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    state_or_scale = 2;
    
    if (state != state_or_scale) {
        func_80025328();
        return;
    }
    goto state2;

state0:
    pos_x = motion->unk_00;
    vel_x = motion->unk_0C;
    vel_y = motion->unk_10;
    vel_z = motion->unk_14;
    motion->unk_00 = pos_x + vel_x;
    pos_y = motion->unk_04;
    pos_z = motion->unk_08;
    motion->unk_04 = pos_y + vel_y;
    motion->unk_08 = pos_z + vel_z;
    if (effect->unk_10.s < effect->unk_14) {
        func_80025328();
        return;
    }
    goto advance;

state1:
    ((S_func_818BD74C_3 *)sprite)->unk_12 = 0;
    ((S_func_818BD74C_3 *)sprite)->unk_14 = (u16)(((S_func_818BD74C_3 *)sprite)->unk_14 & 0xFEFF);
    state_or_scale = (0x19 - effect->unk_10.s) << 8;
    ((S_func_818BD74C_3 *)sprite)->unk_1E = state_or_scale;
    ((S_func_818BD74C_3 *)sprite)->unk_1C = state_or_scale;
    if (effect->unk_10.s < 0x10) {
        return;
    }
    random_value = (s16)func_80069EF8();
    magnitude_table = D_800DDC40;
    scaled_magnitude = magnitude_table[((S_func_818BD74C_4 *)effect->unk_18)->unk_13] * 3;
    if (scaled_magnitude < 0) {
        scaled_magnitude += 3;
    }
    func_800249C4(effect, motion, (s16)random_value, 0 - (scaled_magnitude >> 2));
    func_800247B0(effect, motion, magnitude_table[((S_func_818BD74C_4 *)effect->unk_18)->unk_13]);
    goto advance;

advance:
    effect->unk_10.s = 0;
    effect->unk_0E.u = (u16)(effect->unk_0E.u + 1);
    func_80025328();

state2:
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), effect->unk_16.s);
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), (s16)((u16)effect->unk_16.s + 0x400));
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), (s16)((u16)effect->unk_16.s + 0x800));
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), (s16)((u16)effect->unk_16.s + 0xC00));
    if (effect->unk_10.s < 0x30) {
        return;
    }
    effect->unk_10.s = 0;
    *(u16 *)((u8 *)effect - 2) = (u16)(*(u16 *)((u8 *)effect - 2) | 0x8000);
    final_state = *(volatile u16 *)((u8 *)effect + 0xE);
    {
        s32 global_flags = D_800814A0;
        *(volatile u16 *)((u8 *)effect + 0xE) = (u16)(final_state + 1);
        D_800814A0 = global_flags | 0x8000;
    }
}

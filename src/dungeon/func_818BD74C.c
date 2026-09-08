#include "common.h"

#define FIELD(p, t, off) (*(t)((s8 *)(p) + (off)))

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
    void *effect;
    void *motion;
    void *owner;
    u8 *magnitude_table;

    effect = effect_arg;
    owner = FIELD(effect, void **, 0);
    FIELD(owner, u16 *, 0x14) = (s16)(FIELD(owner, u16 *, 0x14) + 1);
    motion = motion_arg;
    state_ticks = FIELD(effect, u16 *, 0x10);
    color_ticks = FIELD(effect, u16 *, 0x12);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    FIELD(effect, u16 *, 0x10) = (u16)(state_ticks + 1);
    FIELD(effect, u16 *, 0x12) = (u16)(color_ticks + 1);
    angle = FIELD(effect, u16 *, 0x16);
    FIELD(effect, u16 *, 0x16) = (u16)(angle + 0x140);
    if (FIELD(effect, s16 *, 0xE) != 0) {
        color_step = (s16)FIELD(effect, u16 *, 0x12);
        color_step = (s16)(color_step % 7);
        color_step += 1;
        color_shifted = (u32)(color_step << 0x10);
        color_bits = (s16)(color_shifted >> 0x10);
        color_quarter_bias = color_bits;
        if (color_bits < 0) {
            color_quarter_bias += 3;
        }
        color_half = (s32)(color_bits + (color_shifted >> 0x1F)) >> 1;
        FIELD(sprite, s8 *, 0xC) = (s8)(((color_quarter_bias >> 2) << 7) + 0x40);
        FIELD(sprite, s8 *, 0xD) = (s8)(((s32)(((s16)color_half - (((s32)((s16)color_half + ((u32)(color_half << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) + 0x40);
        FIELD(sprite, s8 *, 0xE) = (s8)(((s32)((color_bits - (color_half * 2)) << 0x10) >> 9) + 0x40);
    }
    FIELD(sprite, u16 *, 0x1A) = (u16)(FIELD(sprite, u16 *, 0x1A) + 0x300);
    state = FIELD(effect, s16 *, 0xE);
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
    pos_x = FIELD(motion, s32 *, 0);
    vel_x = FIELD(motion, s32 *, 0xC);
    vel_y = FIELD(motion, s32 *, 0x10);
    vel_z = FIELD(motion, s32 *, 0x14);
    FIELD(motion, s32 *, 0) = pos_x + vel_x;
    pos_y = FIELD(motion, s32 *, 4);
    pos_z = FIELD(motion, s32 *, 8);
    FIELD(motion, s32 *, 4) = pos_y + vel_y;
    FIELD(motion, s32 *, 8) = pos_z + vel_z;
    if (FIELD(effect, s16 *, 0x10) < FIELD(effect, s16 *, 0x14)) {
        func_80025328();
        return;
    }
    goto advance;

state1:
    FIELD(sprite, s16 *, 0x12) = 0;
    FIELD(sprite, u16 *, 0x14) = (u16)(FIELD(sprite, u16 *, 0x14) & 0xFEFF);
    state_or_scale = (0x19 - FIELD(effect, s16 *, 0x10)) << 8;
    FIELD(sprite, s16 *, 0x1E) = state_or_scale;
    FIELD(sprite, s16 *, 0x1C) = state_or_scale;
    if (FIELD(effect, s16 *, 0x10) < 0x10) {
        return;
    }
    random_value = (s16)func_80069EF8();
    magnitude_table = D_800DDC40;
    scaled_magnitude = magnitude_table[FIELD(FIELD(effect, void **, 0x18), u8 *, 0x13)] * 3;
    if (scaled_magnitude < 0) {
        scaled_magnitude += 3;
    }
    func_800249C4(effect, motion, (s16)random_value, 0 - (scaled_magnitude >> 2));
    func_800247B0(effect, motion, magnitude_table[FIELD(FIELD(effect, void **, 0x18), u8 *, 0x13)]);
    goto advance;

advance:
    FIELD(effect, s16 *, 0x10) = 0;
    FIELD(effect, u16 *, 0xE) = (u16)(FIELD(effect, u16 *, 0xE) + 1);
    func_80025328();

state2:
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), FIELD(effect, s16 *, 0x16));
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), (s16)((u16)FIELD(effect, s16 *, 0x16) + 0x400));
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), (s16)((u16)FIELD(effect, s16 *, 0x16) + 0x800));
    func_80024D2C(effect, motion, (s16)(func_80069EF8() % 7), (s16)((u16)FIELD(effect, s16 *, 0x16) + 0xC00));
    if (FIELD(effect, s16 *, 0x10) < 0x30) {
        return;
    }
    FIELD(effect, s16 *, 0x10) = 0;
    FIELD(effect, u16 *, -2) = (u16)(FIELD(effect, u16 *, -2) | 0x8000);
    final_state = *(volatile u16 *)((s8 *)effect + 0xE);
    {
        s32 global_flags = D_800814A0;
        *(volatile u16 *)((s8 *)effect + 0xE) = (u16)(final_state + 1);
        D_800814A0 = global_flags | 0x8000;
    }
}

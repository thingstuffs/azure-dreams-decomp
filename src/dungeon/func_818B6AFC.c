#include "common.h"
#include "m2c_compat.h"

typedef struct S_818B6AFC_0_pre {
    u16 unk_00;
} S_818B6AFC_0_pre;   /* the 0x2 bytes before arg0 in func_818B6AFC, addressed as arg0[-1] */

typedef struct S_818B6AFC_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
    u16 unk_0E;
    void * unk_10;
} S_818B6AFC_0;   /* arg0 in func_818B6AFC */

typedef struct S_818B6AFC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818B6AFC_1;   /* temp_v1 in func_818B6AFC */

typedef struct S_818B6AFC_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_2;   /* temp_a0 in func_818B6AFC */

typedef struct S_818B6AFC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_818B6AFC_3;   /* temp_t0 in func_818B6AFC */

typedef struct S_818B6AFC_4 {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_818B6AFC_4;   /* arg2 in func_818B6AFC */

typedef struct S_818B6AFC_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_5;   /* temp_a0_4 in func_818B6AFC */

typedef struct S_818B6AFC_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_6;   /* temp_a0_7 in func_818B6AFC */

typedef struct S_818B6AFC_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_7;   /* temp_a0_10 in func_818B6AFC */

typedef struct S_818B6AFC_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818B6AFC_8_pre;   /* the 0x14 bytes before ((S_818B6AFC_0 *)arg0)->unk_10 in func_818B6AFC, addressed as ((S_818B6AFC_0 *)arg0)->unk_10[-1] */


M2C_UNK func_80024154();
M2C_UNK func_8002473C() __attribute__((noreturn));
M2C_UNK func_80024780() __attribute__((noreturn));
extern M2C_UNK D_800814A0;

#ifdef NON_MATCHING
#define M2C_READ_MUL_HI(dst, a, b) \
    do { (dst) = (s32) (((s64) (s32) (a) * (s64) (s32) (b)) >> 32); } while (0)
#define M2C_MUL_LO(a, b) ((s32) ((s64) (s32) (a) * (s64) (s32) (b)))
#else
register s32 implicit_lo ASM_REG("lo");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#define M2C_READ_MUL_HI(dst, a, b) \
    do { \
        register s32 implicit_hi ASM_REG("hi"); \
        ASM_CLOBBER("hi"); \
        (dst) = implicit_hi; \
        \
        ASM_CLOBBER("hi"); \
    } while (0)
#define M2C_MUL_LO(a, b) \
    (implicit_lo = (s32) (a) * (s32) (b), implicit_lo)
#endif

/* Cycle through seven colors with fade-in and fade-out, then mark the effect finished. */
void func_818B6AFC(void *effect_data, M2C_UNK render_arg, void *color_out) {
    s32 fade_in_color;
    s16 fade_in_green;
    s32 hold_color;
    s32 fade_out_color;
    s16 fade_out_green;
    s16 frame;
    s16 fade_in_blue;
    register s32 div_adjust ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 fade_work;
    s32 rounded_color;
    register s32 hold_bits ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 channel_bit;
    register s32 fade_out_red ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 fade_in_half;
    s32 fade_out_half;
    s32 packed_channel;
    s32 fade_out_remainder;
    register s32 cycle_quotient ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 packed_color;
    s32 end_frame;
    s32 frames_left;
    s32 div_seven_magic;
    s32 cycle_value;
    u16 fade_in_tick;
    u16 hold_tick;
    u16 fade_out_tick;
    register s32 product_result ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s8 red;
    s8 green;
    s8 blue;
    void *fade_in_target;
    void *finished_target;
    void *hold_target;
    void *fade_out_target;
    void *target_color;
    void *owner;
    void *effect;

    effect = effect_data;
    owner = ((S_818B6AFC_0 *)effect)->unk_00;
    ((S_818B6AFC_1 *)owner)->unk_14 = (u16) (((S_818B6AFC_1 *)owner)->unk_14 + 1);
    ((S_818B6AFC_0 *)effect)->unk_06 = (u16) (((S_818B6AFC_0 *)effect)->unk_06 + 1);
    ((S_818B6AFC_0 *)effect)->unk_08 = (u16) (((S_818B6AFC_0 *)effect)->unk_08 + 1);
    ((S_818B6AFC_0 *)effect)->unk_0C = (u16) (((S_818B6AFC_0 *)effect)->unk_0C + 0x80);
    ((S_818B6AFC_0 *)effect)->unk_0E = (u16) (((S_818B6AFC_0 *)effect)->unk_0E + 0x80);
    frame = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
    if (frame < 8) {
        fade_in_target = ((S_818B6AFC_0 *)effect)->unk_10;
        ((S_818B6AFC_2 *)fade_in_target)->unk_1C = (s32) (((S_818B6AFC_2 *)fade_in_target)->unk_1C | 0x10000000);
        fade_in_tick = ((S_818B6AFC_0 *)effect)->unk_08;
        cycle_value = (s16) fade_in_tick;
        div_seven_magic = (s32) 0x92490000;
        div_seven_magic = (s32) ((u32) div_seven_magic | 0x2493);
#ifndef NON_MATCHING
        implicit_lo = cycle_value * div_seven_magic;
#endif
        target_color = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)effect)->unk_10))[-1].unk_00;
        div_adjust = (s32) (s16) fade_in_tick >> 31;
        M2C_READ_MUL_HI(product_result, cycle_value, div_seven_magic);
        cycle_quotient = ((product_result + cycle_value) >> 2) - div_adjust;
        ASM_KEEP_NV(cycle_quotient);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        cycle_value = cycle_value - (cycle_quotient * 7);
        cycle_value = cycle_value + 1;
        packed_channel = (s32) ((u32) cycle_value << 16);
        fade_in_color = packed_channel >> 16;
        div_adjust = fade_in_color;
        if (fade_in_color < 0) {
            div_adjust = fade_in_color + 3;
        }
        channel_bit = div_adjust >> 2;
        product_result = M2C_MUL_LO(channel_bit, (s16) ((S_818B6AFC_0 *)effect)->unk_06 << 3);
        fade_in_half = (fade_in_color + (s32) ((u32) packed_channel >> 31)) >> 1;
        ((S_818B6AFC_3 *)target_color)->unk_0C = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        fade_in_green = (s16) fade_in_half % 2;
        packed_channel = (s32) ((u32) (fade_in_color - (fade_in_half * 2)) << 16);
        product_result = M2C_MUL_LO(fade_in_green, (s16) ((S_818B6AFC_0 *)effect)->unk_06 << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0D = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        fade_in_blue = packed_channel >> 16;
        product_result = M2C_MUL_LO(fade_in_blue, (s16) ((S_818B6AFC_0 *)effect)->unk_06 << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0E = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        product_result = M2C_MUL_LO(channel_bit, ((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at00.v = (s8) product_result;
        product_result = M2C_MUL_LO(fade_in_green, ((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at01.v = (s8) product_result;
#ifdef NON_MATCHING
        ((S_818B6AFC_4 *)color_out)->unk_0C.at02.v = (s8) (fade_in_blue * ((((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3)) << 3));
#else
        implicit_lo = fade_in_blue * (((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3) << 3);
#endif
        func_8002473C(fade_in_green, fade_in_blue, fade_in_color, effect);
        return;
    }
    if (frame < 0x28) {
        hold_target = ((S_818B6AFC_0 *)effect)->unk_10;
        ((S_818B6AFC_5 *)hold_target)->unk_1C = (s32) (((S_818B6AFC_5 *)hold_target)->unk_1C | 0x10000000);
        hold_tick = ((S_818B6AFC_0 *)effect)->unk_08;
        cycle_value = (s16) hold_tick;
        div_seven_magic = (s32) 0x92490000;
        div_seven_magic = (s32) ((u32) div_seven_magic | 0x2493);
#ifndef NON_MATCHING
        implicit_lo = cycle_value * div_seven_magic;
#endif
        target_color = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)effect)->unk_10))[-1].unk_00;
        div_adjust = (s32) (s16) hold_tick >> 31;
        M2C_READ_MUL_HI(product_result, cycle_value, div_seven_magic);
        cycle_quotient = ((product_result + cycle_value) >> 2) - div_adjust;
        ASM_KEEP_NV(cycle_quotient);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        cycle_value = cycle_value - (cycle_quotient * 7);
        cycle_value = cycle_value + 1;
        cycle_value = (s32) ((u32) cycle_value << 16);
        hold_color = cycle_value >> 16;
        rounded_color = hold_color;
        if (hold_color < 0) {
            rounded_color = hold_color + 3;
        }
        red = (rounded_color >> 2) * 0xC0;
        hold_bits = (hold_color + (s32) ((u32) cycle_value >> 31)) >> 1;
        ((S_818B6AFC_4 *)color_out)->unk_0C.at00.v = red;
        ((S_818B6AFC_3 *)target_color)->unk_0C = red;
        green = ((s16) hold_bits % 2) * 0xC0;
        hold_bits = (s16) (hold_color - (hold_bits * 2));
        ((S_818B6AFC_4 *)color_out)->unk_0C.at01.v = green;
        ((S_818B6AFC_3 *)target_color)->unk_0D = green;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        blue = hold_bits * 0xC0;
        ((S_818B6AFC_4 *)color_out)->unk_0C.at02.v = blue;
        ((S_818B6AFC_3 *)target_color)->unk_0E = blue;
        func_80024154(((S_818B6AFC_0 *)effect)->unk_00, render_arg, ((S_818B6AFC_4 *)color_out)->unk_0C.at00u.v, effect);
        func_80024780();
        return;
    }
    if (frame < 0x30) {
        fade_out_target = ((S_818B6AFC_0 *)effect)->unk_10;
        ((S_818B6AFC_6 *)fade_out_target)->unk_1C = (s32) (((S_818B6AFC_6 *)fade_out_target)->unk_1C | 0x10000000);
        fade_out_tick = ((S_818B6AFC_0 *)effect)->unk_08;
        fade_out_remainder = (s16) fade_out_tick;
        div_seven_magic = (s32) 0x92490000;
        div_seven_magic = (s32) ((u32) div_seven_magic | 0x2493);
#ifndef NON_MATCHING
        implicit_lo = fade_out_remainder * div_seven_magic;
#endif
        target_color = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)effect)->unk_10))[-1].unk_00;
        div_adjust = (s32) (s16) fade_out_tick >> 31;
        M2C_READ_MUL_HI(product_result, fade_out_remainder, div_seven_magic);
        cycle_quotient = ((product_result + fade_out_remainder) >> 2) - div_adjust;
        ASM_KEEP_NV(cycle_quotient);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        fade_out_remainder = fade_out_remainder - (cycle_quotient * 7);
        fade_out_remainder = fade_out_remainder + 1;
        packed_color = (s32) ((u32) fade_out_remainder << 16);
        fade_out_color = packed_color >> 16;
        fade_work = fade_out_color;
        if (fade_out_color < 0) {
            fade_work = fade_out_color + 3;
        }
        fade_out_red = fade_work >> 2;
        fade_out_half = (fade_out_color + (s32) ((u32) packed_color >> 31)) >> 1;
        fade_work = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        ASM_KEEP_NV(fade_work);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        end_frame = 0x30;
        ASM_KEEP_NV(end_frame);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        fade_work = end_frame - fade_work;
        product_result = M2C_MUL_LO(fade_out_red, fade_work << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0C = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        fade_out_green = (s16) fade_out_half % 2;
        packed_channel = (s32) ((u32) (fade_out_color - (fade_out_half * 2)) << 16);
        product_result = M2C_MUL_LO(fade_out_green, (end_frame - (s16) ((S_818B6AFC_0 *)effect)->unk_06) << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0D = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        channel_bit = packed_channel >> 16;
        product_result = M2C_MUL_LO(channel_bit, (end_frame - (s16) ((S_818B6AFC_0 *)effect)->unk_06) << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0E = (s8) (product_result - 0x80);
        ASM_KEEP(product_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        frames_left = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        frames_left = end_frame - frames_left;
        product_result = M2C_MUL_LO(fade_out_red, (frames_left * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at00.v = (s8) product_result;
        frames_left = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        frames_left = end_frame - frames_left;
        product_result = M2C_MUL_LO(fade_out_green, (frames_left * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at01.v = (s8) product_result;
        frames_left = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        frames_left = end_frame - frames_left;
        product_result = M2C_MUL_LO(channel_bit, (frames_left * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at02.v = (s8) product_result;
        func_80024780(fade_out_green, fade_out_color, end_frame, effect);
        return;
    }
    finished_target = ((S_818B6AFC_0 *)effect)->unk_10;
    ((S_818B6AFC_7 *)finished_target)->unk_1C = (s32) (((S_818B6AFC_7 *)finished_target)->unk_1C & 0xEFFFFFFF);
    (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_818B6AFC_0_pre *)effect)[-1].unk_00 | 0x8000);
    D_800814A0 = D_800814A0 | 0x8000;
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

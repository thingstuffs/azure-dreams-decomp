#include "common.h"

typedef struct S_80024A64_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_80024A64_0;   /* arg0 in func_80024A64 */

typedef struct S_80024A64_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024A64_1;   /* arg1 in func_80024A64 */

typedef struct S_80024A64_2 {
    u8 pad_00[0x30];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} S_80024A64_2;   /* sc in func_80024A64 */



extern s32 func_80069EF8(void);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80024790(s32, s32);

/* Builds and draws two eight-segment radial bands around the effect center. */
s32 func_80024A64(S_80024A64_0 *effect, S_80024A64_1 *center, s32 draw_arg) {
    u8 *scratch;
    s32 first_outer_x;
    s32 first_outer_y;
    s32 first_inner_x;
    s32 first_inner_y;
    u16 outer_radius;
    u16 inner_radius;
    s16 jitter_count;
    s16 tip_radius;
    s32 segment;
    s32 angle_step;
    s32 jittered_outer;
    register s32 radial_offset ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    s32 next_segment;
    s32 next_angle;
    s32 jittered_inner;
    s32 raised_z;
    s32 jitter_limit;

    scratch = (u8 *)0x1F800000;
    if (effect->unk_06 < 8) {
        raised_z = center->unk_08 - (effect->unk_06 * 0x180000);
        ((S_80024A64_2 *)scratch)->unk_48 = raised_z;
        ((S_80024A64_2 *)scratch)->unk_38 = raised_z;
        {
            s32 phase_scale = effect->unk_06;
            register s32 inner_scale ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
            s32 outer_scale;
            inner_scale = phase_scale * 2;
            outer_scale = (inner_scale + phase_scale) * 2;
            ASM_USE(inner_scale);   /* MATCH pin: keeps a statement from moving across a call/branch */
            inner_radius = inner_scale;
            outer_radius = outer_scale;
        }
        tip_radius = effect->unk_06 / 2;
        jitter_count = tip_radius + 1;
    } else if (effect->unk_06 < 40) {
        {
            s32 plateau_z = center->unk_08 - (8 * 0x180000);
            ((S_80024A64_2 *)scratch)->unk_48 = plateau_z;
            ((S_80024A64_2 *)scratch)->unk_38 = plateau_z;
        }
        outer_radius = 8 * 6;
        inner_radius = 8 * 2;
        tip_radius = 8 / 2;
        jitter_count = tip_radius + 1;
    } else if (effect->unk_06 < 48) {
        raised_z = center->unk_08 - ((48 - effect->unk_06) * 0x180000);
        ((S_80024A64_2 *)scratch)->unk_48 = raised_z;
        ((S_80024A64_2 *)scratch)->unk_38 = raised_z;
        {
            s32 phase_scale = 48 - effect->unk_06;
            s32 inner_scale;
            register s32 outer_scale ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            inner_scale = phase_scale * 2;
            outer_scale = (inner_scale + phase_scale) * 2;
            inner_radius = inner_scale;
            tip_radius = (47 - effect->unk_06) / 2;
            outer_radius = outer_scale;
            jitter_count = tip_radius + 1;
        }
    } else {
        jitter_count = 0;
        tip_radius = 0;
        inner_radius = 0;
        outer_radius = 0;
    }

    segment = 0;
    jitter_limit = (s16)jitter_count;
    ((S_80024A64_2 *)scratch)->unk_58 = ((S_80024A64_2 *)scratch)->unk_68 = center->unk_08;
    do {
        angle_step = segment * 512;
        radial_offset = func_80069EF8() % jitter_limit;
        {
            s32 wave_x = func_800644B8(effect->unk_0C + angle_step);
            radial_offset = (s16)radial_offset;
            jittered_outer = (s16)outer_radius + radial_offset;
            ((S_80024A64_2 *)scratch)->unk_40 = center->unk_00 +
                (((wave_x >> 4) * jittered_outer) << 8);
        }
        ((S_80024A64_2 *)scratch)->unk_44 = center->unk_04 +
            (((func_80064584(effect->unk_0C + angle_step) >> 4) * jittered_outer) << 8);
        {
            s32 wave_x = func_800644B8(effect->unk_0C + angle_step);
            jittered_inner = (s16)inner_radius + radial_offset;
            ((S_80024A64_2 *)scratch)->unk_50 = center->unk_00 +
                (((wave_x >> 4) * jittered_inner) << 8);
        }
        ((S_80024A64_2 *)scratch)->unk_54 = center->unk_04 +
            (((func_80064584(effect->unk_0C + angle_step) >> 4) * jittered_inner) << 8);
        next_segment = segment + 1;
        next_angle = next_segment * 512;
        ((S_80024A64_2 *)scratch)->unk_30 = ((S_80024A64_2 *)scratch)->unk_60 = center->unk_00 +
            (((func_800644B8(effect->unk_0C + next_angle) >> 4) * (s16)tip_radius) << 8);
        ((S_80024A64_2 *)scratch)->unk_34 = ((S_80024A64_2 *)scratch)->unk_64 = center->unk_04 +
            (((func_80064584(effect->unk_0C + next_angle) >> 4) * (s16)tip_radius) << 8);
        func_80024790((s16)segment, draw_arg);
        segment = next_segment;
    } while (segment < 8);

    segment = 0;
    {
        s32 random_raw = func_80069EF8();
        s32 div5_magic = 0x66666667;
        ASM_USE_NV(div5_magic);   /* MATCH pin: retail immediate-load split depends on it */
        radial_offset = random_raw;
        radial_offset = radial_offset - (radial_offset / 5) * 5;
    }
    {
        s32 wave_x;
        s32 scaled_x;
        s32 outer_x;
        wave_x = func_800644B8(effect->unk_0E);
        scaled_x = wave_x >> 4;
        ASM_KEEP_DEP_NV(radial_offset, scaled_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
        radial_offset = (s16)radial_offset;
        radial_offset = (s16)outer_radius + radial_offset;
        outer_x = center->unk_00 +
            ((scaled_x * radial_offset) << 8);
        ((S_80024A64_2 *)scratch)->unk_30 = outer_x;
        first_outer_x = outer_x;
    }
    {
        s32 outer_y;
        outer_y = center->unk_04 +
            (((func_80064584(effect->unk_0E) >> 4) * radial_offset) << 8);
        ((S_80024A64_2 *)scratch)->unk_34 = outer_y;
        first_outer_y = outer_y;
    }
    {
        s32 wave_x = func_800644B8(effect->unk_0E + 512);
        s32 inner_x;
        inner_x = center->unk_00 +
            (((wave_x >> 4) * (s16)inner_radius) << 8);
        ((S_80024A64_2 *)scratch)->unk_60 = inner_x;
        first_inner_x = inner_x;
    }
    {
        s32 inner_y = center->unk_04 +
            (((func_80064584(effect->unk_0E + 512) >> 4) * (s16)inner_radius) << 8);
        ASM_KEEP_NV(inner_y);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        first_inner_y = inner_y;
        ((S_80024A64_2 *)scratch)->unk_64 = first_inner_y;
    }
    angle_step = 512;
    do {
        ((S_80024A64_2 *)scratch)->unk_40 = ((S_80024A64_2 *)scratch)->unk_30;
        ((S_80024A64_2 *)scratch)->unk_44 = ((S_80024A64_2 *)scratch)->unk_34;
        ((S_80024A64_2 *)scratch)->unk_50 = ((S_80024A64_2 *)scratch)->unk_60;
        ((S_80024A64_2 *)scratch)->unk_54 = ((S_80024A64_2 *)scratch)->unk_64;
        if (segment == 7) {
            ((S_80024A64_2 *)scratch)->unk_30 = first_outer_x;
            ((S_80024A64_2 *)scratch)->unk_34 = first_outer_y;
            ((S_80024A64_2 *)scratch)->unk_60 = first_inner_x;
            ((S_80024A64_2 *)scratch)->unk_64 = first_inner_y;
        } else {
            {
                s32 random_raw = func_80069EF8();
                s32 div5_magic = 0x66666667;
                union {
                    long long full;
                    struct { s32 hi; u32 lo; } half;
                } wide_product;
                s32 quotient;
                radial_offset = random_raw;
                wide_product.full = (long long)radial_offset * div5_magic;
                quotient = (wide_product.half.hi >> 1) - (radial_offset >> 31);
                radial_offset = radial_offset - quotient * 5;
            }
            {
                s32 wave_x = func_800644B8(effect->unk_0E + (segment * 512));
                s32 scaled_x = wave_x >> 4;
                ASM_KEEP_DEP_NV(radial_offset, scaled_x);   /* MATCH pin: retail schedule: same instructions, different order without it */
                radial_offset = (s16)radial_offset;
                radial_offset = (s16)outer_radius + radial_offset;
                ((S_80024A64_2 *)scratch)->unk_30 = center->unk_00 +
                    ((scaled_x * radial_offset) << 8);
            }
            ((S_80024A64_2 *)scratch)->unk_34 = center->unk_04 +
                (((func_80064584(effect->unk_0E + (segment * 512)) >> 4) * radial_offset) << 8);
            ((S_80024A64_2 *)scratch)->unk_60 = center->unk_00 +
                (((func_800644B8(effect->unk_0E + angle_step) >> 4) * (s16)inner_radius) << 8);
            ((S_80024A64_2 *)scratch)->unk_64 = center->unk_04 +
                (((func_80064584(effect->unk_0E + angle_step) >> 4) * (s16)inner_radius) << 8);
        }
        func_80024790((s16)segment, draw_arg);
        segment = segment + 1;
        angle_step = angle_step + 512;
    } while (segment < 8);
    return 0;
}

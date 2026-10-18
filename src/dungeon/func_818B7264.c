#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"

   /* arg0 in draw_two_radial_effect_bands */

   /* arg1 in draw_two_radial_effect_bands */

   /* sc in draw_two_radial_effect_bands */




/* Builds and draws two eight-segment radial bands around the effect center. */
s32 draw_two_radial_effect_bands(B28_818B7264_S_80024A64_0 *effect, B28_818B7264_S_80024A64_1 *center, s32 draw_arg) {
    u8 *scratch;
    s32 first_outer_x;
    s32 first_outer_y;
    s32 first_inner_x;
    s32 first_inner_y;
    u16 outer_radius;
    u16 inner_radius;
    s32 jitter_count;
    s16 tip_radius;
    s32 segment;
    s32 angle_step;
    s32 jittered_outer;
    s32 outer_offset;
    s32 arm_offset;
    s32 arm_radius;
    s32 radial_offset;
    s32 next_segment;
    s32 next_angle;
    s32 jittered_inner;
    s32 jitter_limit;
    s32 scaled;

    scratch = (u8 *)0x1F800000;
    if (effect->unk_06 < 8) {
        s32 growing_z;
        growing_z = center->unk_08 - (effect->unk_06 * 0x180000);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_48 = growing_z;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_38 = growing_z;
        {
            s32 phase_scale = effect->unk_06;
            s32 inner_scale;
            s32 outer_scale;
            inner_scale = phase_scale * 2;
            outer_scale = (inner_scale + phase_scale) * 2;
            outer_radius = outer_scale;
            inner_radius = inner_scale;
        }
        tip_radius = effect->unk_06 / 2;
        jitter_count = tip_radius + 1;
    } else if (effect->unk_06 < 40) {
        {
            s32 plateau_z = center->unk_08 - (8 * 0x180000);
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_48 = plateau_z;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_38 = plateau_z;
        }
        outer_radius = 8 * 6;
        inner_radius = 8 * 2;
        tip_radius = 8 / 2;
        jitter_count = tip_radius + 1;
    } else if (effect->unk_06 < 48) {
        s32 fading_z;
        jitter_count = 48;
        fading_z = center->unk_08 - ((jitter_count - effect->unk_06) * 0x180000);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_48 = fading_z;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_38 = fading_z;
        {
            s32 inner_scale;
            s32 tip_value;
            jitter_count -= effect->unk_06;
            inner_scale = jitter_count * 2;
            jitter_count = inner_scale - -jitter_count;
            jitter_count *= 2;
            inner_radius = inner_scale;
            tip_value = (47 - effect->unk_06) / 2;
            outer_radius = jitter_count;
            tip_radius = tip_value;
            jitter_count = tip_value + 1;
        }
    } else {
        jitter_count = 0;
        tip_radius = 0;
        inner_radius = 0;
        outer_radius = 0;
    }

    segment = 0;
    jitter_limit = (s16)jitter_count;
    ((B28_818B7264_S_80024A64_2 *)scratch)->unk_58 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_68 = center->unk_08;
    do {
        angle_step = segment * 512;
        radial_offset = func_80069EF8() % jitter_limit;
        {
            s32 wave_x = func_800644B8(effect->unk_0C + angle_step);
            radial_offset = (s16)radial_offset;
            jittered_outer = (s16)outer_radius + radial_offset;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_40 = center->unk_00 +
                (((wave_x >> 4) * jittered_outer) << 8);
        }
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_44 = center->unk_04 +
            (((func_80064584(effect->unk_0C + angle_step) >> 4) * jittered_outer) << 8);
        {
            s32 wave_x = func_800644B8(effect->unk_0C + angle_step);
            jittered_inner = (s16)inner_radius + radial_offset;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_50 = center->unk_00 +
                (((wave_x >> 4) * jittered_inner) << 8);
        }
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_54 = center->unk_04 +
            (((func_80064584(effect->unk_0C + angle_step) >> 4) * jittered_inner) << 8);
        next_segment = segment + 1;
        next_angle = next_segment * 512;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = center->unk_00 +
            (((func_800644B8(effect->unk_0C + next_angle) >> 4) * (s16)tip_radius) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = center->unk_04 +
            (((func_80064584(effect->unk_0C + next_angle) >> 4) * (s16)tip_radius) << 8);
        func_80024790((s16)segment, draw_arg);
        segment = next_segment;
    } while (segment < 8);

    segment = 0;
    {
        s32 random_raw = func_80069EF8();
        s32 div5_magic = 0x66666667;
        union {
            long long full;
            struct { s32 hi; u32 lo; } half;
        } wide_product;
        s32 quotient;
        outer_offset = random_raw;
        wide_product.full = (long long)outer_offset * div5_magic;
        quotient = (wide_product.half.hi >> 1) - (outer_offset >> 31);
        outer_offset = outer_offset - quotient * 5;
    }
    {
        s32 wave_x;
        s32 scaled_x;
        s32 outer_x;
        wave_x = func_800644B8(effect->unk_0E);
        outer_x = center->unk_00 +
            (((wave_x >> 4) * ((s16)outer_radius + (s16)outer_offset)) << 8);
        outer_offset = (s16)outer_radius + (s16)outer_offset;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = outer_x;
        first_outer_x = outer_x;
    }
    {
        s32 outer_y;
        outer_y = center->unk_04 +
            (((func_80064584(effect->unk_0E) >> 4) * outer_offset) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = outer_y;
        first_outer_y = outer_y;
    }
    {
        s32 wave_x = func_800644B8(effect->unk_0E + 512);
        s32 inner_x;
        inner_x = center->unk_00 +
            (((wave_x >> 4) * (s16)inner_radius) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = inner_x;
        first_inner_x = inner_x;
    }
    {
        s32 inner_y = center->unk_04 +
            (((func_80064584(effect->unk_0E + 512) >> 4) * (s16)inner_radius) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = inner_y;
        first_inner_y = inner_y;
    }
    angle_step = 512;
    do {
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_40 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_44 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_50 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_54 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64;
        if (segment == 7) {
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = first_outer_x;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = first_outer_y;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = first_inner_x;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = first_inner_y;
        } else {
            {
                s32 random_raw = func_80069EF8();
                s32 div5_magic = 0x66666667;
                union {
                    long long full;
                    struct { s32 hi; u32 lo; } half;
                } wide_product;
                s32 quotient;
                arm_offset = random_raw;
                wide_product.full = (long long)arm_offset * div5_magic;
                quotient = (wide_product.half.hi >> 1) - (arm_offset >> 31);
                arm_offset = arm_offset - quotient * 5;
            }
            {
                scaled = func_800644B8(effect->unk_0E + (segment * 512)) >> 4;
                arm_radius = (s16)outer_radius + (s16)arm_offset;
                ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = center->unk_00 +
                    ((scaled * arm_radius) << 8);
            }
            scaled = func_80064584(effect->unk_0E + (segment * 512)) >> 4;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = center->unk_04 +
                ((scaled * arm_radius) << 8);
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = center->unk_00 +
                (((func_800644B8(effect->unk_0E + angle_step) >> 4) * (s16)inner_radius) << 8);
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = center->unk_04 +
                (((func_80064584(effect->unk_0E + angle_step) >> 4) * (s16)inner_radius) << 8);
        }
        func_80024790((s16)segment, draw_arg);
        segment = segment + 1;
        angle_step = angle_step + 512;
    } while (segment < 8);
    return 0;
}

#include "common.h"
#include "sdk/libgte.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"

typedef struct {
    s16 u0[2];
    s16 type;
    s16 index;
    s16 add;
    s16 scale0;
    s16 step;
    s16 u14[3];
    s16 scale10;
    s16 scale11;
    s16 u24[23];
    s16 f35;
    s16 f36;
    s16 u37[3];
    s16 f40;
    s16 f41;
    s16 f42;
    s16 u43[22];
    s16 f65;
    s16 f66;
    s16 u67[3];
    s16 f70;
    s16 f71;
    s16 f72;
} Record;

extern void func_80024770(s32, s32, s32);
extern void fade_scene_tile_after_completion_flag(s32, s32, s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */

/* Builds scaled vertices and submits a shaded strip using scratchpad storage. */
s32 draw_shaded_rotating_vertex_strip(Record *record) {
    register s32 shade_step = 0;
    RadialBandQuadScratch *scratch;
    s32 upper_color;
    register s32 lower_color;
    s32 segment;
    u32 prev_upper_color;
    s32 lower_shade;
    s32 upper_shade;

    scratch = RADIAL_BAND_SCRATCH;

    switch (record->type) {
    case 0:
    {
        s32 index = record->index;
        s32 index_work;

        index_work = (index << 2) + index;
        shade_step = index_work << 18;
        break;
    }
    case 1:
        shade_step = 0xA0 << 16;
        break;
    case 2:
        shade_step = 0xA0 << 16;
        break;
    case 3:
    {
        s16 shade_base = record->index;
        s32 index_offset;

        index_offset = (shade_base << 2) + shade_base;
        index_offset <<= 2;
        shade_step = ((s32)(160 - index_offset)) << 16;
        break;
    }
    default:
        shade_step &= 0xffff;
        break;
    }
shade:
    shade_step /= 29;

    {
        s32 scale;
        s32 scaled_coord;
        s32 fixed_coord;
        s32 trig_value;

        trig_value = rsin(record->f40 + record->add);
        scale = record->scale10;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        scratch->positions[0].vx = fixed_coord;

        trig_value = rsin(record->f41 + record->add);
        scale = record->scale11;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        scratch->positions[1].vx = fixed_coord;

        trig_value = rsin(record->f35 + record->add);
        scale = record->scale0;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        scratch->positions[2].vx = fixed_coord;

        trig_value = rcos(record->f40 + record->add);
        scale = record->scale10;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        scratch->positions[0].vy = fixed_coord;

        trig_value = rcos(record->f41 + record->add);
        scale = record->scale11;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        scratch->positions[1].vy = fixed_coord;

        {

            lower_color = record->f35 + record->add;
            segment = 0;
            trig_value = rcos(lower_color);
        }
        {
            s32 intensity;
            s32 color_work;
            s32 shade_work;
            s32 end_color;

            shade_work = shade_step * 24;
            intensity = ((shade_work - shade_step) >> 16) & 0xff;
            color_work = intensity << 8;
            color_work += intensity;
            color_work <<= 8;
            lower_color = color_work + intensity;

            fixed_coord = trig_value >> 4;

            intensity = shade_step << 3;
            intensity -= shade_step;
            intensity <<= 2;
            intensity += shade_step;
            color_work = record->scale0;
            intensity >>= 16;
            scaled_coord = fixed_coord * color_work;
            intensity &= 0xff;

            shade_work >>= 16;
            shade_work &= 0xff;
            prev_upper_color = intensity * 0x10101;

            fixed_coord = scaled_coord << 8;
            scratch->positions[2].vy = fixed_coord;

            scratch->positions[0].vz = record->f70 << 16;
            scratch->positions[1].vz = record->f71 << 16;
            end_color = prev_upper_color;
            scratch->positions[2].vz = record->f65 << 16;
            func_80024770(shade_work * 0x10101, lower_color, end_color);
            upper_color = end_color;
        }
    }

    scratch->positions[3].vx = scratch->positions[2].vx;
    scratch->positions[3].vy = scratch->positions[2].vy;
    scratch->positions[3].vz = scratch->positions[2].vz;
    for (; segment < 23; segment++) {
        s32 scaled_coord;
        s32 prev_lower_color;
        s32 saved_upper_color;
        s32 last_trig_value;
        s32 last_scaled_coord;
        s32 prev_z;

        scratch->positions[0].vx = scratch->positions[1].vx;
        scaled_coord = (rsin(((s16 *)record)[segment + 42] + record->add) >> 4) * ((s16 *)record)[segment + 12];
        scratch->positions[2].vx = scratch->positions[3].vx;
        scratch->positions[1].vx = scaled_coord << 8;
        scaled_coord = (rsin(((s16 *)record)[segment + 36] + record->add) >> 4) * ((s16 *)record)[segment + 6];
        scratch->positions[0].vy = scratch->positions[1].vy;
        scratch->positions[3].vx = scaled_coord << 8;
        scaled_coord = (rcos(((s16 *)record)[segment + 42] + record->add) >> 4) * ((s16 *)record)[segment + 12];
        scratch->positions[2].vy = scratch->positions[3].vy;
        scratch->positions[1].vy = scaled_coord << 8;
        last_trig_value = rcos(((s16 *)record)[segment + 36] + record->add);

        lower_shade = (22 - segment) * shade_step;
        upper_shade = (28 - segment) * shade_step;
        prev_upper_color = upper_color;
        prev_lower_color = lower_color;
        saved_upper_color = prev_upper_color;
        last_scaled_coord = (last_trig_value >> 4) * ((s16 *)record)[segment + 6];
        scratch->positions[0].vz = scratch->positions[1].vz;
        lower_color = (((lower_shade >> 16) & 0xff) * 0x10101);
        upper_color = (((upper_shade >> 16) & 0xff) * 0x10101);
        prev_z = scratch->positions[3].vz;
        scratch->positions[3].vy = last_scaled_coord << 8;
        scratch->positions[1].vz = ((s16 *)record)[segment + 72] << 16;
        scratch->positions[2].vz = prev_z;
        scratch->positions[3].vz = ((s16 *)record)[segment + 66] << 16;
        fade_scene_tile_after_completion_flag(prev_lower_color, lower_color, saved_upper_color, upper_color);
    }

    scratch->positions[0].vx = scratch->positions[1].vx;
    scratch->positions[1].vx = scratch->positions[3].vx;
    scratch->positions[0].vy = scratch->positions[1].vy;
    scratch->positions[1].vy = scratch->positions[3].vy;
    scratch->positions[0].vz = scratch->positions[1].vz;
    scratch->positions[1].vz = scratch->positions[3].vz;
    func_80024770(lower_color, upper_color, prev_upper_color);
    return 0;
}

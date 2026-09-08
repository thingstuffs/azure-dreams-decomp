#include "common.h"

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

extern s32 func_80024E38(void) __attribute__((noreturn));
extern void func_80024770(s32, s32, s32);
extern void func_80024A30(s32, s32, s32, s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);

/* Builds scaled vertices and submits a shaded strip using scratchpad storage. */
s32 func_81977584(Record *record) {
    register s32 shade_step = 0;
    register s16 *sample;
    s32 *vertices;
    s32 upper_color;
    register s32 lower_color;
    s32 segment;
    register s32 prev_upper_color ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 lower_shade;
    s32 upper_shade;

    vertices = (s32 *)0x1F800000;

    if (record->type == 1) {
        goto type_1_or_2;
    }
    if (record->type >= 2) {
        goto type_ge_2;
    }
    if (record->type == 0) {
        goto type_0;
    }
    ASM_KEEP(shade_step);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    shade_step &= 0xffff;
    ASM_TAILSLOT_PIN(shade_step);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024E38();

type_ge_2:
    if (record->type == 2) {
        goto type_1_or_2;
    }
    if (record->type == 3) {
        goto type_3;
    }
    ASM_KEEP(shade_step);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    shade_step &= 0xffff;
    ASM_TAILSLOT_PIN(shade_step);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024E38();

type_0:
    {
        s32 index = record->index;
        s32 index_work;

        index_work = (index << 2) + index;
        shade_step = index_work << 18;
        ASM_TAILSLOT_PIN(shade_step);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024E38();
    }

type_1_or_2:
    shade_step = 0xA0 << 16;
    ASM_TAILSLOT_PIN(shade_step);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    func_80024E38();

type_3:
    {
        s32 shade_base = record->index;
        register s32 index_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        ASM_KEEP_NV(shade_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        index_offset = (shade_base << 2) + shade_base;
        index_offset <<= 2;
        shade_base = 160 - index_offset;
        shade_step = shade_base << 16;
    }
    shade_step /= 29;

    {
        s32 scale;
        s32 scaled_coord;
        s32 fixed_coord;
        s32 trig_value;

        trig_value = func_800644B8(record->f40 + record->add);
        scale = record->scale10;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        vertices[12] = fixed_coord;

        trig_value = func_800644B8(record->f41 + record->add);
        scale = record->scale11;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        vertices[16] = fixed_coord;

        trig_value = func_800644B8(record->f35 + record->add);
        scale = record->scale0;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        vertices[20] = fixed_coord;

        trig_value = func_80064584(record->f40 + record->add);
        scale = record->scale10;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        vertices[13] = fixed_coord;

        trig_value = func_80064584(record->f41 + record->add);
        scale = record->scale11;
        scaled_coord = (trig_value >> 4) * scale;
        fixed_coord = scaled_coord << 8;
        vertices[17] = fixed_coord;

        {
            s32 angle;

            angle = record->f35 + record->add;
            segment = 0;
            trig_value = func_80064584(angle);
        }
        {
            register s32 color_pair ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 intensity;
            register s32 color_work ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 shade_work ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 end_color ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            shade_work = (shade_step * 3) << 3;
            intensity = ((shade_work - shade_step) >> 16) & 0xff;
            ASM_KEEP_NV(intensity);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            color_work = (intensity << 8) + intensity;
            lower_color = (color_work << 8) + intensity;
            ASM_KEEP_NV(lower_color);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            trig_value >>= 4;
            ASM_KEEP_NV(trig_value);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

            intensity = shade_step << 3;
            intensity -= shade_step;
            intensity <<= 2;
            intensity += shade_step;
            color_work = record->scale0;
            intensity >>= 16;
            scaled_coord = trig_value * color_work;
            ASM_KEEP(intensity);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            intensity &= 0xff;
            ASM_KEEP_NV(intensity);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            shade_work = (shade_work >> 16) & 0xff;
            ASM_KEEP_NV(shade_work);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            color_pair = (intensity << 8) + intensity;
            prev_upper_color = (color_pair << 8) + intensity;

            color_work = (shade_work << 8) + shade_work;
            color_work = (color_work << 8) | shade_work;

            fixed_coord = scaled_coord << 8;
            vertices[21] = fixed_coord;

            vertices[14] = record->f70 << 16;
            shade_work = lower_color;
            vertices[18] = record->f71 << 16;
            end_color = prev_upper_color;
            vertices[22] = record->f65 << 16;
            upper_color = end_color;
            func_80024770(color_work, shade_work, end_color);
        }
    }

    sample = (s16 *)record;
    vertices[24] = vertices[20];
    vertices[25] = vertices[21];
    vertices[26] = vertices[22];
    do {
        s32 scaled_coord;
        s32 prev_lower_color;
        s32 saved_upper_color;
        s32 last_trig_value;
        s32 last_scaled_coord;
        s32 prev_z;

        ASM_KEEP_NV(sample);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        vertices[12] = vertices[16];
        scaled_coord = (func_800644B8(sample[42] + record->add) >> 4) * sample[12];
        vertices[20] = vertices[24];
        vertices[16] = scaled_coord << 8;
        scaled_coord = (func_800644B8(sample[36] + record->add) >> 4) * sample[6];
        vertices[13] = vertices[17];
        vertices[24] = scaled_coord << 8;
        scaled_coord = (func_80064584(sample[42] + record->add) >> 4) * sample[12];
        ASM_KEEP_NV(scaled_coord);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        vertices[21] = vertices[25];
        vertices[17] = scaled_coord << 8;
        last_trig_value = func_80064584(sample[36] + record->add);

        lower_shade = (22 - segment) * shade_step;
        upper_shade = (28 - segment) * shade_step;
        prev_upper_color = upper_color;
        prev_lower_color = lower_color;
        saved_upper_color = prev_upper_color;
        last_scaled_coord = (last_trig_value >> 4) * sample[6];
        vertices[14] = vertices[18];
        lower_color = (((lower_shade >> 16) & 0xff) * 0x10101);
        upper_color = (((upper_shade >> 16) & 0xff) * 0x10101);
        prev_z = vertices[26];
        vertices[25] = last_scaled_coord << 8;
        vertices[18] = sample[72] << 16;
        vertices[22] = prev_z;
        vertices[26] = sample[66] << 16;
        func_80024A30(prev_lower_color, lower_color, saved_upper_color, upper_color);
        sample++;
        ++segment;
    } while (segment < 23);

    vertices[12] = vertices[16];
    vertices[16] = vertices[24];
    vertices[13] = vertices[17];
    vertices[17] = vertices[25];
    vertices[14] = vertices[18];
    vertices[18] = vertices[26];
    func_80024770(lower_color, upper_color, prev_upper_color);
    return 0;
}

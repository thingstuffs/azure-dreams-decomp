#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_818B6AFC_0_pre {
    u16 unk_00;
} S_818B6AFC_0_pre;   /* the 0x2 bytes before arg0 in func_800242FC, addressed as arg0[-1] */

typedef struct S_818B6AFC_0 {
    void * unk_00;
    u8 pad_04[0x2];
    u16 unk_06;
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
    u16 unk_0E;
    void * unk_10;
} S_818B6AFC_0;   /* arg0 in func_800242FC */

typedef struct S_818B6AFC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818B6AFC_1;   /* temp_v1 in func_800242FC */

typedef struct S_818B6AFC_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_2;   /* temp_a0 in func_800242FC */

typedef struct S_818B6AFC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_818B6AFC_3;   /* temp_t0 in func_800242FC */

typedef struct S_818B6AFC_4 {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_818B6AFC_4;   /* arg2 in func_800242FC */

typedef struct S_818B6AFC_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_5;   /* temp_a0_4 in func_800242FC */

typedef struct S_818B6AFC_6 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_6;   /* temp_a0_7 in func_800242FC */

typedef struct S_818B6AFC_7 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_818B6AFC_7;   /* temp_a0_10 in func_800242FC */

typedef struct S_818B6AFC_8_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_818B6AFC_8_pre;   /* the 0x14 bytes before ((S_818B6AFC_0 *)arg0)->unk_10 in func_800242FC, addressed as ((S_818B6AFC_0 *)arg0)->unk_10[-1] */


M2C_UNK func_80024154();

/* Cycle through seven colors with fade-in and fade-out, then mark the effect finished. */
void func_800242FC(void *effect_data, M2C_UNK render_arg, void *color_out) {
    s32 fade_in_color;
    s16 fade_in_green;
    s32 hold_color;
    s32 fade_out_color;
    s16 fade_out_green;
    s16 frame;
    s32 fade_in_blue;
    s32 fade_work;
    s32 rounded_color;
    s32 channel_bit;
    register s32 fade_out_red ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 fade_in_half;
    s32 fade_out_half;
    s32 packed_channel;
    s32 cycle_quotient;
    s32 packed_color;
    s32 frames_left;
    s32 hold_blue;
    s32 hold_half;
    s32 cycle_value;
    s16 fade_in_cycle;
    s16 hold_cycle;
    s16 fade_out_cycle;
    s32 fade_in_tick;
    u16 hold_tick;
    u16 fade_out_tick;
    s32 product_result;
    s8 red;
    s8 green;
    s8 blue;
    void *fade_in_target;
    void *finished_target;
    void *hold_target;
    void *fade_out_target;
    void *target_color;
    void *owner;
    void *render_owner;
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
        target_color = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)effect)->unk_10))[-1].unk_00;
        fade_in_cycle = (s16) fade_in_tick % 7 + 1;
        packed_channel = (s32) ((u32) fade_in_cycle << 16);
        fade_in_color = packed_channel >> 16;
        fade_in_tick = fade_in_color;
        if (fade_in_color < 0) {
            fade_in_tick = fade_in_color + 3;
        }
        channel_bit = fade_in_tick >> 2;
        product_result = channel_bit * ((s16) ((S_818B6AFC_0 *)effect)->unk_06 << 3);
        fade_in_half = (fade_in_color + (s32) ((u32) packed_channel >> 31)) >> 1;
        ((S_818B6AFC_3 *)target_color)->unk_0C = (s8) (product_result - 0x80);
        fade_in_green = (s16) fade_in_half % 2;
        packed_channel = fade_in_half;
        packed_channel *= 2;
        packed_channel = fade_in_color - packed_channel;
        packed_channel = (u32)packed_channel << 16;
        product_result = fade_in_green * ((s16) ((S_818B6AFC_0 *)effect)->unk_06 << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0D = (s8) (product_result - 0x80);
        fade_in_blue = packed_channel >> 16;
        product_result = fade_in_blue * ((s16) ((S_818B6AFC_0 *)effect)->unk_06 << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0E = (s8) (product_result - 0x80);
        product_result = channel_bit * (((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at00.v = (s8) product_result;
        product_result = fade_in_green * (((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at01.v = (s8) product_result;
        product_result = fade_in_blue * (((s16) ((S_818B6AFC_0 *)effect)->unk_06 * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at02.v = (s8) product_result;
        return;
    }
    if (frame < 0x28) {
        hold_target = ((S_818B6AFC_0 *)effect)->unk_10;
        ((S_818B6AFC_5 *)hold_target)->unk_1C = (s32) (((S_818B6AFC_5 *)hold_target)->unk_1C | 0x10000000);
        hold_tick = ((S_818B6AFC_0 *)effect)->unk_08;
        target_color = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)effect)->unk_10))[-1].unk_00;
        hold_cycle = (s16) hold_tick % 7 + 1;
        cycle_value = (s32) ((u32) hold_cycle << 16);
        hold_color = cycle_value >> 16;
        rounded_color = hold_color;
        red = (rounded_color / 4) * 0xC0;
        hold_half = (hold_color + (s32) ((u32) cycle_value >> 31)) >> 1;
        ((S_818B6AFC_4 *)color_out)->unk_0C.at00.v = red;
        ((S_818B6AFC_3 *)target_color)->unk_0C = red;
        green = ((s16) hold_half % 2) * 0xC0;
        hold_blue = (s16) (hold_color - (hold_half * 2));
        ((S_818B6AFC_4 *)color_out)->unk_0C.at01.v = green;
        (*(s8 *)((u8 *)target_color + 0xD)) = green;
        blue = hold_blue * 0xC0;
        ((S_818B6AFC_4 *)color_out)->unk_0C.at02.v = blue;
        ((S_818B6AFC_3 *)target_color)->unk_0E = blue;
        render_owner = ((S_818B6AFC_0 *)effect)->unk_00;
        func_80024154(render_owner, render_arg, ((S_818B6AFC_4 *)color_out)->unk_0C.at00u.v, effect);
        return;
    }
    if (frame < 0x30) {
        fade_out_target = ((S_818B6AFC_0 *)effect)->unk_10;
        ((S_818B6AFC_6 *)fade_out_target)->unk_1C = (s32) (((S_818B6AFC_6 *)fade_out_target)->unk_1C | 0x10000000);
        fade_out_tick = ((S_818B6AFC_0 *)effect)->unk_08;
        target_color = ((S_818B6AFC_8_pre *)(((S_818B6AFC_0 *)effect)->unk_10))[-1].unk_00;
        fade_out_cycle = (s16) fade_out_tick % 7 + 1;
        packed_color = (s32) ((u32) fade_out_cycle << 16);
        fade_out_color = packed_color >> 16;
        fade_work = fade_out_color;
        if (fade_out_color < 0) {
            fade_work = fade_out_color + 3;
        }
        fade_out_red = fade_work >> 2;
        fade_work = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        fade_in_color = 0x30;
        fade_work = fade_in_color - fade_work;
        fade_out_half = (fade_out_color + (s32) ((u32) packed_color >> 31)) >> 1;
        product_result = fade_out_red * (fade_work << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0C = (s8) (product_result - 0x80);
        fade_out_green = (s16) fade_out_half % 2;
        packed_channel = (s32) ((u32) (fade_out_color - (fade_out_half * 2)) << 16);
        product_result = fade_out_green * ((fade_in_color - (s16) ((S_818B6AFC_0 *)effect)->unk_06) << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0D = (s8) (product_result - 0x80);
        channel_bit = packed_channel >> 16;
        product_result = channel_bit * ((fade_in_color - (s16) ((S_818B6AFC_0 *)effect)->unk_06) << 3);
        ((S_818B6AFC_3 *)target_color)->unk_0E = (s8) (product_result - 0x80);
        frames_left = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        frames_left = fade_in_color - frames_left;
        product_result = fade_out_red * ((frames_left * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at00.v = (s8) product_result;
        frames_left = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        frames_left = fade_in_color - frames_left;
        product_result = fade_out_green * ((frames_left * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at01.v = (s8) product_result;
        frames_left = (s16) ((S_818B6AFC_0 *)effect)->unk_06;
        frames_left = fade_in_color - frames_left;
        product_result = channel_bit * ((frames_left * 3) << 3);
        ((S_818B6AFC_4 *)color_out)->unk_0C.at02.v = (s8) product_result;
        return;
    }
    finished_target = ((S_818B6AFC_0 *)effect)->unk_10;
    ((S_818B6AFC_7 *)finished_target)->unk_1C = (s32) (((S_818B6AFC_7 *)finished_target)->unk_1C & 0xEFFFFFFF);
    (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_818B6AFC_0_pre *)effect)[-1].unk_00 | 0x8000);
    objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
}

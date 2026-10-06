#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct FxOwner {
    u8 pad_00[0x14];
    u16 count;
} FxOwner;

typedef struct FxEffectPre {
    u16 flags;   /* the u16 just before the effect, addressed as effect[-1] */
} FxEffectPre;

typedef struct FxRgb {
    u8 pad_00[0xC];
    s8 r;
    s8 g;
    s8 b;
} FxRgb;

typedef struct FxColorOut {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } rgb;   /* overlapping accesses */
} FxColorOut;

typedef struct FxTarget {
    u8 pad_00[0x1C];
    s32 flags;
} FxTarget;

typedef struct FxTargetPre {
    void *color;
    u8 pad_04[0x10];
} FxTargetPre;   /* the 0x14 bytes before the target, addressed as target[-1] */

typedef struct FxEffect {
    FxOwner *owner;
    u8 pad_04[0x2];
    u16 frame;
    u16 tick;
    u8 pad_0A[0x2];
    u16 scroll_u;
    u16 scroll_v;
    FxTarget *target;
} FxEffect;

M2C_UNK func_80024154();

/* Cycle through seven colors with fade-in and fade-out, then mark the effect finished. */
void func_800242FC(FxEffect *effect, M2C_UNK render_arg, FxColorOut *color_out) {
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
    FxRgb *target_color;
    FxOwner *owner;
    FxOwner *render_owner;

    owner = effect->owner;
    owner->count += 1;
    effect->frame += 1;
    effect->tick += 1;
    effect->scroll_u += 0x80;
    effect->scroll_v += 0x80;
    frame = effect->frame;
    if (frame < 8) {
        effect->target->flags |= 0x10000000;
        fade_in_tick = effect->tick;
        target_color = ((FxTargetPre *)(effect->target))[-1].color;
        fade_in_cycle = (s16) fade_in_tick % 7 + 1;
        packed_channel = (s32) ((u32) fade_in_cycle << 16);
        fade_in_color = packed_channel >> 16;
        fade_in_tick = fade_in_color;
        if (fade_in_color < 0) {
            fade_in_tick = fade_in_color + 3;
        }
        channel_bit = fade_in_tick >> 2;
        product_result = channel_bit * ((s16) effect->frame << 3);
        fade_in_half = (fade_in_color + (s32) ((u32) packed_channel >> 31)) >> 1;
        target_color->r = (s8) (product_result - 0x80);
        fade_in_green = (s16) fade_in_half % 2;
        packed_channel = fade_in_half;
        packed_channel *= 2;
        packed_channel = fade_in_color - packed_channel;
        packed_channel = (u32)packed_channel << 16;
        product_result = fade_in_green * ((s16) effect->frame << 3);
        target_color->g = (s8) (product_result - 0x80);
        fade_in_blue = packed_channel >> 16;
        product_result = fade_in_blue * ((s16) effect->frame << 3);
        target_color->b = (s8) (product_result - 0x80);
        product_result = channel_bit * (((s16) effect->frame * 3) << 3);
        color_out->rgb.at00.v = (s8) product_result;
        product_result = fade_in_green * (((s16) effect->frame * 3) << 3);
        color_out->rgb.at01.v = (s8) product_result;
        product_result = fade_in_blue * (((s16) effect->frame * 3) << 3);
        color_out->rgb.at02.v = (s8) product_result;
        return;
    }
    if (frame < 0x28) {
        effect->target->flags |= 0x10000000;
        hold_tick = effect->tick;
        target_color = ((FxTargetPre *)(effect->target))[-1].color;
        hold_cycle = (s16) hold_tick % 7 + 1;
        cycle_value = (s32) ((u32) hold_cycle << 16);
        hold_color = cycle_value >> 16;
        rounded_color = hold_color;
        red = (rounded_color / 4) * 0xC0;
        hold_half = (hold_color + (s32) ((u32) cycle_value >> 31)) >> 1;
        color_out->rgb.at00.v = red;
        target_color->r = red;
        green = ((s16) hold_half % 2) * 0xC0;
        hold_blue = (s16) (hold_color - (hold_half * 2));
        color_out->rgb.at01.v = green;
        target_color->g = green;
        blue = hold_blue * 0xC0;
        color_out->rgb.at02.v = blue;
        target_color->b = blue;
        render_owner = effect->owner;
        func_80024154(render_owner, render_arg, color_out->rgb.at00u.v, effect);
        return;
    }
    if (frame < 0x30) {
        effect->target->flags |= 0x10000000;
        fade_out_tick = effect->tick;
        target_color = ((FxTargetPre *)(effect->target))[-1].color;
        fade_out_cycle = (s16) fade_out_tick % 7 + 1;
        packed_color = (s32) ((u32) fade_out_cycle << 16);
        fade_out_color = packed_color >> 16;
        fade_work = fade_out_color;
        if (fade_out_color < 0) {
            fade_work = fade_out_color + 3;
        }
        fade_out_red = fade_work >> 2;
        fade_work = (s16) effect->frame;
        fade_in_color = 0x30;
        fade_work = fade_in_color - fade_work;
        fade_out_half = (fade_out_color + (s32) ((u32) packed_color >> 31)) >> 1;
        product_result = fade_out_red * (fade_work << 3);
        target_color->r = (s8) (product_result - 0x80);
        fade_out_green = (s16) fade_out_half % 2;
        packed_channel = (s32) ((u32) (fade_out_color - (fade_out_half * 2)) << 16);
        product_result = fade_out_green * ((fade_in_color - (s16) effect->frame) << 3);
        target_color->g = (s8) (product_result - 0x80);
        channel_bit = packed_channel >> 16;
        product_result = channel_bit * ((fade_in_color - (s16) effect->frame) << 3);
        target_color->b = (s8) (product_result - 0x80);
        frames_left = (s16) effect->frame;
        frames_left = fade_in_color - frames_left;
        product_result = fade_out_red * ((frames_left * 3) << 3);
        color_out->rgb.at00.v = (s8) product_result;
        frames_left = (s16) effect->frame;
        frames_left = fade_in_color - frames_left;
        product_result = fade_out_green * ((frames_left * 3) << 3);
        color_out->rgb.at01.v = (s8) product_result;
        frames_left = (s16) effect->frame;
        frames_left = fade_in_color - frames_left;
        product_result = channel_bit * ((frames_left * 3) << 3);
        color_out->rgb.at02.v = (s8) product_result;
        return;
    }
    effect->target->flags &= 0xEFFFFFFF;
    ((FxEffectPre *)effect)[-1].flags |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}

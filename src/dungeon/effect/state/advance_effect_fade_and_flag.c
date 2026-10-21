#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800B63A8_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B63A8_0;   /* arg1 in advance_effect_fade_and_flag */

typedef struct S_800B63A8_1_pre {
    u16 unk_00;
} S_800B63A8_1_pre;   /* the 0x2 bytes before arg0 in advance_effect_fade_and_flag, addressed as arg0[-1] */

typedef struct S_800B63A8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x2];
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    u8 unk_14;
    u8 pad_15[0x1];
    u8 unk_16;
    u8 pad_17[0x1];
    u8 unk_18;
} S_800B63A8_1;   /* arg0 in advance_effect_fade_and_flag */

extern void advance_sprite_animation_and_textures(void *entity);            /* extern */

/* Advance effect motion, fade its color, and flag it when its lifetime expires. */
void advance_effect_fade_and_flag(void *effect, void *motion, void *primitive) {
    s32 velocity_y;
    s32 velocity_z;
    s32 accel_z_step;
    u16 life_left;
    u8 faded_red;
    u8 faded_green;
    u8 faded_blue;
    u8 red;
    u8 green;
    u8 blue;

    ((S_800B63A8_0 *)motion)->unk_0C = (s32) (((S_800B63A8_0 *)motion)->unk_0C + ((S_800B63A8_1 *)effect)->unk_00);
    ((S_800B63A8_0 *)motion)->unk_10 = (s32) (((S_800B63A8_0 *)motion)->unk_10 + ((S_800B63A8_1 *)effect)->unk_04);
    accel_z_step = ((S_800B63A8_1 *)effect)->unk_08 * ((S_800B63A8_1 *)effect)->unk_10;
    ((S_800B63A8_0 *)motion)->unk_14 = (s32) (((S_800B63A8_0 *)motion)->unk_14 + accel_z_step);
    ((S_800B63A8_1 *)effect)->unk_10 = (s16) ((u16) ((S_800B63A8_1 *)effect)->unk_10 + 1);
    velocity_y = ((S_800B63A8_0 *)motion)->unk_10;
    velocity_z = ((S_800B63A8_0 *)motion)->unk_14;
    ((S_800B63A8_0 *)motion)->unk_00 = (s32) (((S_800B63A8_0 *)motion)->unk_00 + ((S_800B63A8_0 *)motion)->unk_0C);
    ((S_800B63A8_0 *)motion)->unk_04 = (s32) (((S_800B63A8_0 *)motion)->unk_04 + velocity_y);
    ((S_800B63A8_0 *)motion)->unk_08 = (s32) (((S_800B63A8_0 *)motion)->unk_08 + velocity_z);
    advance_sprite_animation_and_textures(primitive);
    red = ((SpriteFrameState *)primitive)->color.c.r;
    if (red != 0) {
        faded_red = red - ((S_800B63A8_1 *)effect)->unk_14;
        ((SpriteFrameState *)primitive)->color.c.r = faded_red;
        if ((u32) (faded_red & 0xFF) >= 0x81U) {
            ((SpriteFrameState *)primitive)->color.c.r = 0x80U;
        }
    }
    green = ((SpriteFrameState *)primitive)->color.c.g;
    if (green != 0) {
        faded_green = green - ((S_800B63A8_1 *)effect)->unk_16;
        ((SpriteFrameState *)primitive)->color.c.g = faded_green;
        if ((u32) (faded_green & 0xFF) >= 0x81U) {
            ((SpriteFrameState *)primitive)->color.c.g = 0x80U;
        }
    }
    blue = ((SpriteFrameState *)primitive)->color.c.b;
    if (blue != 0) {
        faded_blue = blue - ((S_800B63A8_1 *)effect)->unk_18;
        ((SpriteFrameState *)primitive)->color.c.b = faded_blue;
        if ((u32) (faded_blue & 0xFF) >= 0x81U) {
            ((SpriteFrameState *)primitive)->color.c.b = 0x80U;
        }
    }
    life_left = ((S_800B63A8_1 *)effect)->unk_0E - 1;
    ((S_800B63A8_1 *)effect)->unk_0E = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B63A8_1_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}

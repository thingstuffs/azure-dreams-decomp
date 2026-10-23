#include "common.h"
#include "dungeon/effect/state.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"


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
void advance_effect_fade_and_flag(void *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
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

    motion->velocity_x = (s32) (motion->velocity_x + ((S_800B63A8_1 *)effect)->unk_00);
    motion->velocity_y = (s32) (motion->velocity_y + ((S_800B63A8_1 *)effect)->unk_04);
    accel_z_step = ((S_800B63A8_1 *)effect)->unk_08 * ((S_800B63A8_1 *)effect)->unk_10;
    motion->velocity_z = (s32) (motion->velocity_z + accel_z_step);
    ((S_800B63A8_1 *)effect)->unk_10 = (s16) ((u16) ((S_800B63A8_1 *)effect)->unk_10 + 1);
    velocity_y = motion->velocity_y;
    velocity_z = motion->velocity_z;
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + velocity_y);
    motion->z.v = (s32) (motion->z.v + velocity_z);
    advance_sprite_animation_and_textures(primitive);
    red = primitive->color.c.r;
    if (red != 0) {
        faded_red = red - ((S_800B63A8_1 *)effect)->unk_14;
        primitive->color.c.r = faded_red;
        if ((u32) (faded_red & 0xFF) >= 0x81U) {
            primitive->color.c.r = 0x80U;
        }
    }
    green = primitive->color.c.g;
    if (green != 0) {
        faded_green = green - ((S_800B63A8_1 *)effect)->unk_16;
        primitive->color.c.g = faded_green;
        if ((u32) (faded_green & 0xFF) >= 0x81U) {
            primitive->color.c.g = 0x80U;
        }
    }
    blue = primitive->color.c.b;
    if (blue != 0) {
        faded_blue = blue - ((S_800B63A8_1 *)effect)->unk_18;
        primitive->color.c.b = faded_blue;
        if ((u32) (faded_blue & 0xFF) >= 0x81U) {
            primitive->color.c.b = 0x80U;
        }
    }
    life_left = ((S_800B63A8_1 *)effect)->unk_0E - 1;
    ((S_800B63A8_1 *)effect)->unk_0E = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B63A8_1_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

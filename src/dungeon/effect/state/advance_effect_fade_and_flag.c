#include "common.h"
#include "dungeon/effect/state.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"


typedef struct S_800B63A8_1_pre {
    u16 unk_00;
} S_800B63A8_1_pre;   /* the 0x2 bytes before arg0 in advance_effect_fade_and_flag, addressed as arg0[-1] */


/* Advance effect motion, fade its color, and flag it when its lifetime expires. */
void advance_effect_fade_and_flag(OppositeOffsetEffectBody *effect, ObjectPosition *motion, SpriteFrameState *primitive) {
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

    motion->velocity_x = (s32) (motion->velocity_x + effect->acceleration_x);
    motion->velocity_y = (s32) (motion->velocity_y + effect->acceleration_y);
    accel_z_step = effect->acceleration_z * effect->acceleration_step;
    motion->velocity_z = (s32) (motion->velocity_z + accel_z_step);
    effect->acceleration_step = (s16) ((u16) effect->acceleration_step + 1);
    velocity_y = motion->velocity_y;
    velocity_z = motion->velocity_z;
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + velocity_y);
    motion->z.v = (s32) (motion->z.v + velocity_z);
    advance_sprite_animation_and_textures(primitive);
    red = primitive->color.c.r;
    if (red != 0) {
        faded_red = red - effect->red.decrement;
        primitive->color.c.r = faded_red;
        if ((u32) (faded_red & 0xFF) >= 0x81U) {
            primitive->color.c.r = 0x80U;
        }
    }
    green = primitive->color.c.g;
    if (green != 0) {
        faded_green = green - effect->green.decrement;
        primitive->color.c.g = faded_green;
        if ((u32) (faded_green & 0xFF) >= 0x81U) {
            primitive->color.c.g = 0x80U;
        }
    }
    blue = primitive->color.c.b;
    if (blue != 0) {
        faded_blue = blue - effect->blue.decrement;
        primitive->color.c.b = faded_blue;
        if ((u32) (faded_blue & 0xFF) >= 0x81U) {
            primitive->color.c.b = 0x80U;
        }
    }
    life_left = effect->lifetime.remaining_frames - 1;
    effect->lifetime.remaining_frames = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B63A8_1_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

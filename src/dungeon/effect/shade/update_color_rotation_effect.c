#include "slus.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libc.h"
#include "dungeon/effect/shade.h"

typedef struct S_818C3448_0_pre {
    u16 unk_00;
} S_818C3448_0_pre;   /* the 0x2 bytes before arg0 in func_818C3448, addressed as arg0[-1] */

typedef struct S_818C3448_0 {
    void * unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    s16 unk_10;
    u16 unk_12;
    s16 unk_14;
} S_818C3448_0;   /* arg0 in func_818C3448 */

typedef struct S_818C3448_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_818C3448_1;

s32 create_random_rotation_effect();
s32 create_dimmed_copy_effect();

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} Func818C3448State;

/* Update the effect's color, rotation, growth, motion, and phase transitions. */
void animate_color_cycling_sprite_burst(void *effect_arg, void *motion_arg, SpriteFrameState *visual) {
    Func818C3448State *motion = motion_arg;
    S_818C3448_0 *effect = effect_arg;
    s16 scale;
    s32 color_bits;
    s16 color_cycle;
    s16 angle;
    s16 next_tick;
    s16 phase;
    s16 elapsed;
    s16 duration;
    s32 color_bias;
    s32 half_color;
    s32 velocity_y;
    s32 velocity_z;
    s16 full_scale;
    s32 opposite_angle;
    s32 position_x;
    s32 random_value;
    s32 velocity_x;
    s32 opposite_bias;
    s32 random_bias;
    u16 burst_phase;
    u16 wait_phase;
    S_818C3448_1 *owner;

    owner = effect->unk_00;
    owner->unk_0C = (u16) (owner->unk_0C + 1);
    next_tick = (s16) (effect->unk_12 + 1);
    color_cycle = next_tick;
    effect->unk_10++;
    effect->unk_12 = (u16) next_tick;
    color_cycle = (color_cycle % 7) + 1;
    advance_sprite_animation_and_textures(visual);
    color_bits = (s16) color_cycle;
    color_bias = color_bits;
    visual->angle_z = (u16) (visual->angle_z + 0x300);
    if (color_bits < 0) {
        color_bias = color_bits + 3;
    }
    half_color = color_bits / 2;
    visual->color.c.r = (s8) ((color_bias >> 2) << 7);
    visual->color.c.g = (s8) ((s32) (((s16) half_color - (((s32) ((s16) half_color + ((u32) (half_color << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
    visual->color.c.b = (s8) ((s32) ((color_bits - (half_color * 2)) << 0x10) >> 9);
    phase = effect->unk_0E;
    wait_phase = effect->unk_0E;
    switch (phase) {
    case 0:
        full_scale = 0x1400;
        scale = (full_scale / (s16) effect->unk_14) * effect->unk_10;
        visual->scale_y = scale;
        visual->scale_x = scale;
        position_x = motion->f0;
        velocity_x = motion->fC;
        velocity_y = motion->f10;
        velocity_z = motion->f14;
        motion->f0 = position_x + velocity_x;
        motion->f4 = (s32) (motion->f4 + velocity_y);
        motion->f8 = (s32) (motion->f8 + velocity_z);
        elapsed = effect->unk_10;
        duration = effect->unk_14;
        if (elapsed < duration) {
            return;
        }
        burst_phase = effect->unk_0E;
        effect->unk_10 = 0U;
        effect->unk_0E = burst_phase + 1;
        return;
    case 1:
        if (effect->unk_10 < 0xC) {
            return;
        }
        effect->unk_0E = wait_phase + 1;
        effect->unk_10 = 0;
        return;
    case 2:
        create_dimmed_copy_effect(effect, motion, visual);
        random_bias = rand();
        random_value = random_bias;
        angle = (random_value % 4096);
        create_random_rotation_effect(effect, motion, angle);
        opposite_angle = angle + 0x800;
        opposite_bias = opposite_angle;
        if (opposite_angle < 0) {
            opposite_bias = angle + 0x17FF;
        }
        create_random_rotation_effect(effect, motion, (s16) (opposite_angle - ((opposite_bias >> 0xC) << 0xC)));
        if (effect->unk_10 < 0x21) {
            return;
        }
        burst_phase = effect->unk_0E;
        effect->unk_10 = 0U;
        effect->unk_0E = burst_phase + 1;
        return;
    case 3:
        if (visual->flags & 0x6000) {
            ((S_818C3448_0_pre *)effect)[-1].unk_00 = (u16) (((S_818C3448_0_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        return;
    }
}

#include "common.h"
#include "dungeon/monster/ghosh/tracked_fade.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/ghosh.h"





typedef struct S_80172874_4 {
    u8 pad_00[0x4CE0];
    s32 unk_4CE0;
} S_80172874_4;   /* flag_base in update_boss_effect_growth */


typedef struct S_80172874_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172874_6;   /* source in update_boss_effect_growth */

typedef struct S_80172874_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80172874_7;   /* global_base in update_boss_effect_growth */


extern u8 ghosh_frame_set_5[];

/* Brighten and rotate the sprite, track its source position, then fade it out. */
void update_boss_effect_growth(GhoshTrackedFadeBody *effect, ObjectPosition *position, SpriteFrameState *transform)
{
    GhoshTrackedFadeBody *base = effect;
    S_80172874_6 *source;
    SpriteFrameState *owner;
    s16 duration;
    s16 mode;
    s32 grow_scale;
    s32 shrink_scale;
    u16 angle;
    u16 current_mode;
    u16 next_angle;
    u16 grow_step;
    u16 shrink_step;
    u16 owner_value;
    ObjectNodeHeader *parent;

    parent = NODE_HEADER(base->owner);
    source = base->source_position;
    owner = parent->sprite;
    angle = transform->angle_z;
    owner_value = owner->depth_bias;
    next_angle = angle + 0x190;
    transform->angle_z = next_angle;
    transform->depth_bias = owner_value;
    if ((u16)next_angle >= 0x1001U) {
        transform->angle_z = angle - 0xE70;
    }

    mode = (s16)base->phase;
    current_mode = base->phase;
    switch (mode) {
    case 0:
        grow_step = base->phase_ticks + 1;
        duration = base->phase_duration;
        grow_scale = ((s32)(grow_step << 16) >> 9) / duration;
        base->phase_ticks = grow_step;
        transform->color.c.r = grow_scale;
        transform->color.c.g = grow_scale;
        transform->color.c.b = grow_scale;
        if ((s16)base->phase_ticks >= 5) {
            base->phase = base->phase + 1;
            return;
        }
        return;
    case 1:
    {
        u32 flag_base;
        flag_base = 0x80170000;
        if (((S_80172874_4 *)flag_base)->unk_4CE0 == 0) {
            base->phase = current_mode + 1;
            base->phase_duration = 0x14;
            base->phase_ticks = 0x14;
        }
        if (owner->frameTable == ghosh_frame_set_5) {
            base->phase_duration = 0x14;
            base->phase_ticks = 0x14;
            base->phase = base->phase + 1;
        }
        position->x.v = source->unk_00;
        position->y.v = source->unk_04;
        position->z.v = source->unk_08;
        return;
    }
    case 2:
        shrink_step = base->phase_ticks - 1;
        shrink_scale = ((s32)(shrink_step << 16) >> 9) / base->phase_duration;
        base->phase_ticks = shrink_step;
        transform->color.c.r = shrink_scale;
        transform->color.c.g = shrink_scale;
        transform->color.c.b = shrink_scale;
        if ((s16)base->phase_ticks <= 0) {
            s32 *global_base;
            global_base = (s32 *)0x80080000;
            NODE_HEADER(base)->flags |= 0x8000;
            ((S_80172874_7 *)global_base)->unk_14A0 |= 0x8000;
        }

        return;
    default:
        return;
    }
}

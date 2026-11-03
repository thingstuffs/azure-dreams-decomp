#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/u_boat.h"

typedef struct S_80170A84_0_pre {
    u16 unk_00;
} S_80170A84_0_pre;   /* the 0x2 bytes before arg0 in update_shrinking_sprite_effect, addressed as arg0[-1] */

typedef struct S_80170A84_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80170A84_1_pre;   /* the 0x14 bytes before base in update_shrinking_sprite_effect, addressed as base[-1] */

typedef struct S_80170A84_1 {
    u8 pad_00[0x9B];
    u8 unk_9B;
    u8 pad_9C[0x15];
    u8 unk_B1;
    u8 pad_B2[0x1];
    u8 unk_B3;
} S_80170A84_1;   /* base in update_shrinking_sprite_effect */




/* Updates effect rotation and fading, then copies three source words to the output. */
void update_shrinking_sprite_effect(UBoatAuraEffectBody *effect, void *output, void *render_arg)
{
    SpriteFrameState *render_data = render_arg;
    void *owner_data;
    u32 *source_words;
    u16 header_value;
    u16 angle;
    u16 next_phase;
    u16 reset_ticks;
    s32 phase_index;

    owner_data = effect->owner;
    source_words = effect->source.words;
    header_value = ((ObjectPosition *)(((S_80170A84_1_pre *)owner_data)[-1].unk_00))->y.unsigned_parts.integer;

    angle = render_data->angle_z + 400;
    render_data->angle_z = angle;
    render_data->depth_bias = header_value;
    if (angle >= 4097) {
        render_data->angle_z = angle - 4096;
    }

    phase_index = effect->phase.s;
    switch (phase_index) {

    case 0:
    {
        u16 ticks = effect->ticks.s;
        s16 duration = effect->duration;
        s32 intensity;

        ticks++;
        intensity = ((ticks << 16) >> 9) / duration;
        effect->ticks.s = ticks;
        render_data->color.c.r = intensity;
        render_data->color.c.g = intensity;
        render_data->color.c.b = intensity;
    }
        if (effect->ticks.u < 5) {
            break;
        }
        next_phase = effect->phase.u;
        next_phase++;
        effect->phase.u = next_phase;
        break;

    case 1:
        if (((S_80170A84_1 *)owner_data)->unk_9B >= 4) {
            effect->ticks.s = 0;
            effect->duration = 20;
            effect->phase.u++;
        }
        if (((S_80170A84_1 *)owner_data)->unk_B3 != 3 || ((S_80170A84_1 *)owner_data)->unk_B1 != 2) {
            break;
        }
        effect->phase.u = 4;
        effect->duration = 20;
        effect->ticks.s = 20;
        break;

    case 2:
    {
        u16 ticks = effect->ticks.s;
        s16 duration = effect->duration;
        s32 intensity;

        ticks++;
        intensity = ((ticks << 16) >> 9) / duration;
        effect->ticks.s = ticks;
        render_data->color.c.r = intensity;
        render_data->color.c.g = intensity;
        render_data->color.c.b = intensity;
    }
        if (effect->ticks.u < effect->duration) {
            break;
        }
        next_phase = effect->phase.u;
        reset_ticks = 20;
        effect->duration = reset_ticks;
        effect->ticks.s = reset_ticks;
        next_phase++;
        effect->phase.u = next_phase;
        break;

    case 3:
    {
        u16 ticks = effect->ticks.s;
        s16 duration = effect->duration;
        s32 intensity;

        ticks--;
        intensity = ((ticks << 16) >> 9) / duration;
        effect->ticks.s = ticks;
        render_data->color.c.r = intensity;
        render_data->color.c.g = intensity;
        render_data->color.c.b = intensity;
    }
        if (effect->ticks.u > 0) {
            break;
        }
        ((S_80170A84_0_pre *)effect)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;

    case 4:
    {
        u16 ticks = effect->ticks.s;
        s16 duration = effect->duration;
        s32 intensity;

        ticks--;
        intensity = ((ticks << 16) >> 9) / duration;
        effect->ticks.s = ticks;
        render_data->color.c.r = intensity;
        render_data->color.c.g = intensity;
        render_data->color.c.b = intensity;
    }
        if (effect->ticks.u > 0) {
            break;
        }
        next_phase = effect->phase.u;
        reset_ticks = 20;

        effect->ticks.s = reset_ticks;
        next_phase++;
        effect->phase.u = next_phase;
        break;

    case 5:
    {
        u16 ticks = effect->ticks.s;

        effect->ticks.s = ticks - 1;
        if ((ticks << 16) > 0) {
            break;
        }
    }
        effect->phase.u = 2;
        effect->ticks.s = 0;
        effect->duration = 20;

    default:
        break;
    }
    ((u32 *)output)[0] = source_words[0];
    ((u32 *)output)[1] = source_words[1];
    ((u32 *)output)[2] = source_words[2];
}

#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"

#include "engine/effect.h"
/* Fade through seven table entries, then advance the owner and mark completion. */
void update_fade_in_out_effect(CdCueEffectBody *state, ObjectPosition *unused_arg, SpriteFrameState *visual)
{
    u8 *flags_page;
    u16 next_tick = state->timer + 1;
    s32 phase = state->state;
    u16 saved_phase = state->state;
    u16 advance_phase;
    u32 flags;
    state->timer = next_tick;
    switch (phase) {
    case 0:
        if (state->completion != 0) {
            advance_phase = state->state;
            state->completion = 0;
            state->timer = 0;
            state->state = advance_phase + 1;
        }
        break;

    case 1:
    {
        u8 brightness = visual->color.c.b + 4;
        visual->color.c.b = brightness;
        visual->color.c.g = brightness;
        visual->color.c.r = brightness;
    }
        if (state->timer < 0x20) {
            break;
        }
        advance_phase = state->state;
        state->timer = 0;

        state->state = advance_phase + 1;
        break;

    case 2:
        if (((s16) next_tick) >= 0x3F) {
            state->state = saved_phase + 1;
            state->timer = 0;
        }
        break;

    case 3:
    {
        u8 brightness = visual->color.c.b - 4;
        visual->color.c.b = brightness;
        visual->color.c.g = brightness;
        visual->color.c.r = brightness;
    }
        if (state->timer < 0x20) {
            break;
        }
        {
            s16 entry_index = state->index + 1;
            state->index = entry_index;
            if (entry_index != 7) {
                entry_index = entry_index % 7;
                state->index = entry_index;
                visual->source = fade_effect_visual_table[entry_index];
                state->state = 0;
                state->timer = 0;
                return;
            }
        }
        state->owner.fade->value_14 = 0;
        state->owner.fade->flags = state->owner.fade->flags + 1;
        NODE_HEADER(state)->flags |= 0x8000;
        flags = ((u32)object_flag_block.flags);
        flags |= 0x8000;
        flags_page = (u8 *) 0x80080000;
        *((u32 *) (flags_page + 0x14A0)) = flags;
        break;

    default:
        visual->color.c.b = 0;
        visual->color.c.g = 0;
        visual->color.c.r = 0;
        state->owner.fade->value_14 = 0;
        state->owner.fade->flags = state->owner.fade->flags + 1;
        NODE_HEADER(state)->flags |= 0x8000;
        flags = ((u32)object_flag_block.flags);
        flags |= 0x8000;
        flags_page = (u8 *) 0x80080000;
        *((u32 *) (flags_page + 0x14A0)) = flags;
        break;
    }
}

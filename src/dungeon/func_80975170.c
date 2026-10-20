#include "dungeon/monster/hikewne/apply_countdown_scaled_effect_intensity.h"
#include "shared/sprite_frame_state.h"

void advance_and_fade_transformed_effect(void *effect, MovingPosition *transform, SpriteFrameState *render_state)
{
    s16 ticks_left;
    s32 brightness;
    u16 render_offset;
    MovingPosition *source_transform;

    source_transform = ((S_80975170_0 *)effect)->unk_B0;
    transform->unk_02 = source_transform->unk_02;
    transform->unk_06 = source_transform->unk_06;
    transform->unk_0A = source_transform->unk_0A;

    render_offset = render_state->scale_y + 0x320;
    render_state->scale_y = render_offset;
    render_state->scale_x = render_offset;

    ticks_left = ((S_80975170_0 *)effect)->unk_96.s - 1;
    brightness = (s32)(ticks_left * 0x50) / (s16)((S_80975170_0 *)effect)->unk_AA;
    ((S_80975170_0 *)effect)->unk_96.s = (u16)ticks_left;
    render_state->color.c.b = (s8)brightness;
    render_state->color.c.g = (s8)brightness;
    render_state->color.c.r = (s8)brightness;
    func_800478B8(render_state);

    if (((S_80975170_0 *)effect)->unk_96.u <= 0) {
        ((ObjectRetirementFlags *)effect)[-1].unk_00 = (u16)(((ObjectRetirementFlags *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | 0x8000);
    }
}

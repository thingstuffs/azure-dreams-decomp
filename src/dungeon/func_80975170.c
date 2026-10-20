#include "dungeon/monster/hikewne/apply_countdown_scaled_effect_intensity.h"

void advance_and_fade_transformed_effect(void *effect, MovingPosition *transform, Rec_D_80082E80 *render_state)
{
    s16 ticks_left;
    s32 brightness;
    u16 render_offset;
    MovingPosition *source_transform;

    source_transform = ((S_80975170_0 *)effect)->unk_B0;
    transform->unk_02 = source_transform->unk_02;
    transform->unk_06 = source_transform->unk_06;
    transform->unk_0A = source_transform->unk_0A;

    render_offset = render_state->unk_1C.at02_u16.v + 0x320;
    render_state->unk_1C.at02_u16.v = render_offset;
    render_state->unk_1C.at00_u16.v = render_offset;

    ticks_left = ((S_80975170_0 *)effect)->unk_96.s - 1;
    brightness = (s32)(ticks_left * 0x50) / (s16)((S_80975170_0 *)effect)->unk_AA;
    ((S_80975170_0 *)effect)->unk_96.s = (u16)ticks_left;
    render_state->unk_0C.at02_s8.v = (s8)brightness;
    render_state->unk_0C.at01_s8.v = (s8)brightness;
    render_state->unk_0C.at00_s8.v = (s8)brightness;
    func_800478B8(render_state);

    if (((S_80975170_0 *)effect)->unk_96.u <= 0) {
        ((ObjectRetirementFlags *)effect)[-1].unk_00 = (u16)(((ObjectRetirementFlags *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | 0x8000);
    }
}

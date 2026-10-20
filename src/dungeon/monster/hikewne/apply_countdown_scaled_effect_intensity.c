#include "dungeon/monster/hikewne/apply_countdown_scaled_effect_intensity.h"
#include "shared/sprite_frame_state.h"

void apply_countdown_scaled_effect_intensity(void *record_data, void *unused, SpriteFrameState *color_target) {
    s16 remaining_ticks;
    s32 intensity;

    intensity = (s32) (((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98
        << 7) / (s16) ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_AC;
    color_target->color.c.b = (s8) intensity;
    color_target->color.c.g = (s8) intensity;
    color_target->color.c.r = (s8) intensity;
    func_800478B8(color_target);
    remaining_ticks = (u16) ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98 - 1;
    ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_98 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        ((S_809750E8_0 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_809750E8_0 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}

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

void create_directional_template_effect(void *unused, MovingPosition *source_pos, void *sprite_template, S_80975244_3 *facing_source) {
    SpriteFrameState *sprite;
    void *effect;
    S_80975244_0 *effect_state;
    MovingPosition *effect_pos;
    void *template_data;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    effect = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    template_data = sprite_template;
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_96 = 7;
        effect_state->unk_AA = 7;
        ((S_80975244_1 *)effect)->unk_10 = advance_and_fade_transformed_effect;
        effect_state->unk_B0 = source_pos;
        sprite = ((S_80975244_1 *)effect)->unk_0C;
        src = (Block16 *)template_data;
        dst = (Block16 *)sprite;
        end = src + 3;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x50;
        sprite->color.c.g = 0x50;
        sprite->color.c.r = 0x50;
        sprite->tpage_abr = 0x20;
        sprite->clut = 0xFF80;
        sprite->unk_22 = 0xFFF1;
        sprite->flags = (u16) (sprite->flags | 0xC);
        register_node(effect, project_sprite_chain);
        sprite->frameTable = &D_80174128;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7)
            + D_80174128), 0);
        effect_pos = ((S_80975244_1 *)effect)->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (u16) source_pos->unk_0A;
    }
}

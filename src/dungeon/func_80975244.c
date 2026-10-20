#include "dungeon/monster/hikewne/apply_countdown_scaled_effect_intensity.h"
#include "shared/sprite_frame_state.h"

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
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7)
            + D_80174128), 0);
        effect_pos = ((S_80975244_1 *)effect)->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (u16) source_pos->unk_0A;
    }
}

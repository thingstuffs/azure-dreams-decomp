#include "dungeon/monster/unicorn/advance_record_state_and_set_completion_flags.h"
#include "shared/sprite_frame_state.h"

/* Create a tinted sprite effect at the supplied position with a random variant. */
void create_tinted_sprite_effect_supplied_position(void *unused, void *position_data, SpriteFrameState *unused_primitive) {
    T_8017406C_S_8017406C_0 *effect_state;
    SpriteFrameState *sprite;
    void *effect;
    T_8017406C_S_8017406C_3 *source_pos = position_data;
    T_8017406C_S_8017406C_4 *effect_pos;

    effect = func_8003FC64(0x212);
    if (effect != 0) {
        effect_state = effect + 0x20;
        effect_state->unk_1A = 0xF;
        ((T_8017406C_S_8017406C_1 *)effect)->unk_10 = &advance_record_state_and_set_completion_flags;
        register_node(effect, project_sprite_chain);
        sprite = ((T_8017406C_S_8017406C_1 *)effect)->unk_0C;
        sprite->tpage_abr = 0x20;
        sprite->flags = (u16)(sprite->flags | 0xC);
        effect_pos = ((T_8017406C_S_8017406C_1 *)effect)->unk_08;
        effect_state->unk_40 = (s32)source_pos->unk_00.at00.v;
        effect_state->unk_44 = (s32)source_pos->unk_04.at00.v;
        effect_pos->unk_02 = (u16)source_pos->unk_00.at02.v;
        effect_pos->unk_06 = (u16)source_pos->unk_04.at02.v;
        effect_pos->unk_0A = (u16)source_pos->unk_0A;
        sprite = ((T_8017406C_S_8017406C_1 *)effect)->unk_0C;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->color.c.b = 0x60U;
        sprite->color.c.g = 0xFFU;
        sprite->color.c.r = 0xFFU;
        ((T_8017406C_S_8017406C_1 *)effect)->unk_20 = 0xFFU;
        effect_state->unk_01 = (u8)sprite->color.c.g;
        effect_state->unk_02 = (u8)sprite->color.c.b;
        func_8003DB94(sprite, &D_800DEC70, rand() & 1);
        sprite->clut = 0x7DCF;
        sprite->flags = (u16)(sprite->flags | 0x100);
    }
}

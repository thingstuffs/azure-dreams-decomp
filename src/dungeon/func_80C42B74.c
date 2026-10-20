#include "dungeon/monster/unicorn/advance_record_state_and_set_completion_flags.h"
#include "shared/sprite_frame_state.h"

/* Creates a yellow effect at an angular offset from the supplied position. */
void create_angular_offset_effect(void *unused_context, Rec_func_80173CFC_arg1 *origin, s32 unused_param_2, s32 unused_param_3,
    s16 angle, u16 height_offset) {
    void *effect;
    T_80174374_S_80174374_0 *effect_state;
    SpriteFrameState *sprite;
    void *position;
    s16 wrapped_angle;

    effect = func_8003FC64(0x212);
    wrapped_angle = angle;
    if (effect != 0) {
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_1A = 0x14;
        effect_state->unk_1E = angle;
        ((T_80174374_S_80174374_1 *)effect)->unk_10 = &update_orbit_height_and_fade_effect;
        register_node(effect, project_sprite_chain);

        sprite = ((T_80174374_S_80174374_1 *)effect)->unk_0C;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;

        position = ((T_80174374_S_80174374_1 *)effect)->unk_08;
        effect_state->unk_40 = origin->unk_00.at00_s32.v;
        effect_state->unk_44 = origin->unk_04.at00_s32.v;

        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        ((T_80174374_S_80174374_4 *)position)->unk_00 = effect_state->unk_40 + func_80064584(wrapped_angle) * 0x280;
        ((T_80174374_S_80174374_4 *)position)->unk_04 = effect_state->unk_44 + func_800644B8(wrapped_angle) * 0x280;
        ((T_80174374_S_80174374_4 *)position)->unk_0A = origin->unk_0A + height_offset;

        sprite = ((T_80174374_S_80174374_1 *)effect)->unk_0C;
        sprite->scale_y = 0x400;
        sprite->scale_x = 0x400;
        sprite->color.c.b = 0x60;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        effect_state->unk_00 = 0xFF;
        effect_state->unk_01 = sprite->color.c.g;
        effect_state->unk_02 = sprite->color.c.b;

        func_8003DB94(sprite, &D_800DEC00, rand() & 1);
        sprite->clut = 0x7DCF;
        sprite->flags |= 0x100;
    }
}

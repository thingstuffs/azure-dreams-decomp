#include "dungeon/monster/unicorn/advance_record_state_and_set_completion_flags.h"
#include "shared/sprite_frame_state.h"

/* Advance state and decrement the record count, setting record and global flags at completion. */
void advance_record_state_and_set_completion_flags(void *record_data, DelayMotionZ *state, s32 update_arg) {
    u16 remaining_count;

    state->unk_08 = (s32) (state->unk_08 + 0x10000);
    func_800478B8(update_arg);
    remaining_count = ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}

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

/* Update the effect's orbit and height, fade its color, and mark it for removal when its life expires. */
void update_orbit_height_and_fade_effect(void *effect, ObjectPosition *position, SpriteFrameState *primitive) {
    s16 life;
    s16 angle;
    s16 next_life;

    angle = ((T_801741A0_S_801741A0_0 *)effect)->unk_1E - 0x12C;
    ((T_801741A0_S_801741A0_0 *)effect)->unk_1E = (u16) angle;
    position->x.v = (s32) (((T_801741A0_S_801741A0_0 *)effect)->unk_40 + (func_80064584(angle) * 0x280));
    position->y.v = (s32) (((T_801741A0_S_801741A0_0 *)effect)->unk_44
        + (func_800644B8((s16) ((T_801741A0_S_801741A0_0 *)effect)->unk_1E) * 0x280));
    position->z.v = (s32) (position->z.v + 0xFFF60000);
    func_800478B8(primitive);
    if ((((T_801741A0_S_801741A0_0 *)effect)->unk_1A < 0x11) && (((T_801741A0_S_801741A0_0 *)effect)->unk_20 == 0) && !(rand() & 0xF)) {
        create_tinted_sprite_effect_supplied_position(effect, position, primitive);
    }
    life = ((T_801741A0_S_801741A0_0 *)effect)->unk_1A;
    if (life < 0xA) {
        primitive->color.c.r = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_00 * life) / 9);
        primitive->color.c.g = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_01 * ((T_801741A0_S_801741A0_0 *)effect)->unk_1A) / 9);
        primitive->color.c.b = (s8) ((((T_801741A0_S_801741A0_0 *)effect)->unk_02 * ((T_801741A0_S_801741A0_0 *)effect)->unk_1A) / 9);
    }
    next_life = (u16) ((T_801741A0_S_801741A0_0 *)effect)->unk_1A - 1;
    ((T_801741A0_S_801741A0_0 *)effect)->unk_1A = next_life;
    if ((next_life << 0x10) <= 0) {
        ((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 = (u16) (((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}

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

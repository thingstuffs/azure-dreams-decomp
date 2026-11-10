/* Unicorn effect completion, tinted sprite creation, orbiting, and fading. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/monster/unicorn/advance_record_state_and_set_completion_flags.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/unicorn.h"

/* Advance state and decrement the record count, setting record and global flags at completion. */
void advance_record_state_and_set_completion_flags(void *record_data, DelayMotionZ *state, SpriteFrameState *update_arg) {
    u16 remaining_count;

    state->unk_08 = (s32) (state->unk_08 + 0x10000);
    advance_sprite_animation_and_textures(update_arg);
    remaining_count = ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C - 1;
    ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_1C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        ((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((T_80173FF4_S_80173FF4_1 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Create a tinted sprite effect at the supplied position with a random variant. */
void create_tinted_sprite_effect_supplied_position(void *unused, ObjectPosition *position_data, SpriteFrameState *unused_primitive) {
    T_8017406C_S_8017406C_0 *effect_state;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;
    ObjectPosition *source_pos = position_data;
    ObjectPosition *effect_pos;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect_state = NODE_BODY(effect);
        effect_state->unk_1A = 0xF;
        effect->update_callback = &advance_record_state_and_set_completion_flags;
        register_node(effect, project_sprite_chain);
        sprite = effect->sprite;
        sprite->tpage_abr = 0x20;
        sprite->flags = (u16)(sprite->flags | 0xC);
        effect_pos = effect->position;
        effect_state->unk_40 = (s32)source_pos->x.v;
        effect_state->unk_44 = (s32)source_pos->y.v;
        effect_pos->x.w.i = (u16)source_pos->x.unsigned_parts.integer;
        effect_pos->y.w.i = (u16)source_pos->y.unsigned_parts.integer;
        effect_pos->z.w.i = (u16)source_pos->z.unsigned_parts.integer;
        sprite = effect->sprite;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->color.c.b = 0x60U;
        sprite->color.c.g = 0xFFU;
        sprite->color.c.r = 0xFFU;
        ((T_8017406C_S_8017406C_1 *)effect)->unk_20 = 0xFFU;
        effect_state->unk_01 = (u8)sprite->color.c.g;
        effect_state->unk_02 = (u8)sprite->color.c.b;
        select_record_entry_and_value(sprite, &shared_sprite_entries, rand() & 1);
        sprite->clut = 0x7DCF;
        sprite->flags = (u16)(sprite->flags | 0x100);
    }
}

/* Update the effect's orbit and height, fade its color, and mark it for removal when its life expires. */
void update_orbit_height_and_fade_effect(AngularOffsetEffectBody *effect, ObjectPosition *position, SpriteFrameState *primitive) {
    s16 life;
    s16 angle;
    s16 next_life;

    angle = effect->angle - 0x12C;
    effect->angle = (u16) angle;
    position->x.v = (s32) (effect->center_x + (rcos(angle) * 0x280));
    position->y.v = (s32) (effect->center_y + (rsin((s16) effect->angle) * 0x280));
    position->z.v = (s32) (position->z.v + 0xFFF60000);
    advance_sprite_animation_and_textures(primitive);
    if ((effect->remaining_ticks < 0x11) && (effect->pulse_state == 0) && !(rand() & 0xF)) {
        create_tinted_sprite_effect_supplied_position(effect, position, primitive);
    }
    life = effect->remaining_ticks;
    if (life < 0xA) {
        primitive->color.c.r = (s8) ((effect->red * life) / 9);
        primitive->color.c.g = (s8) ((effect->green * effect->remaining_ticks) / 9);
        primitive->color.c.b = (s8) ((effect->blue * effect->remaining_ticks) / 9);
    }
    next_life = (u16) effect->remaining_ticks - 1;
    effect->remaining_ticks = next_life;
    if ((next_life << 0x10) <= 0) {
        ((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 = (u16) (((T_801741A0_S_801741A0_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Creates a yellow effect at an angular offset from the supplied position. */
/* Creates a yellow Unicorn effect on a circular offset, with supplied height, random texture variant, and
 * orbit callback. */
void create_angular_offset_effect(void *unused_context, ObjectPosition *origin, SpriteFrameState *unused_param_2, ActorRecord *unused_param_3,
    s16 angle, u16 height_offset) {
    ObjectNodeHeader *effect;
    AngularOffsetEffectBody *effect_state;
    SpriteFrameState *sprite;
    ObjectPosition *position;
    s16 wrapped_angle;

    effect = allocate_flagged_object_node(0x212);
    wrapped_angle = angle;
    if (effect != 0) {
        effect_state = NODE_BODY(effect);
        effect_state->remaining_ticks = 0x14;
        effect_state->angle = angle;
        effect->update_callback = &update_orbit_height_and_fade_effect;
        register_node(effect, project_sprite_chain);

        sprite = effect->sprite;
        sprite->tpage_abr = 0x20;
        sprite->flags |= 0xC;

        position = effect->position;
        effect_state->center_x = origin->x.v;
        effect_state->center_y = origin->y.v;

        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        position->x.v = effect_state->center_x + rcos(wrapped_angle) * 0x280;
        position->y.v = effect_state->center_y + rsin(wrapped_angle) * 0x280;
        position->z.w.i = origin->z.w.i + height_offset;

        sprite = effect->sprite;
        sprite->scale_y = 0x400;
        sprite->scale_x = 0x400;
        sprite->color.c.b = 0x60;
        sprite->color.c.g = 0xFF;
        sprite->color.c.r = 0xFF;
        effect_state->red = 0xFF;
        effect_state->green = sprite->color.c.g;
        effect_state->blue = sprite->color.c.b;

        select_record_entry_and_value(sprite, &directional_sprite_entries, rand() & 1);
        sprite->clut = 0x7DCF;
        sprite->flags |= 0x100;
    }
}

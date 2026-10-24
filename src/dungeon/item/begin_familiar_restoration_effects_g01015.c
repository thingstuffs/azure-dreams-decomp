/* Begin familiar restoration effects.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01015 - CL:dungeon/func_800BC2E4.
 */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/item/begin_familiar_restoration_effects_g01015.h"
#include "shared/object_flags.h"

/* Processes the two object slots if has_enough_available_runtime_nodes(2) succeeds. */
s32 begin_familiar_restoration_effects(void)
{
    s32 slot;
    u8 *object;
    u8 *linked_object;

    if (has_enough_available_runtime_nodes(2) == 0) {
        return 0;
    }

    slot = 0;
    do {
        object = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 0xAC + slot * 4);
        if (object != 0) {
            linked_object = *(u8 **)(object - 0x14);
            create_familiar_restoration_effect(linked_object[0x24], linked_object[0x25],
                          *(s16 *)(object + 0x88));
        }
        slot++;
    } while (slot < 2);

    return 1;
}

/* Dispatches a target action according to its type and address. */
s32 use_item_to_draw_full_recovery_circle(void *target, s32 action_id, s16 action_type, s32 action_arg) {
    void *target_data;

    if (action_type == 0xD) {
        return process_record_and_update_linked_state(action_id, action_arg);
    }
    if (target == dungeon_actor_ring_anchor) {
        *(s32 *)((u8 *)target + 0x110) = action_id;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), 0);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, action_id);
        if (feed_actor_restore_mp(target, entity_action_selectors[*(u8 *)((u8 *)target + 0x13)] & 3, action_id) == 0) {
            place_actor_item(target, action_id);
            return 1;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    } else {
        target_data = *(void **)((u8 *)target - 0x14);
        if (create_five_point_effect(*(u8 *)((u8 *)target_data + 0x24), *(u8 *)((u8 *)target_data + 0x25),
            *(s16 *)((u8 *)target + 0x88), &D_800DF514, 0x2800, 0x802020, &D_800C152C) == 0) {
            return 0;
        }
        display_formatted_context_message(&D_800E14A6);
    }
    clear_slot_and_update_linked_state(action_id);
    return 1;
}

/* Updates a three-stage visual effect, restoring objects and fading the rendered effect. */
void update_familiar_restoration_effect(DungeonState *state, RenderSource *render_source, u8 *effect_data) {
    s32 object_index;
    s32 step_index;
    RenderSource *source = render_source;
    s16 mode = state->mode;
    s16 frames_left;
    s16 reset_marker;
    u16 grow_angle;
    u16 fade_angle;
    void *object_entry;
    u8 *object;

    switch (mode) {
    case 0:
    {
        u16 effect_scale = *(u16 *)(effect_data + 0x1c);
        effect_scale += (u16)((0x800 - effect_scale) / state->count);
        *(u16 *)(effect_data + 0x1c) = effect_scale;
        *(u16 *)(effect_data + 0x1e) = effect_scale;
    }

        frames_left = (u16)state->count - 1;
        state->count = frames_left;
        if ((frames_left << 16) > 0)
            return;

        object_index = 0;
        reset_marker = 0xff;
        do {
            object_entry = *(void **)(((u8 *)dungeon_actor_ring_anchor) + object_index * 4 + 0xac);
            if (object_entry != NULL) {
                object = object_entry;
                step_index = 1;
                *(u8 *)(object + 0x26) = *(u8 *)(object + 0x68);
                *(u8 *)(object + 0x27) = *(u8 *)(object + 0x69);
                do {
                    clear_slots_of_type(object, (s8)step_index);
                    step_index += 1;
                } while (step_index < 0x21);
                *(s16 *)(object + 0x64) = reset_marker;
                *(s32 *)(object + 0x1c) &= 0xfbffe107;
                cap_pending_actor_value_delta(object);
                *(s8 *)(object + 0x24) = reset_marker;
                *(u8 *)(object + 0x25) = *(u8 *)(object + 0x66);
                apply_entity_effects(object);
            }
            object_index += 1;
        } while (object_index < 2);

        state->count = 8;
        state->mode += 1;
        return;

    case 1:
        state->field50 = (s16)((u16)state->field50 +
            ((0xc0 - state->field50) / state->count));
        step_index = 0;
        do {
            grow_angle = state->field4e + 0x100;
            state->field4e = grow_angle;
            create_orbiting_color_particle(source->x, source->y, source->z, (s16)grow_angle,
                          state->field50, state->field58, 0x802020,
                          state->field48);
            step_index += 1;
        } while (step_index < 4);
        frames_left = (u16)state->count - 1;
        state->count = frames_left;
        if ((frames_left << 16) > 0)
            return;
        state->count = 4;
        state->mode += 1;
        return;

    case 2:
        state->field50 = (s16)((u16)state->field50 -
            (state->field50 / state->count));
        *(u8 *)(effect_data + 0xc) = (u8)(*(u8 *)(effect_data + 0xc) -
            (*(u8 *)(effect_data + 0xc) / state->count));
        *(u8 *)(effect_data + 0xd) = (u8)(*(u8 *)(effect_data + 0xd) -
            (*(u8 *)(effect_data + 0xd) / state->count));
        *(u8 *)(effect_data + 0xe) = (u8)(*(u8 *)(effect_data + 0xe) -
            (*(u8 *)(effect_data + 0xe) / state->count));
        step_index = 0;
        do {
            fade_angle = state->field4e + 0x100;
            state->field4e = fade_angle;
            create_orbiting_color_particle(source->x, source->y, source->z, (s16)fade_angle,
                          state->field50, state->field58, 0x802020,
                          state->field48);
            step_index += 1;
        } while (step_index < 4);
        frames_left = (u16)state->count - 1;
        state->count = frames_left;
        if ((frames_left << 16) > 0)
            return;
        *((u16 *)state - 1) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    }
}

/* Create an object at the tile center and initialize its rendering and state. */
void *create_familiar_restoration_effect(s32 tile_x, s32 tile_y, s32 z) {
    ObjectNodeHeader *object;
    ObjectPosition *position;
    SpriteFrameState *render_state;
    S_800C1A44_3 *object_state;

    object = allocate_list_node(0x12, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        object->update_callback = &D_800C1718[0];
        register_node(object, &clipped_sprite_renderer_address[0]);
        position = object->position;
        position->x.w.i = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
        position->y.w.i = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
        position->z.w.i = z;
        render_state = object->sprite;
        render_state->source = &familiar_restore_sprite_data[0];
        render_state->color.word = 0x808080;
        render_state->depth_bias = 8;
        object_state = ((void *)object) + 0x20;
        object_state->unk_4C = 8;
        object_state->unk_48 = 7;
    }
    return object;
}

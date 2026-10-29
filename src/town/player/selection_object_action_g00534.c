#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
/* G00534: selection object action. */
/* Original-file evidence (G00534): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80096098. */
#include "town/player/selection_object_action_g00534.h"
#include "town/player.h"

/* Returns whether the town state matches one of the accepted state pairs. */
s32 is_town_state_pair_accepted(void) {
    s32 isAcceptedStatePair;
    s16 primaryState;
    s16 secondaryState;

    isAcceptedStatePair = 0;
    primaryState = map_runtime_state.field_18;
    if (primaryState == 12) {
        secondaryState = map_runtime_state.field_1A;
        if (secondaryState == 6 ||
            secondaryState == 8 ||
            secondaryState == 9 ||
            secondaryState == 42 ||
            secondaryState == primaryState ||
            secondaryState == 43) {
            isAcceptedStatePair = 1;
        }
    }
    return isAcceptedStatePair;
}

/* Initialize the global context record using its two stored values. */
void initialize_town_context_action(void) {
    ObjectNodeHeader *context = &scene_object_list_anchor;
    initialize_scene_action_record((Rec_func_80094268_arg0 *)((u8 *)context + 0x20),
                  context->position,
                  context->sprite);
}

/* Checks the current selection, displays rejection messages, or creates and selects an object. */
void handle_selection_and_create_object(void) {
    Unk96134Work work;
    ObjectNodeHeader *data;
    u8 *context;
    u8 *object;
    ObjectPosition *position;
    SpriteFrameState *callback_data;
    void *created_entry;
    u32 state_code;
    s32 state_index;
    s32 state_is_12_or_13;
    s32 is_available;
    s32 mode;

    data = &scene_object_list_anchor;
    object = (u8 *)data + 0x20;
    context = item_menu_scene_state;
    position = data->position;
    callback_data = data->sprite;

    if (((S_80093894_1 *)context)->unk_08 == 3) {
        Unk96134Bytes *source = ((S_80093894_1 *)context)->unk_00;

        work.bytes.unk0 = source->unk0;
        state_code = source->unk1;
        work.bytes.unk1 = state_code;
        work.bytes.unk2 = source->unk2;
        work.bytes.unk3 = source->unk3;
        state_index = state_code - 0x12;
        state_is_12_or_13 = (u32)state_index < 2;
        is_available = is_unk_18_n_12_unk_1_a_between_n_37_n_41(state_index) == 1;

        switch (is_available) {
        case 0: {
            if (is_town_state_pair_accepted() != 0) {
                write_resource_command(D_80088C0C, 0x11);
            } else if (count_type_n_4_links_whose_state_not_n_1() >= 0x12) {
                write_resource_command(D_80088C48, 0x11);
            } else if (work.bytes.unk1 == 0x13) {
                write_resource_command(D_80088C8C, 0x11);
            } else {
                break;
            }
            set_item_selection_data_pointer(object, position, callback_data);
            town_player_action_callback = (void (*)(void *, void *, void *))&town_motion_action_address;
            town_interaction_pending = 0;
            return;
        }
        default: {
            if (work.bytes.unk1 != 0x13) {
                if (work.bytes.unk1 == 0x12) {
                    mode = find_target_byte_index_in_list();
                    if (get_first_free_four_byte_entry_index_n_1_none_available((void *)0x80010980, town_record_capacities[mode]) == -1) {
                        write_resource_command(D_80088CCC, 0x11);
                        set_item_selection_data_pointer(object, position, callback_data);
                        town_player_action_callback = (void (*)(void *, void *, void *))&town_motion_action_address;
                        town_interaction_pending = 0;
                        return;
                    }
                } else {
                    write_resource_command(D_80088D04, 0x11);
                    set_item_selection_data_pointer(object, position, callback_data);
                    town_player_action_callback = (void (*)(void *, void *, void *))&town_motion_action_address;
                    town_interaction_pending = 0;
                    return;
                }
            }
            break;
        }
        }

        work.pos.x = position->x.v;
        work.pos.y = position->y.v;
        work.pos.z = position->z.v + town_target_height_offset;
        mode = 0;
        if (state_is_12_or_13) {
            mode = is_available != 0;
        }
        created_entry = create_configured_object(((S_80093894_3 *)(&item_menu_scene_state))->unk_00, &work.pos, mode);
        if (created_entry != 0) {
            Unk96134State *state = (Unk96134State *)town_actor_control;
            void *next_object;

            next_object = (u8 *)created_entry + 0x20;
            ((S_80093894_4 *)object)->unk_2C = next_object;
            state->unk10 = next_object;
            state->unk18 = 0;
            initialize_actor_movement_interaction_action(object, position, callback_data);
            return;
        }
        initialize_scene_action_record((Rec_func_80094268_arg0 *)object, position, callback_data);
        return;
    }

    town_player_action_callback(object, position, callback_data);
}

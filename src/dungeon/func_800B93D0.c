#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"



extern s32 begin_mode_selected_item_action();
extern s32 begin_parameterized_actor_action();
extern s32 process_record_and_update_linked_state();
extern s32 clear_slot_and_update_linked_state();
extern s32 get_unused_text_buffer();
extern s32 expand_text_control_codes();
extern s32 func_80099290();
extern s32 append_typed_formatted_value();
extern s32 apply_type_based_entry_adjustments();
extern s32 display_formatted_context_message();
extern s32 copy_fullwidth_vowel_bytes();
extern s32 append_value_seven_suffix();
extern s32 display_text_with_fullwidth_adjustment();
extern s32 apply_item_effect_at_entity_position();
extern s32 display_actor_item_status_message();
extern s32 apply_actor_food_preference();

extern u8 D_80089364[];
extern u8 D_80089368[];
extern u8 D_800DD148[];
extern u8 D_800E110B[];
extern u8 D_800E112A[];
extern u8 D_800E1156[];
extern u8 D_800E116E[];

/* Applies an action to a target or held item and updates the action counter. */
s32 dispatch_selected_item_action(u32 target, u8 *action, s16 action_kind, s32 context) {
    EntityRec *state;
    u8 *item;
    s32 action_value;
    register s32 value;
    u32 choice_index;
    s32 call_context = context;
    s32 value_arg;
    s32 result_value;
    u8 item_type;

    if (action_kind == 0xD) {
        return process_record_and_update_linked_state(action, call_context);
    }

    state = D_800E3D7C;
    if (target == (u32)state) {
        state->unk_110 = action;
        begin_mode_selected_item_action(state, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), state);
        action[3] &= (u8)~0x20;
        return 0;
    }

    if (target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action, action_kind);
        if (apply_actor_food_preference(target, D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3))] & 3, 0) == 0) {
            apply_item_effect_at_entity_position(target, action);
            return 1;
        }
    } else {
        item = ((u8 *)state->unk_4C);
        if (item != 0) {
            if (!(action[3] & 0x20)) {
                state->unk_114 = 0x202080;
                begin_parameterized_actor_action(state, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), D_800DD148, 2);
                action[3] |= 0x20;
                return 0;
            }

            action_value = get_unused_text_buffer();
            value = action_value;
            item_type = item[1];
            if (item_type == 0xF || (item_type == 0x10 && item[0] == 2)) {
                if (!(item[3] & 0x40)) {
                    value = apply_type_based_entry_adjustments(item, action_value);
                    if ((s8)item[2] < 0x63) {
                        item[2] = (u8)(item[2] + 1);
                    }
                    value = append_value_seven_suffix(expand_text_control_codes(D_800E110B, value));
                    choice_index = value - 2;
                    value = expand_text_control_codes(D_80089364, value);
                    result_value = append_typed_formatted_value(item, value);
                    value_arg = value;
                    value = result_value;
                    copy_fullwidth_vowel_bytes(choice_index, value_arg);
                    value = expand_text_control_codes(D_80089368, value);
                } else {
                    value = expand_text_control_codes(D_800E112A, append_typed_formatted_value(item, action_value));
                }
            } else {
                value = expand_text_control_codes(D_800E1156, append_typed_formatted_value(item, value));
            }
            func_80099290(value);
            display_text_with_fullwidth_adjustment(action_value);
        } else {
            display_formatted_context_message(D_800E116E, call_context, action_kind);
        }
    }

    g_dungeon_status.unk_0A--;
    clear_slot_and_update_linked_state(action);
    return 1;
}

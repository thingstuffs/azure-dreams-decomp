#include "shared/entity_action_selectors.h"
#include "shared/dungeon_item_entries.h"
#include "shared/item_ids.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "dungeon/player/item.h"



extern s32 begin_parameterized_actor_action();
extern s32 process_record_and_update_linked_state();
extern void clear_slot_and_update_linked_state(DungeonItemEntry *slot);
extern void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
extern u8 * expand_text_control_codes(const u8 *src, u8 *dst);
extern u8 * clear_byte_and_advance(u8 *byte_ptr);
extern u8 *append_typed_formatted_value(DungeonItemEntry *data, u8 *buffer);
extern s32 display_formatted_context_message(); /* Unprototyped: one or three arguments; retail retains only the text context. */
extern void * copy_fullwidth_vowel_bytes();
extern void * append_value_seven_suffix(u8 *dst);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern s32 place_actor_item();
extern s32 display_actor_item_status_message();
extern s32 feed_actor_restore_mp();

extern u8 D_80089364[];
extern u8 D_80089368[];
extern u8 D_800DD148[];
extern u8 D_800E110B[];
extern u8 D_800E112A[];
extern u8 D_800E1156[];
extern u8 D_800E116E[];

/* Applies an action to a target or held item and updates the action counter. */
s32 dispatch_selected_item_action(u32 target, DungeonItemEntry *action, s16 action_kind, s32 context) {
    ActorRecord *state;
    DungeonItemEntry *item;
    void *action_value;
    register void *value;
    u32 choice_index;
    s32 call_context = context;
    void *value_arg;
    void *result_value;
    u8 item_type;

    if (action_kind == 0xD) {
        return process_record_and_update_linked_state(action, call_context);
    }

    state = dungeon_actor_ring_anchor;
    if (target == (u32)state) {
        ((PlayerRecord *)state)->pending_item_action = action;
        begin_mode_selected_item_action(state, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), state);
        action->unk_03 &= (u8)~0x20;
        return 0;
    }

    if (target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, action);
        if (feed_actor_restore_mp(target, entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3))] & 3, 0) == 0) {
            place_actor_item(target, action);
            return 1;
        }
    } else {
        item = state->unk_4C;
        if (item != 0) {
            if (!(action->unk_03 & 0x20)) {
                ((PlayerRecord *)state)->unk_114 = 0x202080;
                begin_parameterized_actor_action(state, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), D_800DD148, 2);
                action->unk_03 |= 0x20;
                return 0;
            }

            action_value = get_unused_text_buffer();
            value = action_value;
            item_type = item->kind;
            if (item_type == ITEM_KIND_SWORD || (item_type == ITEM_KIND_WAND && item->unk_00 == ITEM_TRAINED_WAND)) {
                if (!(item->unk_03 & 0x40)) {
                    value = apply_type_based_entry_adjustments(item, action_value);
                    if ((s8)item->unk_02 < 0x63) {
                        item->unk_02 = (u8)(item->unk_02 + 1);
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
            clear_byte_and_advance(value);
            display_text_with_fullwidth_adjustment(action_value);
        } else {
            display_formatted_context_message(D_800E116E, call_context, action_kind);
        }
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(action);
    return 1;
}

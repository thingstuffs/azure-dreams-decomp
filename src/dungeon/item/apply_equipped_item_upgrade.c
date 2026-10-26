#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "dungeon/player/item.h"

extern s32 begin_parameterized_actor_action();
struct DungeonItemEntry;
extern s32 process_record_and_update_linked_state(struct DungeonItemEntry *, s32);
extern s32 clear_slot_and_update_linked_state();
extern void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
extern u8 * expand_text_control_codes();
extern void * clear_byte_and_advance();
extern u8 * append_typed_formatted_value();
extern s32 display_formatted_context_message(); /* Unprototyped: one or three arguments; retail retains only the text context. */
extern void * copy_fullwidth_vowel_bytes();
extern void * append_value_seven_suffix();
extern s32 display_text_with_fullwidth_adjustment();
extern s32 place_actor_item();
extern s32 display_actor_item_status_message();
extern s32 feed_actor_restore_mp();

extern u8 D_8008936C[];
extern u8 D_80089370[];
extern u8 D_800DD158[];
extern u8 D_800E118C[];
extern u8 D_800E11AB[];
extern u8 D_800E11D7[];

/* Applies an item effect to its target and prepares the resulting message. */
s32 apply_equipped_item_upgrade(u32 target_addr, DungeonItemEntry *item, s16 effect_type, s32 effect_value) {
    u8 *actor;
    u8 *text_target;
    register void *text_cursor;
    u8 *linked_item;
    register void *text_start;


    if (effect_type == 0xD) {
        return process_record_and_update_linked_state(item, effect_value);
    }

    actor = ((u8 *)dungeon_actor_ring_anchor);
    if ((u8 *)target_addr == actor) {
        u8 item_flags;
        s32 result;

        ((PlayerRecord *)actor)->pending_item_action = item;
        begin_mode_selected_item_action(actor, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), actor);
        item_flags = item->unk_03;
        result = 0;
        item->unk_03 = item_flags & 0xDF;
        return result;
    }

    if (target_addr <= 0x9FFFFFFF) {
        display_actor_item_status_message(target_addr, item);
        if (feed_actor_restore_mp(target_addr, entity_action_selectors[*(u8 *)(target_addr + 0x13)] & 3, 0) == 0) {
            place_actor_item(target_addr, item);
            return 1;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        clear_slot_and_update_linked_state(item);
        return 1;
    }

    linked_item = *(u8 **)(actor + 0x50);
    if (linked_item != 0) {
        if (!(item->unk_03 & 0x20)) {
            u8 item_flags;
            register s32 result;

            ((PlayerRecord *)actor)->unk_114 = 0x802020;
            begin_parameterized_actor_action(actor, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), D_800DD158, 0);
            item_flags = item->unk_03;
            result = 0;
            item->unk_03 = item_flags | 0x20;
            return result;
        }

        {
            void *text_end;
            void *message_end;

            if (!(linked_item[3] & 0x40)) {
                void *next_cursor;

                text_start = get_unused_text_buffer();
                text_cursor = apply_type_based_entry_adjustments(linked_item, text_start);
                if (*(s8 *)(linked_item + 2) < 0x63) {
                    linked_item[2] = linked_item[2] + 1;
                }
                text_cursor = append_value_seven_suffix(expand_text_control_codes(D_800E118C, text_cursor));
                next_cursor = expand_text_control_codes(D_8008936C, text_cursor);
                text_target = text_cursor - 2;
                text_cursor = next_cursor;
                next_cursor = append_typed_formatted_value(linked_item, text_cursor);
                message_end = text_cursor;
                text_cursor = next_cursor;
                copy_fullwidth_vowel_bytes(text_target, message_end);
                clear_byte_and_advance(expand_text_control_codes(D_80089370, text_cursor));
            } else {
                text_start = get_unused_text_buffer();

                text_end = append_typed_formatted_value(linked_item, text_start);
                clear_byte_and_advance(expand_text_control_codes(D_800E11AB, text_end));
            }
        }
        display_text_with_fullwidth_adjustment(text_start);
    } else {
        display_formatted_context_message(D_800E11D7, effect_value, effect_type);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(item);
    return 1;
}

#include "dungeon/player/state.h"
#include "dungeon/actor/status.h"
#include "dungeon/system.h"
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
#include "dungeon/item/message.h"
#include "dungeon/player.h"

extern u8 *expand_text_control_codes(const u8 *source, u8 *buffer);
extern u8 *clear_byte_and_advance(u8 *byte_ptr);
extern u8 *append_typed_formatted_value(DungeonItemEntry *data, u8 *buffer);
struct DungeonItemEntry;
extern void * copy_fullwidth_vowel_bytes(void *dst, void *character);
extern void * append_value_seven_suffix(u8 *dst);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_8008936C[];
extern u8 D_80089370[];
extern u8 D_800DD158[];
extern u8 D_800E118C[];
extern u8 D_800E11AB[];
extern u8 D_800E11D7[];

/* Applies an item effect to its target and prepares the resulting message. */
s32 apply_equipped_item_upgrade(void *target_addr, DungeonItemEntry *item, s16 effect_type, void *effect_value) {
    u8 *actor;
    u8 *text_target;
    register void *text_cursor;
    DungeonItemEntry *linked_item;
    register void *text_start;


    if (effect_type == 0xD) {
        return process_record_and_update_linked_state(item, effect_value);
    }

    actor = ((u8 *)dungeon_actor_ring_anchor);
    if (target_addr == actor) {
        u8 item_flags;
        s32 result;

        ((PlayerRecord *)actor)->pending_item_action = item;
        begin_mode_selected_item_action(actor, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), actor);
        item_flags = item->unk_03;
        result = 0;
        item->unk_03 = item_flags & 0xDF;
        return result;
    }

    if ((u32)target_addr <= 0x9FFFFFFF) {
        display_actor_item_status_message(target_addr, item);
        if (feed_actor_restore_mp(target_addr, entity_action_selectors[*(u8 *)(target_addr + 0x13)] & 3, 0) == 0) {
            place_actor_item(target_addr, item);
            return 1;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        clear_slot_and_update_linked_state(item);
        return 1;
    }

    linked_item = *(DungeonItemEntry **)(actor + 0x50);
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

            if (!(linked_item->unk_03 & 0x40)) {
                void *next_cursor;

                text_start = get_unused_text_buffer();
                text_cursor = apply_type_based_entry_adjustments(linked_item, text_start);
                if (linked_item->unk_02 < 0x63) {
                    linked_item->unk_02 = (u8)linked_item->unk_02 + 1;
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
        display_formatted_context_message(D_800E11D7);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(item);
    return 1;
}

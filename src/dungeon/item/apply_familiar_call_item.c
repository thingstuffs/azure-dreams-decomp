#include "shared/entity_action_selectors.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/status.h"
#include "dungeon/data.h"
#include "dungeon/system.h"

#include "dungeon/player/item.h"
#include "dungeon/actor.h"
#include "engine/scene.h"
#include "dungeon/item/message.h"

extern s32 resolve_item_attack(struct DungeonItemEntry *, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
#include "dungeon/player/state/clear_slot_and_update_linked_state_api.h"
extern u8 *clear_byte_and_advance(u8 *byte_ptr);
extern void teleport_familiar_near_player(s32, s16); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Applies a target action or processes occupied player slots and updates the action count. */
s32 apply_familiar_call_item(ActorRecord *target, DungeonItemEntry *action, s16 action_type, s32 action_arg) {
    s32 slot;
    void *message_end;
    void *message_start;
    s32 slot_entry;
    u8 *global_page;

    if (action_type == 0xD) {
        return resolve_item_attack(action, action_arg);
    }

    global_page = (u8 *)0x800E0000;
    if (target == *(u8 **)(global_page + 0x3D7C)) {
        ((PlayerRecord *)target)->pending_item_action = action;
        begin_mode_selected_item_action(target, ((&view_reference_entity)), ((&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, action);
        if (feed_actor_restore_mp(target, entity_action_selectors[target->species] & 3, action) == 0) {
            place_actor_item(target, action);
            return 1;
        }
    } else {
        message_start = get_unused_text_buffer();
        message_end = message_start;
        if ((*(s32 *)(*(u8 **)(global_page + 0x3D7C) + 0xAC) != 0) ||
            (*(s32 *)(*(u8 **)(global_page + 0x3D7C) + 0xB0) != 0)) {
            if (has_enough_available_nodes(4) == 0) {
                return 0;
            }
            slot = 0;
            do {
                slot_entry = *(s32 *)(*(u8 **)(global_page + 0x3D7C) + 0xAC + slot * 4);
                if (slot_entry != 0) {
                    teleport_familiar_near_player(slot_entry, (s16)slot);
                }
                slot += 1;
            } while (slot < 2);
            message_end = expand_text_control_codes(familiar_call_text, message_end);
            play_sound_if_enabled(0x501);
        } else {
            message_end = expand_text_control_codes(familiar_call_text + 0x17, message_start);
        }
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message_start);
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_item_slot(action);
    return 1;
}

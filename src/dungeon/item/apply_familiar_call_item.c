#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 familiar_call_text[];

extern void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32, s16);
extern s32 feed_actor_restore_mp(void *, u16, s32);
extern void teleport_familiar_near_player(s32, s16);
extern s32 has_enough_available_runtime_nodes(s32);

/* Applies a target action or processes occupied player slots and updates the action count. */
s32 apply_familiar_call_item(void *target, s32 action, s16 action_type, s32 action_arg) {
    s32 slot;
    s32 message_end;
    s32 message_start;
    s32 slot_entry;
    u8 *global_page;

    if (action_type == 0xD) {
        return process_record_and_update_linked_state(action, action_arg);
    }

    global_page = (u8 *)0x800E0000;
    if (target == *(u8 **)(global_page + 0x3D7C)) {
        *(s32 *)((u8 *)target + 0x110) = action;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, action, action_type);
        if (feed_actor_restore_mp(target, entity_action_selectors[((u8 *)target)[0x13]] & 3, action) == 0) {
            place_actor_item(target, action);
            return 1;
        }
    } else {
        message_start = get_unused_text_buffer();
        message_end = message_start;
        if ((*(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xAC) != 0) ||
            (*(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xB0) != 0)) {
            if (has_enough_available_runtime_nodes(4) == 0) {
                return 0;
            }
            slot = 0;
            do {
                slot_entry = *(s32 *)((u8 *)*(u8 **)(global_page + 0x3D7C) + 0xAC + slot * 4);
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

    (((u16)g_dungeon_status.activity_counts.parts.pending_action_count))--;
    clear_slot_and_update_linked_state(action);
    return 1;
}

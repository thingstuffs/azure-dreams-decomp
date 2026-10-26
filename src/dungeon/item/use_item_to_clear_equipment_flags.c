#include "shared/actor_status_ids.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"

extern void clear_slots_of_type(void *, s32);
#include "dungeon/player/item.h"
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern u8 * append_typed_formatted_value(void *,u8 *);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void place_actor_item(void *, s32);
extern void display_actor_item_status_message(void *, s32);
extern s32 feed_actor_restore_mp(void *, s32, s32);

extern u8 D_800E1756[];
extern u8 D_800E176F[];
extern u8 D_800E1788[];

/* Applies a curse-removal item effect and reports changes to equipped items. */
s32 use_item_to_clear_equipment_flags(void *target, s32 item, s16 use_mode, s32 use_context)
{
    u8 *equipment;
    void *message_buf;
    s32 uncursed;

    if (use_mode == 13) {
        return process_record_and_update_linked_state(item, use_context);
    }

    if (target == ((u8 *)dungeon_actor_ring_anchor)) {
        *(s32 *)((u8 *)target + 0x110) = item;
        begin_mode_selected_item_action(target, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, item);
        if (feed_actor_restore_mp(target,
                          entity_action_selectors[((u8 *)target)[0x13]] & 3,
                          item) == 0) {
            place_actor_item(target, item);
            return 1;
        }
    } else {
        create_view_color_flash(0xC0C0C0, 0);
        play_sound_if_enabled(0x702);
        /*
         * BUG: cursed equipment sets the curse effect without a status slot. Clearing slot 8 leaves that
         * effect active; clear the effect flag too.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        clear_slots_of_type(target, STATUS_CURSE);

        uncursed = 0;
        equipment = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 0x4C);
        if (equipment[1] != 0 && (equipment[3] & 0x40) != 0) {
            equipment[3] &= 0xBF;
            message_buf = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(D_800E1756,
                                        append_typed_formatted_value(equipment, message_buf)));
            display_text_with_fullwidth_adjustment(message_buf);
            uncursed = 1;
        }

        equipment = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 0x50);
        if (equipment[1] != 0 && (equipment[3] & 0x40) != 0) {
            equipment[3] &= 0xBF;
            message_buf = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(D_800E176F,
                                        append_typed_formatted_value(equipment, message_buf)));
            display_text_with_fullwidth_adjustment(message_buf);
            uncursed = 1;
        }

        if (uncursed == 0) {
            message_buf = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(D_800E1788, message_buf));
            display_text_with_fullwidth_adjustment(message_buf);
        }
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state(item);
    return 1;
}

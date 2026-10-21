#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern s32 begin_mode_selected_item_action();
extern s32 process_record_and_update_linked_state();
extern void clear_slot_and_update_linked_state();
extern s32 get_unused_text_buffer();
extern s32 expand_text_control_codes();
extern void clear_byte_and_advance();
extern void display_text_with_fullwidth_adjustment();
extern void place_actor_item();
extern void display_actor_item_status_message();
extern s32 feed_actor_restore_mp();
extern void create_view_color_flash();

extern u8 D_800E1567[];
extern u8 floor_objects[];


/* Apply an entity event or mark eligible slots, then finish the event. */
s32 make_floor_traps_invisible(EntityRec *entity, s32 event, s16 event_type, s32 event_arg) {
    s32 message_arg;
    u8 *slot;
    u8 *event_state;
    u16 *pending_count;
    s32 message_buf;
    s32 message_end;
    s32 slot_index;

    if (event_type == 0xD) {
        return process_record_and_update_linked_state(event, event_arg);
    }
    if (entity == ((u8 *)dungeon_actor_ring_anchor)) {
        entity->unk_110 = event;
        begin_mode_selected_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.unk_000, entity);
        return 0;
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        display_actor_item_status_message(entity, event);
        if (feed_actor_restore_mp(
                entity,
                entity_action_selectors[(*(u8 *)((u8 *)&entity->unk_10 + 3))] & 3,
                event) == 0) {
            place_actor_item(entity, event);
            return 1;
        }
    } else {
        create_view_color_flash(0xC02020, 1);
        message_buf = get_unused_text_buffer();

        message_arg = message_buf;
        if (reference_tile_object.room_index >= 0) {
            for (slot_index = 0; slot_index < 0x20; slot_index++) {
                slot = &floor_objects[slot_index * 4];
                if (slot[1] != 0 && slot[0] != 0) {
                    if (!(slot[3] & 0x40)) {
                        slot[3] |= 0x80;
                    }
                }
            }

            clear_byte_and_advance(message_arg);
        } else {
            message_end = expand_text_control_codes(D_800E1567, message_buf);
            clear_byte_and_advance(message_end);
        }
        display_text_with_fullwidth_adjustment(message_buf);
    }
    event_state = (u8 *)&g_dungeon_status.turn_scale;
    pending_count = (u16 *)(event_state + 0xA);
    *pending_count = *pending_count - 1;
    clear_slot_and_update_linked_state(event);
    return 1;
}

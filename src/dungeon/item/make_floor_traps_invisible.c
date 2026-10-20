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
extern void func_80099290();
extern void display_text_with_fullwidth_adjustment();
extern void apply_item_effect_at_entity_position();
extern void display_actor_item_status_message();
extern s32 apply_actor_food_preference();
extern void create_view_color_flash();

extern u8 D_800E1567[];
extern u8 D_800E3648[];


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
    if (entity == ((u8 *)D_800E3D7C)) {
        entity->unk_110 = event;
        begin_mode_selected_item_action(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        display_actor_item_status_message(entity, event);
        if (apply_actor_food_preference(
                entity,
                entity_action_selectors[(*(u8 *)((u8 *)&entity->unk_10 + 3))] & 3,
                event) == 0) {
            apply_item_effect_at_entity_position(entity, event);
            return 1;
        }
    } else {
        create_view_color_flash(0xC02020, 1);
        message_buf = get_unused_text_buffer();

        message_arg = message_buf;
        if (D_80082E80.room_index >= 0) {
            for (slot_index = 0; slot_index < 0x20; slot_index++) {
                slot = &D_800E3648[slot_index * 4];
                if (slot[1] != 0 && slot[0] != 0) {
                    if (!(slot[3] & 0x40)) {
                        slot[3] |= 0x80;
                    }
                }
            }

            func_80099290(message_arg);
        } else {
            message_end = expand_text_control_codes(D_800E1567, message_buf);
            func_80099290(message_end);
        }
        display_text_with_fullwidth_adjustment(message_buf);
    }
    event_state = (u8 *)&g_dungeon_status.turn_scale;
    pending_count = (u16 *)(event_state + 0xA);
    *pending_count = *pending_count - 1;
    clear_slot_and_update_linked_state(event);
    return 1;
}

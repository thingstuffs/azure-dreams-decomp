#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 D_800C152C[];
extern u8 D_800DF514[];
extern u8 D_800E14A6[];

s32 process_record_and_update_linked_state(s32, s32);
void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
void display_actor_item_status_message(void *, s32);
s32 apply_actor_food_preference(void *, s32, s32);
void apply_item_effect_at_entity_position(void *, s32);
s32 create_five_point_effect(s16 tile_x, s16 tile_y, s16 pos_z, void *transform_data, s16 scale, s32 setup_word_5c, s32 setup_word_60);
void display_formatted_context_message(void *);
void clear_slot_and_update_linked_state(s32);

/* Dispatches a target action according to its type and address. */
s32 use_item_to_draw_full_recovery_circle(void *target, s32 action_id, s16 action_type, s32 action_arg) {
    void *target_data;

    if (action_type == 0xD) {
        return process_record_and_update_linked_state(action_id, action_arg);
    }
    if (target == D_800E3D7C) {
        *(s32 *)((u8 *)target + 0x110) = action_id;
        begin_mode_selected_item_action(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), 0);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, action_id);
        if (apply_actor_food_preference(target, entity_action_selectors[*(u8 *)((u8 *)target + 0x13)] & 3, action_id) == 0) {
            apply_item_effect_at_entity_position(target, action_id);
            return 1;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    } else {
        target_data = *(void **)((u8 *)target - 0x14);
        if (create_five_point_effect(*(u8 *)((u8 *)target_data + 0x24), *(u8 *)((u8 *)target_data + 0x25),
            *(s16 *)((u8 *)target + 0x88), &D_800DF514, 0x2800, 0x802020, &D_800C152C) == 0) {
            return 0;
        }
        display_formatted_context_message(&D_800E14A6);
    }
    clear_slot_and_update_linked_state(action_id);
    return 1;
}

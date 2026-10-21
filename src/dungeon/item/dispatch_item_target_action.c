#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 process_record_and_update_linked_state(void *request, s32 record_data);
extern s32 clear_slot_and_update_linked_state(void *slot);
extern s32 display_formatted_context_message(void *context, s32 first_input, s32 second_input);
extern s32 apply_item_effect_at_entity_position(void *object_context, void *target);
extern s32 display_actor_item_status_message(void *actor, void *item, s32 buffer_arg2);
extern s32 feed_actor_restore_mp(void *state, s32 mode, void *item);

typedef struct {
    s16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup D_80073414[];
extern u8 D_800E101C;

/* Dispatch an item action using its category flags and target selector, then decrement the counter. */
s32 dispatch_item_target_action(void *target, void *item, s16 action_type, s32 action_value) {
    s32 item_index;
    s32 category_index;
    DungeonItem *item_entries;
    u16 *selector_table;
    s32 selector;
    s16 item_flags;
    u16 selector_bits;

    if (action_type == 0xD) {
        return process_record_and_update_linked_state(item, action_value);
    }
    if ((s32) target == ((s32)D_800E3D7C)) {
        *(void **)((u8 *)target + 0x110) = item;
        begin_mode_selected_item_action(target, ((s32 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, item, action_type);
        category_index = *((u8 *)item + 1);
        item_index = *((u8 *)item + 0);
        item_entries = D_80073414[category_index].entries;
        item_flags = item_entries[item_index].flags;
        if (!(item_flags & 0x8000)) {
            selector = entity_action_selectors[*((u8 *)target + 0x13)] & 3;
        } else {
            selector_table = entity_action_selectors;
            selector_bits = selector_table[*((u8 *)target + 0x13)];
            selector = (selector_bits >> 4) & 3;
        }
        if (feed_actor_restore_mp(target, selector, item) == 0) {
            apply_item_effect_at_entity_position(target, item);
            return 1;
        }
        clear_slot_and_update_linked_state(item);
    } else {
        display_formatted_context_message((u8 *)&D_800E101C, action_value, action_type);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    return 1;
}

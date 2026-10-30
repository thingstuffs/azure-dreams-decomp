#include "shared/entity_action_selectors.h"
#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

#include "dungeon/player/item.h"
#include "dungeon/actor.h"

extern s32 process_record_and_update_linked_state(struct DungeonItemEntry *request, s32 record_data); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void clear_slot_and_update_linked_state(DungeonItemEntry *slot);
extern s32 display_formatted_context_message(void *context, s32 first_input, s32 second_input);
extern void place_actor_item(void *object_context, struct DungeonItemEntry *target);
extern s32 display_actor_item_status_message(void *actor, struct DungeonItemEntry *item, s32 unused_2);

typedef struct {
    s16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup item_category_groups[];
extern u8 D_800E101C;

/* Dispatch an item action using its category flags and target selector, then decrement the counter. */
s32 dispatch_item_target_action(void *target, DungeonItemEntry *item, s16 action_type, s32 action_value) {
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
    if (target == (dungeon_actor_ring_anchor)) {
        ((PlayerRecord *)target)->pending_item_action = item;
        begin_mode_selected_item_action(target, ((s32 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), target);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        display_actor_item_status_message(target, item, action_type);
        category_index = item->kind;
        item_index = item->unk_00;
        item_entries = item_category_groups[category_index].entries;
        item_flags = item_entries[item_index].flags;
        if (!(item_flags & 0x8000)) {
            selector = entity_action_selectors[*((u8 *)target + 0x13)] & 3;
        } else {
            selector_table = entity_action_selectors;
            selector_bits = selector_table[*((u8 *)target + 0x13)];
            selector = (selector_bits >> 4) & 3;
        }
        if (feed_actor_restore_mp(target, selector, item) == 0) {
            place_actor_item(target, item);
            return 1;
        }
        clear_slot_and_update_linked_state(item);
    } else {
        display_formatted_context_message((u8 *)&D_800E101C, action_value, action_type);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
    return 1;
}

#include "common.h"
#include "shared/item_ids.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "town.h"
#include "town/shop/group_index.h"
#include "town/shop.h"

typedef struct S_800B2400_2 {
    u8 pad_00[0x1C];
    TownGroupIndex group;
} S_800B2400_2;

/* Move the selected item to the destination list and return a status code. */
s32 move_item_to_list(ItemMenuInputObject *state) {
    u8 *row_base = (u8 *)state;
    DungeonItemEntry *new_item;
    s32 dest_capacity;
    s32 source_index;
    s32 remove_index;
    s32 result;
    S_800B2400_2 *source_list;
    DungeonItemEntry **dest_slot;
    DungeonItemEntry *selected_item;
    S_800B2400_2 *dest_list;

    dest_capacity = get_mode_value_or_default(state->destination_index);
    dest_list = (S_800B2400_2 *)(row_base + state->destination_index * sizeof(TownGroupIndex));
    if (dest_list->group.value >= dest_capacity) {
        result = 1;
        if (state->preset == 0) {
            result = 2;
        }
    } else {
        source_index = state->source_index;
        source_list = (S_800B2400_2 *)(row_base + source_index * sizeof(TownGroupIndex));
        if (source_list->group.value == 0) {
            result = 4;
        } else {
            selected_item = state->lists[source_index][source_list->group.selection];
            if (state->preset == 0 && selected_item->kind == ITEM_KIND_FAMILIAR) {
                result = 3;
            } else {
                dest_slot = state->lists[state->destination_index]
                    + count_nonzero_entries(state->lists[state->destination_index]);
                new_item = find_unused_pool_slot(state->lists[state->destination_index],
                    state->destination_index, dest_capacity);
                *new_item = *selected_item;
                dest_slot[0] = new_item;
                dest_slot[1] = 0;
                remove_index = state->source_index;
                remove_selected_entry_from_list(state->lists[remove_index], state->groups[remove_index].selection);
                state->groups[state->source_index].value--;
                get_zero_based_group_index(&state->groups[state->source_index]);
                state->groups[state->destination_index].value++;
                get_zero_based_group_index(&state->groups[state->destination_index]);
                result = 0;
            }
        }
    }
    return result;
}

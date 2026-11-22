/* Resource entry initialization g01156.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800B5204, CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C.
 */
#include "shared/object_node.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "shared/object_flags.h"
#include "town/shop.h"
#include "engine/resource.h"

/* Collect pointers to enabled entries and terminate the list with 0. */
void collect_enabled_entry_pointers(DungeonItemEntry **entries, s32 entry_count) {
    DungeonItemEntry **output;
    DungeonItemEntry *entry;
    s32 entry_index;

    output = entries;
    entry_index = 0;
    if (entry_count > 0) {
        entry = (DungeonItemEntry *)0x80011F80;
        do {
            if (entry->kind != 0) {
                *output = entry;
                output += 1;
            }
            entry_index += 1;
            entry += 1;
        } while (entry_index < entry_count);
    }
    *output = 0;
}

/* Count the item pointers before the list terminator. */
s32 count_nonzero_entries(DungeonItemEntry **entries) {
    DungeonItemEntry **entry;
    s32 count;

    entry = entries;
    count = 0;
    if (*entry != 0) {
        do {
            entry += 1;
            count += 1;
        } while (*entry != 0);
    }
    return count;
}

/* Acquires a resource and initializes its associated state on success. */
DungeonItemEntry **allocate_item_pointer_list(ItemMenuInputObject *state) {
    DungeonItemEntry **resourceHandle;
    s32 resourceConfig;

    resourceHandle = allocate_node_body(0x100);
    state->lists[1] = resourceHandle;
    if (resourceHandle != 0) {
        resourceConfig = get_mode_selected_value();
        state->count = resourceConfig;
        collect_enabled_entry_pointers(state->lists[1], resourceConfig);
        state->groups[1].value = count_nonzero_entries(state->lists[1]);
        get_zero_based_group_index(&state->groups[1]);
    }
    return state->lists[1];
}

/* Copy leading item values to the fixed output buffer and zero the remaining slots. */
void write_back_item_table(ItemMenuInputObject *table) {
    DungeonItemEntry values[64];
    DungeonItemEntry *item;
    s32 i;
    u8 *page;

    if (table->lists[1] != 0) {
        for (i = 0; i < table->count; i++) {
            item = table->lists[1][i];
            if (item == 0) {
                break;
            }
            values[i] = *item;
        }
        page = (u8 *)0x80010000;
        for (i = 0; i < table->count; i++) {
            if (table->lists[1][i] == 0) {
                break;
            }
            ((DungeonItemEntry *)(page + 0x1F80))[i] = values[i];
        }
        for (; i < table->count; i++) {
            ((s32 *)0x80011F80)[i] = 0;
        }
        flag_object_for_removal(table->lists[1]);
    }
}

/* Initialize the record table pointer, stored value, and group index. */
void init_item_list_group(ItemMenuInputObject *record) {
    record->lists[0] = (DungeonItemEntry **)0x8001029C;
    record->groups[0].value = func_800B0718();
    get_zero_based_group_index(&record->groups[0]);
}

/* Initializes the task and resources for open_twin_souko. */
void * open_twin_souko(s32 option) {
    StorageMenuNode *resource_08;
    ItemMenuObjectNode *resource_00;
    StorageMenuNode *resource_04;
    ItemMenuInputObject *state;
    void *task;

    task = allocate_flagged_object_node(0);
    state = task + 0x20;
    if (task == 0 ||
        (init_item_list_group(state),
         allocate_item_pointer_list(state) != 0 &&
         (store_shop_display_preset(state, 0),
          resource_08 = create_storage_item_menu(task),
          state->destination_menu = resource_08,
          resource_08 != 0) &&
         (resource_00 = func_800B3924(task),
          ((S_800B2BA0_1 *)task)->unk_20 = resource_00,
          resource_00 != 0) &&
         (resource_04 = create_storage_owner_menu(task),
          state->source_menu = resource_04,
          resource_04 != 0))) {
        if (task != 0) {
            came_bright_set(5);
            obj_disp23_cancel_sw_set(1);
            state->option = option;
            NODE_HEADER(state)->update_callback = &handle_item_move_menu_input;
        }
        return task;
    }
    close_item_move_menu(state);
    return 0;
}

/* Apply three record values, set status flags, and process the record. */
void close_item_move_menu(ItemMenuInputObject *record)
{
    func_800B3A80((s32)record->item_menu_object);
    release_storage_owner_menu(record->source_menu);
    release_storage_item_menu(record->destination_menu);
    NODE_HEADER(record)->flags |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    came_bright_set(3);
    obj_disp23_cancel_sw_set(0);
    write_back_item_table(record);
}

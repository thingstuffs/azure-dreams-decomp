/* Resource entry initialization g01156.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01156 - CL:town/func_800B5204, CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C.
 */
#include "shared/object_node.h"
#include "town/shop/resource_entry_initialization_g01156.h"
#include "shared/object_flags.h"

/* Collect pointers to enabled entries and terminate the list with 0. */
void collect_enabled_entry_pointers(s32 *entries, s32 entry_count) {
    s32 *output;
    s8 *entry;
    s32 entry_index;

    output = entries;
    entry_index = 0;
    if (entry_count > 0) {
        entry = (s8 *)0x80011F80;
        do {
            if (((S_800B2964_0 *)entry)->unk_01 != 0) {
                *output = (s32) entry;
                output += 1;
            }
            entry_index += 1;
            entry += 4;
        } while (entry_index < entry_count);
    }
    *output = 0;
}

/* Counts entries in a zero-terminated integer array. */
s32 count_nonzero_entries(s32 *entries) {
    s32 *entry;
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
s32 acquire_resource_and_initialize_state(void *state) {
    s32 resourceHandle;
    s32 resourceConfig;

    resourceHandle = create_callback_pair_default(0x100);
    ((S_800B29D0_0 *)state)->unk_40 = resourceHandle;
    if (resourceHandle != 0) {
        resourceConfig = get_mode_selected_value();
        ((S_800B29D0_0 *)state)->unk_44 = resourceConfig;
        collect_enabled_entry_pointers((s32 *)(((S_800B29D0_0 *)state)->unk_40), resourceConfig);
        ((S_800B29D0_0 *)state)->unk_38 = count_nonzero_entries((s32 *)(((S_800B29D0_0 *)state)->unk_40));
        get_zero_based_group_index(state + 0x2C);
    }
    return ((S_800B29D0_0 *)state)->unk_40;
}

/* Copy leading item values to the fixed output buffer and zero the remaining slots. */
void fill_item_value_buffer(S_800B52D8 *table) {
    UA32 values[64];
    UA32 *item;
    s32 i;
    u8 *page;

    if (table->items != 0) {
        for (i = 0; i < table->count; i++) {
            item = table->items[i];
            if (item == 0) {
                break;
            }
            values[i] = *item;
        }
        page = (u8 *)0x80010000;
        for (i = 0; i < table->count; i++) {
            if (table->items[i] == 0) {
                break;
            }
            ((UA32 *)(page + 0x1F80))[i] = values[i];
        }
        for (; i < table->count; i++) {
            ((s32 *)0x80011F80)[i] = 0;
        }
        flag_object_for_removal(table->items);
    }
}

/* Initialize the record table pointer, stored value, and group index. */
void initialize_record_table_and_group(void *record) {
    ((S_800B2B60_0 *)record)->unk_3C = (u32 *)0x8001029C;
    ((S_800B2B60_0 *)record)->unk_28 = func_800B0718();
    get_zero_based_group_index(record + 0x1C);
}

/* Initializes the task and resources for open_twin_souko. */
void * open_twin_souko(s32 option) {
    s32 resource_08;
    ItemMenuObjectNode *resource_00;
    s32 resource_04;
    void *state;
    void *task;

    task = allocate_flagged_object_node(0);
    state = task + 0x20;
    if (task == 0 ||
        (initialize_record_table_and_group(state),
         acquire_resource_and_initialize_state(state) != 0 &&
         (store_table_index_and_entry_bytes(state, 0),
          resource_08 = create_storage_item_menu(task),
          ((S_800B2BA0_0 *)state)->unk_08 = resource_08,
          resource_08 != 0) &&
         (resource_00 = func_800B3924(task),
          ((S_800B2BA0_1 *)task)->unk_20 = resource_00,
          resource_00 != 0) &&
         (resource_04 = create_storage_owner_menu(task),
          ((S_800B2BA0_0 *)state)->unk_04 = resource_04,
          resource_04 != 0))) {
        if (task != 0) {
            came_bright_set(5);
            obj_disp23_cancel_sw_set(1);
            ((S_800B2BA0_0 *)state)->unk_48 = option;
            ((ObjectNodeHeader *)((u8 *)state - 0x20))->update_callback = &handle_item_menu_input_2;
        }
        return task;
    }
    apply_record_values_and_process_record(state);
    return 0;
}

/* Apply three record values, set status flags, and process the record. */
void apply_record_values_and_process_record(void *record)
{
    func_800B3A80(*(s32 *)((s8 *)record + 0));
    process_object_resources_and_high_flag(*(s32 *)((s8 *)record + 4));
    refresh_object_components_and_high_flag(*(s32 *)((s8 *)record + 8));
    *(u16 *)((s8 *)record - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    came_bright_set(3);
    obj_disp23_cancel_sw_set(0);
    fill_item_value_buffer(record);
}

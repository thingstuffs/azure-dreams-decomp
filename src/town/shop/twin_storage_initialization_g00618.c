/* Twin storage initialization (G00618). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5270, CL:town/func_800B52D8, CL:town/func_800B5400, CL:town/func_800B550C. */
#include "town/shop/twin_storage_initialization_g00618.h"

/* Initialize the record table pointer, stored value, and group index. */
void initialize_record_table_and_group(void *record) {
    ((S_800B2B60_0 *)record)->unk_3C = (u32 *)0x8001029C;
    ((S_800B2B60_0 *)record)->unk_28 = func_800B0718();
    get_zero_based_group_index(record + 0x1C);
}

/* Initializes the task and resources for open_twin_souko. */
s32 open_twin_souko(s32 option) {
    s32 resource_08;
    s32 resource_00;
    s32 resource_04;
    void *state;
    void *task;

    task = allocate_flagged_object_node(0);
    state = task + 0x20;
    if (task == 0 ||
        (initialize_record_table_and_group(state),
         acquire_resource_and_initialize_state(state) != 0 &&
         (store_table_index_and_entry_bytes(state, 0),
          resource_08 = func_800B4588(task),
          ((S_800B2BA0_0 *)state)->unk_08 = resource_08,
          resource_08 != 0) &&
         (resource_00 = func_800B3924(task),
          ((S_800B2BA0_1 *)task)->unk_20 = resource_00,
          resource_00 != 0) &&
         (resource_04 = func_800B4F60(task),
          ((S_800B2BA0_0 *)state)->unk_04 = resource_04,
          resource_04 != 0))) {
        if (task != 0) {
            came_bright_set(5);
            obj_disp23_cancel_sw_set(1);
            ((S_800B2BA0_0 *)state)->unk_48 = option;
            ((S_800B2BA0_0_pre *)state)[-1].unk_00 = &handle_item_menu_input_2;
        }
        return (s32)task;
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
    *(u16 *)((s8 *)record - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
    came_bright_set(3);
    obj_disp23_cancel_sw_set(0);
    fill_item_value_buffer(record);
}

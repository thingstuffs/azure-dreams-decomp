#include "shared/object_node.h"
#include "common.h"
s32 obj_disp23_cancel_sw_set(s32 cancel_switch);                     /* extern */
void came_bright_set(u32 brightness);                     /* extern */
void store_table_index_and_entry_bytes();             /* extern */
s32 acquire_resource_and_initialize_state();                          /* extern */
void initialize_record_table_and_group();                      /* extern */
void apply_record_values_and_process_record();                      /* extern */
s32 func_800B3924();                          /* extern */
s32 func_800B4588();                          /* extern */
s32 func_800B4F60();                          /* extern */
void handle_item_menu_input_2(u8 *menu);


typedef struct S_800B2BA0_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800B2BA0_0_pre;

typedef struct S_800B2BA0_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x3C];
    s32 unk_48;
} S_800B2BA0_0;

typedef struct S_800B2BA0_1 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B2BA0_1;

/* Initializes the task and resources for open_twin_souko. */
s32 open_twin_souko(s32 option) {
    s32 resource_08;
    s32 resource_00;
    s32 resource_04;
    void *state;
    void *task;

    task = func_8003FC64(0);
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

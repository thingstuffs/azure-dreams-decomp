/* Item index flags and its file-private helper. */
#include "common.h"
#include "shared/object_flags.h"
/* Sibling of w_800510DC.c / code9.c / code10.c: sets the "used"/flag bit
 * (0x8000) on a 16-bit flags field 2 bytes before a0, and on the global
 * 32-bit flags word D_800814A0. Here the target reuses a SINGLE lui-computed
 * base register across both the load and the store of D_800814A0 (no second
 * lui before the store), the "array/struct >8B" codegen shape noted in
 * w_800510DC.c rather than the two-independent-lui -G0 shape. */

extern void copy_a_pointer_table_initializes_extra_data_tag_hex_13(void *a0, void *a1);
extern void unlink_scene_list_node(void *a0);
extern void unlink_node_if_registered(void *a0);
extern void func_80033D08(void *a0);
extern s32 get_item_chk();

static void update_the_data_set_local_global_flags(void *object, void *update_data)
{
    copy_a_pointer_table_initializes_extra_data_tag_hex_13(update_data, (u8 *)object + 0x4C);
    unlink_scene_list_node(object);
    unlink_node_if_registered(object);
    *(u16 *)((u8 *)object - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
}

s32 process_the_item_index_available_report_success(s32 context) {
    s32 item_index;

    item_index = get_item_chk();
    if (item_index == -1) {
        return 0;
    }
    update_the_data_set_local_global_flags(context, item_index);
    return 1;
}

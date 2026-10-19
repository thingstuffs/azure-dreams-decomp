/* Object setup links and its file-private helper. */
#include "common.h"
typedef struct Entry {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
} Entry;
extern void set_object_value_and_negation(void *object, s32 value);
#include "m2c_compat.h"
void pass_global_data_with_fixed_args();
/* extern */
s32 link_indexed_entry_chain();
/* extern */
void set_attached_object_position(s32 *, s32);
/* extern */
static void initialize_nine_entry_links();

static void initialize_nine_entry_links(void *entry_data, s32 enable_flag) {
    s32 entry_index;
    s32 record_offset;

    for (entry_index = 0; entry_index < 9; entry_index++) {
        ((Entry *)*(s8 **)((s8 *)entry_data + 0))[entry_index].field4 =
            (s32)(((Entry *)*(s8 **)((s8 *)entry_data + 4)) + entry_index);
    }

    entry_index = 0;
    record_offset = entry_index;
    for (; entry_index < 9; entry_index++, record_offset += 0xC) {
        ((Entry *)*(s8 **)((s8 *)entry_data + 0))[entry_index].field8 =
            (s32)(*(s8 **)((s8 *)entry_data + 8) + record_offset);
    }

    for (entry_index = 0; entry_index < 9; entry_index++) {
        ((Entry *)*(s8 **)((s8 *)entry_data + 0))[entry_index].field0 =
            ((s32 *)*(s8 **)((s8 *)entry_data + 0xC))[entry_index];
    }

    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x12) = 0x5F;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x1E) = 0x61;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x44) = -0xF;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 4) + 0x88) = 0x9A;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 4) + 0x8A) = 0x69;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x68) = -0xF;
    *(s16 *)(*(s8 **)((s8 *)entry_data + 8) + 0x60) = 0x800;

    if (enable_flag != 0) {
        return set_object_value_and_negation(entry_data, 0x400);
    }
    set_object_value_and_negation(entry_data, 0);
}

s32 run_object_setup_and_finalize(s32 *value_ptr, s32 context) {
    s32 result;

    set_attached_object_position(value_ptr, context);
    initialize_nine_entry_links(value_ptr, context);
    result = link_indexed_entry_chain(*value_ptr, context);
    pass_global_data_with_fixed_args();
    return result;
}

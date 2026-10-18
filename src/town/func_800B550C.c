#include "common.h"
#include "shared/object_flags.h"

extern void obj_disp23_cancel_sw_set(u32);
extern void came_bright_set(s32);
extern void func_800B2A38(void *);
extern void func_800B3A80(s32);
extern void refresh_object_components_and_high_flag(u8 *object);
extern void process_object_resources_and_high_flag(u8 *object);

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
    func_800B2A38(record);
}

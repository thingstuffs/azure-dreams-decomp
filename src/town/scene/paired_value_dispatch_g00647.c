/* Paired value dispatch (G00647).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C3620, PD:town/engine:800D25C0.
 */
#include "town/scene/paired_value_dispatch_g00647.h"

/* Run setup, assign the retrieved object handler when present, and return -1. */
s32 run_setup_and_get_object_handler(s32 context, s32 value, s32 options) {
    S_800C0C48_0 *object;

    process_paired_arrays_until_terminator();
    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        object->unk_10 = &D_800C0C28;
    }
    return -1;
}

/* Dispatch paired table values according to each entry's kind and record flag. */
void dispatch_paired_table_values(void)
{
    s32 i = 0;
    u8 *table_base;
    u8 entry_kind;

    if (paired_scene_flag_ids[0] != 0) {
        table_base = (u8 *)0x80010000U;
        do {
            entry_kind = table_base[i * 4 + 0x981];
            if (entry_kind != 0) {
                if (entry_kind == 0x13 && table_base[i * 0x54 + 0xAC4] != 0) {
                    clear_resident_bitmap_bit(paired_scene_flag_ids[i]);
                    set_resident_bitmap_bit(scene_resident_flag_ids[i]);
                } else {
                    set_resident_bitmap_bit(paired_scene_flag_ids[i]);
                    clear_resident_bitmap_bit(scene_resident_flag_ids[i]);
                }
            } else {
                clear_resident_bitmap_bit(paired_scene_flag_ids[i]);
                clear_resident_bitmap_bit(scene_resident_flag_ids[i]);
            }
            i++;
        } while (paired_scene_flag_ids[i] != 0);
    }
}

/* Processes paired array entries until the first array's zero terminator. */
void process_paired_arrays_until_terminator(void) {

    if (paired_scene_flag_ids[0] != 0) {
        s32 entryIndex = 0;

        do {
            clear_resident_bitmap_bit(paired_scene_flag_ids[entryIndex]);
            clear_resident_bitmap_bit(scene_resident_flag_ids[entryIndex]);
            entryIndex++;
        } while (paired_scene_flag_ids[entryIndex] != 0);
    }
}

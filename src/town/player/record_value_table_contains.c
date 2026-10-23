#include "common.h"
#include "shared/record_ptrs.h"


/* Return whether any of the 34 entries contains the requested byte value. */
s32 record_value_table_contains(s32 target_value) {
    s32 entry_index;
    void *entry;

    entry = (void *)(*(s32 *)((s8 *)town_scene_root + 0x38) + 0x33A4);
    for (entry_index = 0; entry_index < 0x22; entry_index++) {
        if (*(u8 *)((s8 *)entry + 1) == target_value) {
            return 1;
        }
        entry += 2;
    }
    return 0;
}

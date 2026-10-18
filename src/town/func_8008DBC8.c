#include "common.h"

extern s32 resource_value_table_contains(s32 target_value);

extern u8 D_800CF828[15];
extern s32 D_800CF838[16];

/* Returns whether any of the 15 selected entries passes resource_value_table_contains. */
s32 has_listed_resource_in_slots(void) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 15; entry_index++) {
        if (resource_value_table_contains(D_800CF838[D_800CF828[entry_index]]) != 0) {
            return 1;
        }
    }

    return 0;
}

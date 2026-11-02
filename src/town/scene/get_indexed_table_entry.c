#include "common.h"
#include "town/scene.h"
#include "town/player.h"

extern s32 D_80019144[];

/* Return the indexed table value, using entry 40 for indices of 41 or greater. */
s32 get_indexed_table_entry_40(void) {
    s32 index = get_linked_record_field_2_d_60();
    s32 *value_table = D_80019144;
    s32 *value_entry;

    if (index < 0x29) {
        value_entry = &value_table[index];
    } else {
        value_entry = &value_table[40];
    }
    return *value_entry;
}

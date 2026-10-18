#include "common.h"

extern s16 D_800FE4A6;
extern s32 low_12_values_within_511(s16 value_a, s16 value_b);
extern s32 get_transform_entry_by_index(s32 entry_index);

/* Update the object's state value according to whether the pair check returns zero. */
void update_transform_state_value(void *object) {
    s32 result;

    result = low_12_values_within_511(D_800FE4A6, *(s16 *)((s8 *)object + 0x16));
    if (result != 0) {
        *(s32 *)((s8 *)object + 0xC) = get_transform_entry_by_index(0);
    } else {
        *(s32 *)((s8 *)object + 0xC) = get_transform_entry_by_index(1);
    }
}

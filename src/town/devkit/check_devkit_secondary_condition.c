#include "common.h"
#include "town/scene/flags.h"

extern s16 D_80700BAC[];
extern u8 devkit_flag_ids[];

/* Returns whether the indexed secondary check passes while both primary checks fail. */
s32 check_devkit_secondary_condition(s32 value_index) {
    s16 *primary_values;
    s32 passes;

    primary_values = D_80700BAC;
    passes = 0;
    if (test_indexed_flag_bit(primary_values[value_index]) == 0) {
        passes = 0;
        if (test_indexed_flag_bit(primary_values[0]) == 0) {
            passes = test_indexed_flag_bit(*(s16 *)(devkit_flag_ids + value_index * 2)) != 0;
        }
    }
    return passes;
}

#include "common.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"

extern M2C_UNK D_80016E1C;

/* Returns the address of D_80016E1C. */
s32 *get_flag_test_table_address(void *unused_table_a, void *unused_table_b, s32 unused_value, s32 unused_line) {
    return &D_80016E1C;
}

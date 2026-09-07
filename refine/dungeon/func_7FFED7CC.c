#include "common.h"
#include "m2c_compat.h"

extern u32 *D_801131EC;

typedef struct S_8008AF2C_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8008AF2C_0;   /* var_t0 in func_8008AF2C */

/* Return the table value matching the three packed key fields, or zero if absent. */
u32 func_8008AF2C(s32 key_flag, s32 key_high, s32 key_low) {
    u32 *value_ptr;
    u32 *entry;
    u32 packed_key;
    u32 high_mask;
    u32 low_mask;

    entry = D_801131EC;
    if (((S_8008AF2C_0 *)entry)->unk_04 != 0) {
        high_mask = 0x3F000000;
        low_mask = 0x007F0000;
        value_ptr = entry + 1;
scan_entry:
        packed_key = *entry;
        if ((key_flag == ((packed_key >> 0x17) & 1)) && (key_high == ((packed_key & high_mask) >> 0x18)) && (key_low == ((packed_key & low_mask) >> 0x10))) {
            return *value_ptr;
        }
        value_ptr += 2;
        entry += 2;
        if (*value_ptr != 0) {
            goto scan_entry;
        }
    } else {
        return 0U;
    }
    return 0U;
}

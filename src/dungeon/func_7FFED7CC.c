#include "modules/dungeon_ovl_d54c.h"

u32 *func_8008AF2C(s32 key_flag, s32 key_high, s32 key_low) {
    u32 *value_ptr;
    u32 *entry;
    u32 packed_key;
    u32 high_mask;
    u32 low_mask;

    entry = D_801131EC;
    if (((ovl_d54c_7FFED7CC_S_8008AF2C_0 *)entry)->unk_04 != 0) {
        high_mask = 0x3F000000;
        low_mask = 0x007F0000;
        value_ptr = entry + 1;
        do {
            packed_key = *entry;
            if ((key_flag == ((packed_key >> 0x17) & 1)) && (key_high == ((packed_key & high_mask) >> 0x18))
            && (key_low == ((packed_key & low_mask) >> 0x10))) {
                return (u32 *)*value_ptr;
            }
            value_ptr += 2;
            entry += 2;
        } while (*value_ptr != 0);
    }
    return NULL;
}

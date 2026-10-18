#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"

s32 generate_random_value();                             /* extern */

/* Combine the adjusted input divided by four with the helper result low bits. */
s32 get_random_scaled_value(s16 input_value) {
    s16 adjusted_value;

    adjusted_value = input_value;
    if (input_value == 0xFF) {
        adjusted_value = 0x1E;
    }
    return ((s32) (adjusted_value << 0x10) >> 0x12) + (generate_random_value() & 3);
}

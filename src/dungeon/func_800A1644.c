#include "common.h"

extern s32 generate_random_value(void);


/* Return a 16-bit random value within the inclusive bounds. */
s32 random_dungeon_range_16(u32 bound_a, u32 bound_b) {
    u32 result;
    u32 range;
    u32 random_value;
    u32 upper;
    u32 lower;

    lower = bound_a;
    upper = bound_b;
    if (upper < lower) {
        random_value = upper;
        upper = lower;
        lower = random_value;
    }
    random_value = generate_random_value() & 0xFFFF;
    range = (upper - lower) + 1;
    result = ((random_value % range) + lower) & 0xFFFF;
    return result;
}

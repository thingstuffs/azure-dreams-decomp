#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
/* Test whether the value lies within the inclusive lower and upper bounds. */
s32 func_8001CE14(s16 value, s32 lower_bound, s16 upper_bound)
{
    s32 in_range;
    s32 scaled_lower_bound;
    in_range = 0;
    scaled_lower_bound = lower_bound << 0x10;
    if ((value << 0x10) >= scaled_lower_bound) {
        in_range = upper_bound >= value;
    }
    return in_range;
}

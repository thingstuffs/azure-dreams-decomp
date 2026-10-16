/* Relink of matched dungeon/func_80289E14; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

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

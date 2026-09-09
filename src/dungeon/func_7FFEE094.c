#include "common.h"

extern u8 D_800FC418;

/* Set D_800FC418 to 0xFF and return 1. */
s32 town_map_del(void) {
    D_800FC418 = 0xFF;
    return 1;
}

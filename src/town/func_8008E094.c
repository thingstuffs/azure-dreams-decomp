#include "common.h"

extern u8 D_800FC418;

/* town_map_del: flag the town map for deletion and return success. */
s32 town_map_del(void) {
    D_800FC418 = 0xFF;
    return 1;
}

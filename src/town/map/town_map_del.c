#include "common.h"

extern u8 town_map_status;

/* town_map_del: flag the town map for deletion and return success. */
s32 town_map_del(void) {
    town_map_status = 0xFF;
    return 1;
}

#include "common.h"

extern s8 town_map_status;

/* Clears D_800FC418 and returns success. */
s32 clear_town_map_status(void) {
    town_map_status = 0;
    return 1;
}

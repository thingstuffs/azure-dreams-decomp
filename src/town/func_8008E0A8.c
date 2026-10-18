#include "common.h"

extern s8 D_800FC418;

/* Clears D_800FC418 and returns success. */
s32 clear_town_map_status(void) {
    D_800FC418 = 0;
    return 1;
}

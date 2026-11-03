#include "common.h"
#include "town/scene.h"

extern s32 count_town_items(void);
/* Returns 20 minus the result of func_80017200. */
s32 get_remaining_value_to_20(void) { return 20 - count_town_items(); }

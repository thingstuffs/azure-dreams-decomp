#include "common.h"
#include "town/scene.h"
#include "town/shop.h"

/* Returns 20 minus the result of func_80017200. */
s32 get_remaining_town_item_capacity(void) { return 20 - count_town_items(); }

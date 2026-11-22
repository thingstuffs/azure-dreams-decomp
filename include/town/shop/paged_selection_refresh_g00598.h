#ifndef TOWN_SHOP_PAGED_SELECTION_REFRESH_G00598_H
#define TOWN_SHOP_PAGED_SELECTION_REFRESH_G00598_H
/* Paged selection refresh declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B03D0, CL:town/func_800B085C. */

#include "common.h"
#include "m2c_compat.h"

#include "shared/dungeon_item_entries.h"

#include "town/shop/grid_menu.h"

/* Functions defined in this translation unit. */
s32 count_leading_typed_records(DungeonItemEntry *entries);
void refresh_paged_selection_state(GridMenuObject *record);

#endif

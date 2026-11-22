#ifndef TOWN_SHOP_TWIN_SHOP_INPUT_G00597_H
#define TOWN_SHOP_TWIN_SHOP_INPUT_G00597_H
/* Twin shop input declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B016C, CL:town/func_800B02BC, CL:town/func_800B03A4, CL:town/func_800B03D0. */

#include "common.h"
#include "engine/script.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "town/shop.h"


int get_item_name(struct DungeonItemEntry *object);
extern s32 advance_index_with_directional_clamp(s32 current_selection, s32 selection_step, s32 value);
extern void SD_Call(s32 sound_id);
extern void confirm_selected_entry(GridMenuObject *menu);

/* Functions defined in this translation unit. */
void refresh_selected_item_name(GridMenuObject *record);

#endif

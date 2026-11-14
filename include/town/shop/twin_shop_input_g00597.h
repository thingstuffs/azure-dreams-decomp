#ifndef TOWN_SHOP_TWIN_SHOP_INPUT_G00597_H
#define TOWN_SHOP_TWIN_SHOP_INPUT_G00597_H
/* Twin shop input declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B016C, CL:town/func_800B02BC, CL:town/func_800B03A4, CL:town/func_800B03D0. */

#include "common.h"
#include "records/Rec_func_800AD7F8_arg0.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "town/shop/grid_menu.h"


int get_item_name(void *object);
extern s32 advance_index_with_directional_clamp(s32 current_selection, s32 selection_step, s32 value);
extern void SD_Call(s32 sound_id);
extern void set_status_from_flagged_total(void *record);
extern void confirm_selected_entry(s32 *menu);
extern void close_twin_shop(void *shop_ptr);
extern void set_shop_page_and_selection(s32 menu_value, s32 row, s32 selection);
extern void set_shop_selected_entry(s32 menu_value, s32 selection);
extern s32 script_status;

/* Functions defined in this translation unit. */
void refresh_selected_item_name(Rec_func_800AD7F8_arg0 *record);
void refresh_selected_item_name_with_fallback(GridMenuObject *entry_table);
void handle_twin_shop_input(s32 *menu);

#endif

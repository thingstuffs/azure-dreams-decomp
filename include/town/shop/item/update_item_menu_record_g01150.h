#ifndef TOWN_SHOP_ITEM_UPDATE_ITEM_MENU_RECORD_G01150_H
#define TOWN_SHOP_ITEM_UPDATE_ITEM_MENU_RECORD_G01150_H
/* update item menu record g01150. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01150 - CL:town/func_800B2100, CL:town/func_800B2150, CL:town/func_800B2264. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/item_menu.h"
#include "town/shop.h"
#include "town/shop/item_menu_actions.h"

void populate_item_menu_page_entries(ItemMenuPart **parts, ItemMenuObject *object);
/* extern */
void populate_item_menu_lower_entries(ItemMenuObject *object);
void populate_current_item_menu_page(ItemMenuObject *object);
/* extern */
void update_item_menu_page_bounds(ItemMenuObject *object);
/* extern */
void *create_item_menu_display_controller(ItemMenuStateNode *owner, s32 position, s32 x, s32 y, void *entry);
extern s32 D_800891F4;
extern u8 D_800AF96C[];
extern s32 advance_index_with_directional_clamp(s32, s32, s32);
extern void get_item_name_with_shared_text_table(void *entry);
extern void sort_entries_by_category(void *);
extern void SD_Call(s32);
extern void set_item_menu_entry_coordinates(ItemMenuObject *object);
void fade_color_to_gray(ItemMenuPart *part, s32 stop_at_gray);
s32 advance_timed_tagged_stream(FrameState *state);
extern s32 item_menu_record_callback[];

/* Functions defined in this translation unit. */
void update_item_menu_record(ItemMenuObject *record);
void *place_selected_item_menu_entry(ItemMenuObject *entry);
void store_item_menu_check_result(ItemMenuObject *record_data);
void update_item_menu_selection(ItemMenuObject *obj);
void reset_item_menu_entity_state(ItemMenuObject *entity);
void advance_item_menu_step(ItemMenuObject *object);

#endif

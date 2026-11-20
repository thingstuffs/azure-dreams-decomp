#ifndef TOWN_SHOP_SHOP_STATE_INITIALIZATION_G00599_H
#define TOWN_SHOP_SHOP_STATE_INITIALIZATION_G00599_H
/* Shop state initialization declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0888, CL:town/func_800B0994, CL:town/func_800B09E8, CL:town/func_800B0B44. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "town/shop.h"

void refresh_paged_selection_state();
/* extern */
s32 allocate_paged_shop_item_list(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
/* extern */
void *create_floating_number_widget();
/* extern */
void advance_dispatch_when_countdown_expires(GridMenuObject *state_data);
extern void set_shop_fade_out_callback(s32 object);
extern void set_advance_inner_value_callback(s32 object); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Functions defined in this translation unit. */
void save_shop_script_state(struct ShopMenu *shop);
void restore_shop_script_state(struct ShopMenu *shop);
void *open_shop(s32 unused, s32 primary_param, s32 secondary_param, s32 shared_param);

#endif

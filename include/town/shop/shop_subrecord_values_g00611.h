#ifndef TOWN_SHOP_SHOP_SUBRECORD_VALUES_G00611_H
#define TOWN_SHOP_SHOP_SUBRECORD_VALUES_G00611_H
/* Shop subrecord values declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3FDC. */

#include "common.h"
#include "m2c_compat.h"

struct ShopWindow;

/* Functions defined in this translation unit. */
void set_shop_change_indicator_color(struct ShopWindow *window, s32 target_value);
void set_shop_page_and_selection(s32 record_address, s32 value_10, s32 value_08);

#endif

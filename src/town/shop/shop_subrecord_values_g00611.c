/* Shop subrecord values (G00611). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3FDC. */
#include "town/shop/shop_subrecord_values_g00611.h"
#include "town/shop/shop_window_layout_g00610.h"
#include "town/shop.h"
#include "town/shop/item.h"

/* Set the decrease or increase indicator color when the current and target values differ. */
void set_shop_change_indicator_color(ShopWindow *window, s32 target_value) {
    ShopWindowWidgets *widgets;
    s32 current_value;
    ShopWidget **indicator_entry;

    current_value = window->page;
    if (current_value != target_value) {
        widgets = window->widgets;
        if (current_value >= target_value) {
            indicator_entry = &widgets->left_child;
        } else {
            indicator_entry = &widgets->right_child;
        }
        (*indicator_entry)->data->color = 0xE0E0E0;
    }
}

/* Set two subrecord values and run their associated update routines. */
void set_shop_subrecord_values(s32 record_address, s32 value_10, s32 value_08) {
    ShopWindow *subrecord;

    subrecord = record_address + 0x20;
    subrecord->selected_entry = value_08;
    set_shop_change_indicator_color(subrecord, value_10);
    subrecord->page = value_10;
    populate_shop_item_rows(subrecord);
}

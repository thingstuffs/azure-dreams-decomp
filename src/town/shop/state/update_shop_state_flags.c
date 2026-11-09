#include "common.h"
#include "town/shop/shop_window_layout_g00610.h"
#include "town/shop/state.h"

extern s32 item_menu_primary_page_data[];
extern s32 card_selection_display_data[];

/* Update status flags and state pointers from the current value and its limit. */
void update_shop_state_flags(ShopWindow *window) {
    if (window->page > 0) {
        s32 branch_flags;

        window->widgets->left_child->value.pointer = item_menu_primary_page_data;
        branch_flags = window->page_edge_flags;
        branch_flags &= ~2;
        window->page_edge_flags = branch_flags;
    } else {
        s32 branch_flags;

        branch_flags = window->page_edge_flags;
        branch_flags |= 2;
        window->page_edge_flags = branch_flags;
    }

    if (window->page < window->page_limit) {
        s32 clear_mask;

        clear_mask = ~1;
        window->page_edge_flags &= clear_mask;

        window->widgets->right_child->value.pointer = card_selection_display_data;
        return;
    }

    window->page_edge_flags |= 1;
}

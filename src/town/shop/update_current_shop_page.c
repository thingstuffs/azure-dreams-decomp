#include "common.h"
#include "town/shop.h"
#include "town/shop/shop_window_layout_g00610.h"

/* Updates up to five entries on the current page and clears unused slots. */
void update_current_shop_page(struct ShopWindow *list) {
    s32 slot;

    for (slot = 0; slot < 5; slot++) {
        s32 entry_index = list->page * 5 + slot;
        if (entry_index >= list->entry_count) {
            break;
        }
        set_shop_slot_colors((struct TownObject *)list, entry_index);
    }

    for (; slot < 5; slot++) {
        list->widgets->rows[1][slot]->value.word = 0;
    }
}

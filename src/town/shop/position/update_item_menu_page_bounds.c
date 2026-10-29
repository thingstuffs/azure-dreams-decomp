#include "common.h"
#include "shared/item_menu.h"
#include "town/shop/position.h"

extern u8 item_menu_primary_page_data[];
extern u8 card_selection_display_data[];

/* Shows or hides the previous/next page indicators (parts 38 and 39) and updates the page flags. */
void update_item_menu_page_bounds(ItemMenuObject *obj)
{
    register ItemMenuState *state;
    s32 clear_mask;

    if (obj->menu->page > 0) {
        u32 flags;

        obj->parts[38]->handler = item_menu_primary_page_data;
        flags = obj->page_flags;
        flags &= ~2;
        obj->page_flags = flags;
    } else {
        obj->parts[38]->handler = 0;
        obj->page_flags |= 2;
    }
    state = obj->menu;
    if (state->page < state->last_page) {
        clear_mask = -2;
        obj->page_flags &= clear_mask;
        obj->parts[39]->handler = card_selection_display_data;
        return;
    }

    obj->parts[39]->handler = 0;
    obj->page_flags |= 1;
}

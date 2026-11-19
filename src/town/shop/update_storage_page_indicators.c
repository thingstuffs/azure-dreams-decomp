#include "common.h"
#include "town/shop.h"
#include "town/menu/alternate_page_records_g00619.h"

/* Shows or hides the previous/next page indicators (parts 38 and 39) and updates the edge flags. */
void update_storage_page_indicators(StorageOwner *control)
{
    StorageSource *range_state;

    if (control->owner->page.current > 0) {
        control->parts[38]->handler = item_menu_primary_page_data;
        control->edge_flags = control->edge_flags & -3;
    } else {
        control->parts[38]->handler = 0;
        control->edge_flags = control->edge_flags | 2;
    }

    range_state = control->owner;
    if (range_state->page.current < range_state->page.last) {
        control->edge_flags = control->edge_flags & -2;
        control->parts[39]->handler = card_selection_display_data;
    } else {
        control->edge_flags = control->edge_flags | 1;
        control->parts[39]->handler = 0;
    }
}

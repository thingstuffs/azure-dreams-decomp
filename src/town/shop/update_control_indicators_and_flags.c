#include "common.h"
#include "town/shop.h"

typedef struct S_800B4AB0_1 {
    u8 pad_00[0x2C];
    s32 unk_2C;
    s32 unk_30;
} S_800B4AB0_1;   /* state in update_control_indicators_and_flags */

typedef struct S_800B4AB0_2 {
    u8 pad_00[0x2C];
    s32 unk_2C;
} S_800B4AB0_2;   /* control->owner in update_control_indicators_and_flags */

extern u8 item_menu_primary_page_data[];
extern u8 card_selection_display_data[];

/* Shows or hides the previous/next page indicators (parts 38 and 39) and updates the edge flags. */
void update_control_indicators_and_flags(StorageOwner *control)
{
    S_800B4AB0_1 *range_state;

    if (((S_800B4AB0_2 *)(control->owner))->unk_2C > 0) {
        control->parts[38]->handler = item_menu_primary_page_data;
        control->edge_flags = control->edge_flags & -3;
    } else {
        control->parts[38]->handler = 0;
        control->edge_flags = control->edge_flags | 2;
    }

    range_state = control->owner;
    if (range_state->unk_2C < range_state->unk_30) {
        control->edge_flags = control->edge_flags & -2;
        control->parts[39]->handler = card_selection_display_data;
    } else {
        control->edge_flags = control->edge_flags | 1;
        control->parts[39]->handler = 0;
    }
}
